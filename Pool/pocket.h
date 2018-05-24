#ifndef POCKET_H
#define POCKET_H

#include "decoration.h"

/**
 * @brief The Pocket class is an implementation of 'Decoration' interface.
 * It has the color and radius of the pocket
 */
class Pocket : public Decoration
{
public:
    QColor m_color = Qt::black;
    float m_radius;

    /**
     * @brief Pocket constructor
     * @param position where is the pocket
     * @param radius the radius of the pocket
     */
    Pocket(const QVector2D& position, float radius = 15.0f);

    /**
     * @brief ~Pocket destructor
     */
    virtual ~Pocket(){}

    // Graphic interface
    /**
     * @brief Draws the table onto the scene
     *
     * @param painter for rendering the table
     */
    virtual void draw(QPainter &painter) const;
};

#endif // POCKET_H
