#ifndef POCKETDECORATOR_H
#define POCKETDECORATOR_H

#include "decorator.h"
#include "pocket.h"

/**
 * @brief The PocketDecorator class is an implementation of 'Decorator'.
 * It decorates the base table using pockets.
 */
class PocketDecorator : public Decorator
{
public:

    /**
     * @brief PocketDecorator constructor
     * @param table decorated table
     * @param pockets decorations on the table
     */
    PocketDecorator(unique_ptr<Table> table, vector<Pocket *> *pockets);

    /**
     * @brief ~PocketDecorator destructor
     */
    virtual ~PocketDecorator(){
        delete m_pockets;
    }

    /**
     * @brief Draws the table onto the scene
     *
     * @param painter for rendering the table
     */
    void draw(QPainter &painter) const override;

    /**
     * @brief whichStage return which kind of table is using
     * @return 2 as this table is decorated
     */
    virtual int whichStage() override;

    // Table interface
    /**
     * @brief getDecorations return a list of decoration used to decorate table
     * if no decorations, return an empty list
     * @return a list of decorations
     */
    virtual vector<Decoration *> getDecorations() const override;

protected:
    vector<Pocket*> *m_pockets;
};

#endif // POCKETDECORATOR_H
