#include "scenemanager.h"
#include "math.h"

void collideBalls(Ball&, Ball&);
void collideTable(const Table&, Ball&);
bool dropIntoPockets(const Table&, Ball&);
void updateChildren(unique_ptr<Ball> parent);
QVector2D isTouching(const Ball&, const Ball&);
QVector2D isTouching(const Table&, const Ball&);

SceneManager::SceneManager(unique_ptr<Table> poolTable, vector<unique_ptr<Ball>>& initBalls)
    : table(std::move(poolTable)), balls(std::move(initBalls)), offset(20, 20) {}

void SceneManager::draw(QPainter& painter) const {
    painter.translate(offset);
    this->table->draw(painter);
    for (unsigned long i=0; i<this->balls.size(); ++i) {
        const auto& item = balls[i];
        item->draw(painter);
    }
    painter.translate(-offset);
}

QSize SceneManager::veiwPort() const {
    return this->table->dimension + QSize(this->offset.x(), this->offset.y())*2;
}

void SceneManager::press(QVector2D& pos)
{
    QVector2D whiteBallPos = balls.at(0)->position;
    // check if press on cue ball and the cue ball is rest.
    if(whiteBallPos.distanceToPoint(pos) < balls.at(0)->radius*5 && balls.at(0)->velocity.length() <= 0.1){
        balls.at(0)->velocity *= 0;
        pressOnWhiteBall = true;
    }
    // chekc if click on composed balls, show their children or not.
    for (unsigned long i=0; i<this->balls.size(); ++i) {
        const auto& item = balls[i];
        bool click = (pos.distanceToPoint(item->position+QVector2D(offset)) < item->radius);
        item->showComposedChildren(click);
    }
}


void SceneManager::releaseMouse(QVector2D& pos)
{
    // if cue ball is pressed and released, give it a velocity
    if(pressOnWhiteBall
            &&balls.at(0)->velocity.lengthSquared() == 0){
        double dist = pos.distanceToPoint(balls.at(0)->position);
        QVector2D dir = (balls.at(0)->position - pos).normalized();
        balls.at(0)->velocity += 2*dir*dist;
        pressOnWhiteBall = false;
    }
}

/**
 * @brief SceneManager::tick
 * @param dtime
 */
void SceneManager::tick(float dtime) {

    for (unsigned long a=0; a<balls.size(); ++a) {
        Ball& ballA = *balls[a];
        // kinetic energy
        float ballMass = ballA.mass;
        double strength = ballA.getStrength();
        float radius = ballA.radius;
        QVector2D preCollisionVelocity = ballA.velocity;
        //

        // collision
        collideTable(*this->table, ballA);
        for (auto b = a + 1; b != balls.size(); ++b) {
            collideBalls(ballA, *balls[b]);
        }

        ballA.position += ballA.velocity * dtime;
        ballA.velocity -= ballA.velocity.normalized() * dtime * this->table->surface_friction;

        //checking if this is decorated table
        if(this->table->whichStage() == 2){
            if(dropIntoPockets(*this->table, ballA)){
                if(a == 0){// if the current ball drops, and it is the cue ball, reset its position
                    ballA.velocity *= 0;
                    ballA.position.setX(this->table->dimension.width()/4);
                    ballA.position.setY(this->table->dimension.height()/2);
                }else{//if not cue ball, remove it
                    balls.erase(balls.begin()+a);
                    --a;
                    continue;
                }
            }
        }

        //SOURCE: Assignment SPEC
        //If the ball does not drop, check if it's broken or not
        QVector2D deltaV = ballA.velocity - preCollisionVelocity;
        float energyOfCollision = ballMass*deltaV.lengthSquared();
        if(strength<energyOfCollision)
        {// if the parent ball is broken, remove it, and place its children onto table
            float energyPerBall = energyOfCollision/ballA.getChildrenNumber();
            QVector2D pointOfCollision((-deltaV.normalized())*radius);

            //for each component ball
            vector<unique_ptr<Ball>> children = ballA.getChildren();
            for(unique_ptr<Ball>& child:children){
                float componentBallMass = child->mass;
                QVector2D componentBallPosition = child->position + ballA.position;
                QVector2D componentBallVelocity = preCollisionVelocity
                        + sqrt(energyPerBall/componentBallMass)
                        *(componentBallPosition-pointOfCollision).normalized();
                child->velocity = componentBallVelocity;
                child->position = componentBallPosition;
                this->balls.push_back(std::move(child));
            }
            if(children.size()!=0){
                balls.erase(balls.begin()+a);
                --a;
            }
        }
    }
}

/**
 * @brief dropIntoPockets check if the ball drops into pockets
 * if the distance from pockets to ball is shorter than the radius
 * of ball, return true.
 * @param table current table
 * @param ball current ball
 * @author: Xing DENG
 */
bool dropIntoPockets(const Table &table, Ball &ball){
    auto pockets = table.getDecorations();
    for(auto item : pockets){
        Pocket* pocket = static_cast<Pocket*>(item);
        float dist = pocket->m_position.distanceToPoint(
                    ball.position);
        if(dist < ball.radius || dist < pocket->m_radius){
            return true;
        }
    }
    return false;
}

void collideTable(const Table& table, Ball& ball) {

    auto collision = isTouching(table, ball);

    if (QVector2D::dotProduct(collision, ball.velocity) < 0)
        return;

    if (collision.x())
        ball.velocity *= QVector2D(-1, 1);
    else if (collision.y())
        ball.velocity *= QVector2D(1, -1);
}

void collideBalls(Ball& ballA, Ball& ballB) {
    // SOURCE : ASSIGNMENT SPEC
    auto collision = isTouching(ballA, ballB);
    if (collision == NULL_2D) return;

    float mr = ballB.mass / ballA.mass;
    double pa = QVector2D::dotProduct(collision, ballA.velocity);
    double pb = QVector2D::dotProduct(collision, ballB.velocity);

    if (pa <= 0 && pb >= 0) return;

    double a = -(mr + 1);
    double b = 2*(mr * pb + pa);
    double c = -((mr - 1)*pb*pb + 2*pa*pb);
    double disc = sqrt(b*b - 4*a*c);
    double root = (-b + disc)/(2*a);
    if (root - pb < 0.01) {
        root = (-b - disc)/(2*a);
    }

    ballA.velocity += mr * (pb - root) * collision;
    ballB.velocity += (root - pb) * collision;
}

QVector2D isTouching(const Ball& ballA, const Ball& ballB) {
    auto collision = ballB.position - ballA.position;
    if (collision.length() <= ballA.radius + ballB.radius)
        return collision.normalized();
    else
        return NULL_2D;
}

QVector2D isTouching(const Table& table, const Ball& ball) {
    if (ball.position.x() <= ball.radius)
        return QVector2D(-1, 0);
    else if (ball.position.y() <= ball.radius)
        return QVector2D(0, -1);
    else if (ball.position.x() + ball.radius >= table.dimension.width())
        return QVector2D(1, 0);
    else if (ball.position.y() + ball.radius >= table.dimension.height())
        return QVector2D(0, 1);
    else
        return NULL_2D;
}
