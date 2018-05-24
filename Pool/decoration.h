#ifndef DECORATION_H
#define DECORATION_H

#include "util.h"
#include "graphic.h"

/**
 * @brief The Decoration class is an interface for decoration
 * decorating the pool game.
 */
class Decoration : public Graphic
{
public:
    QVector2D m_position;

    /**
     * @brief Decoration constructor
     * @param position the position of the decoration
     */
    Decoration(const QVector2D& position) : m_position(position){}

    /**
     * @brief ~Decoration destructor
     */
    virtual ~Decoration(){}
};

#endif // DECORATION_H
