#include "composedball.h"


ComposedBall::ComposedBall(const QColor &color, float radius, float mass, const QVector2D &position, const QVector2D &velocity, double strength)
    : Ball(radius, mass, position, velocity), color(color), strength(strength)
{
    showChildren = true;
}

void ComposedBall::add(unique_ptr<Ball> child)
{
    this->childBalls.push_back(std::move(child));
}

void ComposedBall::draw(QPainter &painter) const
{
    QBrush brush(this->color);
    painter.setBrush(brush);
    painter.drawEllipse(
        this->position.toPointF(),
        this->radius, this->radius
                );
    if(showChildren){
        for (auto a = this->childBalls.begin(); a != this->childBalls.end(); ++a) {
            Ball& ballA = **a;
            ballA.position += this->position;
            ballA.showComposedChildren(showChildren);
            ballA.draw(painter);
            ballA.position -= this->position;
        }
    }
}

QColor ComposedBall::getColor() const
{
    return color;
}

void ComposedBall::setColor(const QColor &color)
{
    this->color = color;
}

void ComposedBall::showComposedChildren(const bool& click)
{
    if(click) showChildren = !showChildren;
}

double ComposedBall::getStrength() const{
    return this->strength;
}

int ComposedBall::getChildrenNumber() const{
    return childBalls.size();
}

vector<unique_ptr<Ball>> ComposedBall::getChildren()
{
    return std::move(childBalls);
}

