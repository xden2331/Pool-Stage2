#include "stagetwocreator.h"
#include "simpletable.h"
#include "simpleball.h"
#include "composedball.h"
#include "simplecreator.h"
#include "pocketdecorator.h"
#include "pocket.h"

/**
 * @brief StageTwoCreator::makeTable create table using Decorator
 * Design Pattern.
 * @param spec QJsonObject descripts table information
 * @return a table
 */
unique_ptr<Table> StageTwoCreator::makeTable(const QJsonObject &spec)
{
    SimpleCreator sc;
    unique_ptr<Table> tableBase = sc.makeTable(spec);
    vector<Pocket*>* pockets = new vector<Pocket*>();
    for(const auto& item : spec["pockets"].toArray()){
        double radius = 15;
        if(item.toObject().contains("radius")){
            radius = item.toObject()["radius"].toDouble();
        }
        Pocket* p = new Pocket(QVector2D(item.toObject()["position"].toObject()["x"].toDouble(),
                item.toObject()["position"].toObject()["y"].toDouble()),
                radius);
        pockets->push_back(p);
    }

    return unique_ptr<PocketDecorator>(
                new PocketDecorator(std::move(tableBase), pockets)
                );
}

/**
 * @brief StageTwoCreator::makeBall make a composed ball
 * @param spec QJsonObject descripts a ball
 * @return a composed ball or a simple ball
 */
unique_ptr<Ball> StageTwoCreator::makeBall(const QJsonObject &spec)
{
    QString color("white");
    float mass = 1.0f;
    double strength = std::numeric_limits<double>::infinity();
    float radius = 10;
    QVector2D pos(0,0);
    QVector2D vel(0,0);
    if(spec.contains("colour")) color = QString(spec["colour"].toString());
    if(spec.contains("mass")) mass = spec["mass"].toDouble();
    if(spec.contains("strength")) strength = spec["strength"].toDouble();
    if(spec.contains("radius")) radius = spec["radius"].toDouble();
    if(spec.contains("position")) pos = QVector2D(spec["position"].toObject()["x"].toDouble(), spec["position"].toObject()["y"].toDouble());
    if(spec.contains("velocity")) vel = QVector2D(spec["velocity"].toObject()["x"].toDouble(), spec["velocity"].toObject()["y"].toDouble());


    //if it does not have children
    if(!spec.contains("balls")){
        return unique_ptr<Ball>(
                    new SimpleBall(
                        radius, color,
                        mass,
                        pos,
                        vel
                ));
    }

    //if has children
    unique_ptr<ComposedBall> parent(new ComposedBall(
                              color, radius,
            mass,
            pos,
            vel,
            strength));

    // make its children balls
    for(const auto& i : spec["balls"].toArray()){
        unique_ptr<Ball> child = this->makeBall(i.toObject());
        QVector2D childPosition(parent->position.x()+child->position.x(),
                                parent->position.y()+child->position.y());
        if(child->getColor().operator ==("white")){ // default value is white as the child does not have any color,
            QColor pC = parent->getColor();
            child->setColor(pC); // change its color to the parent's color
        }

        // if the child is valid add it to the parent
        if((child->radius + childPosition.distanceToPoint(parent->position)) <= parent->radius){
            parent->mass += child->mass;
            parent->add(std::move(child));
        }
    }

    return parent;
}
