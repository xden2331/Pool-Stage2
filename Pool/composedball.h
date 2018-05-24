#ifndef COMPOSEDBALL_H
#define COMPOSEDBALL_H

#include "ball.h"
#include "simpleball.h"


/**
 * @brief The ComposedBall class can be made of some balls within it,
 * and it is responsible for them (i.e. updating their position), and
 * when the kinectic energy is great enough, the composed balls will be
 * broken, release their children, and disappear.
 */
class ComposedBall : public Ball
{
public:

    /**
     * @brief ComposedBall constructor for ComposedBall
     * @param color the colour of the ball
     * @param radius the radius of the ball
     * @param mass the mass of the ball
     * @param position the initial position of the ball
     * @param velocity the initial velocity of the ball
     * @param strength the strength of the ball(default to inifity)
     */
    ComposedBall(const QColor& color, float radius = 10.0f,
                 float mass = 1.0f,
                 const QVector2D& position = QVector2D(0,0),
                 const QVector2D& velocity = QVector2D(0,0),
                 double strength = std::numeric_limits<double>::infinity());

    /**
     * @brief add add a child (a ball tied on this ball) to the ball
     * @param child the tied ball
     */
    void add(unique_ptr<Ball> child);

    // Graphic interface
    /**
     * @brief draw render the ball
     * @param painter used to render
     */
    virtual void draw(QPainter &painter) const override;

    // Ball interface
    /**
     * @brief getColor get ball's colour
     * @return ball's colour
     */
    virtual QColor getColor() const override;

    /**
     * @brief setColor update ball's colour
     * @param color new colour
     */
    virtual void setColor(const QColor &color) override;

    /**
     * @brief showComposedChildren <b>only</b> used for composed balls, it
     * tells the composed balls to show their children or not
     * @param if yes, set showChildren to true, else false.
     */
    void showComposedChildren(const bool&) override;

    /**
     * @brief getStrength return the strength of a ball (usually used for composed balls)
     * the default strength is infinity
     * @return the strength
     */
    double getStrength() const override;

    /**
     * @brief getChildrenNumber return children's number (usually used for composed balls)
     * @return the number of children
     */
    int getChildrenNumber() const override;

    /**
     * @brief getChildren usually used for composed balls, get a list of children
     * @return a vector containing unique_ptrs pointing to balls
     */
    vector<unique_ptr<Ball>> getChildren() override;

private:
    QColor color;
    double strength;
    vector<unique_ptr<Ball>> childBalls;
    bool showChildren = true;
};

#endif // COMPOSEDBALL_H
