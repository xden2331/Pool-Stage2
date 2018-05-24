#include "decorator.h"

Decorator::Decorator(unique_ptr<Table> table) :
    Table(table->dimension, table->surface_friction), m_table(std::move(table))
{}

void Decorator::draw(QPainter &painter) const{
    m_table->draw(painter);
}
