#ifndef TABLE_H
#define TABLE_H

#include "util.h"
#include "graphic.h"
#include "decoration.h"

class Table : public Graphic
{
public:
	QSize dimension;
	float surface_friction;

	/**
	 * @brief Constructor for Table
	 *
	 * @param dimension
	 * @param friction
	 */
    Table(const QSize& dimension = QSize(600, 300), float friction = 0.01)
	: dimension(dimension), surface_friction(friction) {}
    //Table(){}
	virtual ~Table() {}

    /**
     * @brief whichStage return which stage(version) of Table is being used
     * @return the version of table
     */
    virtual int whichStage() = 0;

    /**
     * @brief getDecorations return a list of decoration used to decorate table
     * if no decorations, return an empty list
     * @return a list of decorations
     */
    virtual vector<Decoration *> getDecorations() const = 0;
};

#endif // TABLE_H
