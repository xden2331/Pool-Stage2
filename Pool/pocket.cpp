#include "pocket.h"

Pocket::Pocket(const QVector2D &position, float radius):
    Decoration(position), m_radius(radius)
{}

void Pocket::draw(QPainter &painter) const
{
    QBrush brush(this->m_color);
    painter.setBrush(brush);
    painter.drawEllipse(
        this->m_position.toPointF(),
        this->m_radius, this->m_radius
    );
}
