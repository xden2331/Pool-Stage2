#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include "table.h"

class SimpleTable : public Table
{
public:
	/**
	 * @brief SimpleTable constructor
	 *
	 * @param dimension : size of the table
	 * @param color
	 * @param friction
	 */
    SimpleTable(const QSize& dim = QSize(600,300), const QColor& color = Qt::green, float friction = 0.01f);
	/**
	 * @brief Draws the table onto the scene
	 *
	 * @param painter for rendering the table
	 */
	void draw(QPainter& painter) const;

    /**
     * @brief whichStage tell which type of table is using
     * @return the number implies the type
     */
    virtual int whichStage();

    // Table interface
    /**
     * @brief getDecorations return a list of decoration used to decorate table
     * if no decorations, return an empty list
     * @return a list of decorations
     */
    virtual vector<Decoration *> getDecorations() const;

private:
	QColor color;
};

#endif // SIMPLETABLE_H
