#ifndef SIMPLEBALL_H
#define SIMPLEBALL_H

#include "ball.h"
#include <QColor>

class SimpleBall : public Ball
{
public:
	/**
	 * @brief SimpleBall Constructor
	 *
	 * @param radius
	 * @param color
	 * @param mass : use 0 for infinite mass
	 * @param position
	 * @param velocity
	 */
	SimpleBall(
        float radius, const QColor& color,
        float mass = 1.0f,
        const QVector2D& position = QVector2D(0,0),
        const QVector2D& velocity = QVector2D(0,0)
	);
	/**
	 * @brief Draws the ball onto the scene
	 *
	 * @param painter for rendering the ball
	 */
    void draw(QPainter& painter) const override;

    // Ball interface
    /**
     * @brief getColor
     * @return the colour of the ball
     */
    virtual QColor getColor() const override;

    /**
     * @brief setColor sets the ball's colour
     * @param color new colour
     */
    virtual void setColor(const QColor &color) override;

private:
    QColor color;

};

#endif // SIMPLEBALL_H
