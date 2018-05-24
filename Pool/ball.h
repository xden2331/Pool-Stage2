#ifndef BALL_H
#define BALL_H

#include "util.h"
#include "graphic.h"
#include <QVector2D>

/**
 * @brief The Ball class is not responsible for physics calculation
 *        it exposes public radius position, velocity and mass fields
 *        so the responsible class can access them directly.
 *        You can pretend it's a struct if you like.
 */
class Ball : public Graphic
{
public:
	float radius;
	float mass;
	QVector2D position;
	QVector2D velocity;
	/**
	 * @brief Constructor for ball
	 *
	 * @param radius used for collision detection
	 * @param mass used for physics
	 * @param pos initial poisiton for the ball
	 * @param vel inital velocity for the ball
	 */
	Ball(
        float radius = 10, float mass = 0,
		const QVector2D& pos = NULL_2D,
		const QVector2D& vel = NULL_2D
    ) : radius(radius), mass(mass), position(pos), velocity(vel) {}

    /**
     * @brief getColor
     * @return the colour of the ball
     */
    virtual QColor getColor() const = 0;

    /**
     * @brief setColor sets the ball's colour
     * @param color new colour
     */
    virtual void setColor(const QColor& color) = 0;

    /**
     * @brief showComposedChildren <b>only</b> used for composed balls so
     * far, it tells the composed balls to show their children or not
     * @param a bool parm shows children or not
     */
    virtual void showComposedChildren(const bool&) {}

    /**
     * @brief getStrength return the strength of a ball (usually used for composed balls)
     * default return value is 0, and a specific return value
     * is defined in the drieved classes
     * @return the strength
     */
    virtual double getStrength() const{
        return 0;
    }

    /**
     * @brief getChildrenNumber return children's number (usually used for composed balls)
     * default return value is 0 as a ball could have no children, and a specific return value
     * is defined in the drieved classes
     * @return the number of children
     */
    virtual int getChildrenNumber() const{
        return 0;
    }

    /**
     * @brief getChildren usually used for composed balls
     * default return value is an empty vector, and a specific return value is
     * defined in the drieved classes
     * As the children are unique_ptrs, I do not mark it as 'const' as std::move() is called.
     * @return a vector containing unique_ptrs pointing to balls
     */
    virtual vector<unique_ptr<Ball>> getChildren(){
        return {};
    }

    /**
     * @brief ~Ball destructor
     */
	virtual ~Ball() {}
};

#endif // BALL_H
