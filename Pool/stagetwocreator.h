#ifndef STAGETWOCREATOR_H
#define STAGETWOCREATOR_H

#include "creator.h"
#include <typeinfo>

class StageTwoCreator : public Creator
{
    // Creator interface
protected:
    /**
     * @brief makes a SimpleTable from JSON config
     *
     * @param spec a JSON configuration for the table
     *
     * @return a SimpleTable with the specified configuration
     */
    virtual unique_ptr<Table> makeTable(const QJsonObject &spec);

    /**
     * @brief makes a SimpleBall from the JSON config
     *
     * @param spec a JSON configuration for the ball
     *
     * @return a SimpleBall with the specified configuration
     */
    virtual unique_ptr<Ball> makeBall(const QJsonObject &spec);
};

#endif // STAGETWOCREATOR_H
