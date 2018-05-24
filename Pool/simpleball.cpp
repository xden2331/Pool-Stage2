#include "simpleball.h"
#include <QBrush>
#include <QPen>

SimpleBall::SimpleBall(
	float radius, const QColor& color, float mass,
	const QVector2D& pos, const QVector2D& vel
) : Ball(radius, mass, pos, vel), color(color) {
    if(this->radius == 0){
        this->radius = 10;
    }
    if(this->mass == 0){
        this->mass = 1;
    }
}

void SimpleBall::draw(QPainter& painter) const {
	QBrush brush(this->color);
	painter.setBrush(brush);
	painter.drawEllipse(
		this->position.toPointF(),
		this->radius, this->radius
                );
}

QColor SimpleBall::getColor() const
{
    return color;
}

void SimpleBall::setColor(const QColor &color)
{
    this->color = color;
}
