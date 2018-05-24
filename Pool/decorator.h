#ifndef DECORATOR_H
#define DECORATOR_H

#include "table.h"

/**
 * @brief The Decorator class is an interface. It is used to
 * decorate the table, adding new functions or feature to it.
 * Currently it is used for adding pockets to the table.
 */
class Decorator : public Table{
public:

    /**
     * @brief Decorator constructor
     * @param table the decorated table
     */
    Decorator(unique_ptr<Table> table);

    /**
     * @brief ~Decorator destructor
     */
    virtual ~Decorator(){}

    /**
     * @brief draw render the table with decorations
     * @param painter used to render
     */
    virtual void draw(QPainter &painter) const override;

    /**
     * @brief whichStage used to return which kind of table
     * is using. As the limitation of personal skills, I cannot
     * find a way casting unique_ptr<Table> to its drived class.
     * Instead, a method is called.
     * @return which 'stage'(version) of table is using. Stage one's
     * table return 1; Stage two's table return 2
     */
    virtual int whichStage() override = 0;

    // Table interface
    /**
     * @brief getDecorations return a list of decoration used to decorate table
     * if no decorations, return an empty list
     * @return a list of decorations
     */
    virtual vector<Decoration *> getDecorations() const override = 0;



protected:
    unique_ptr<Table> m_table;
};

#endif // DECORATOR_H
