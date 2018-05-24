#include "pocketdecorator.h"

PocketDecorator::PocketDecorator(unique_ptr<Table> table, vector<Pocket *> *pockets):
    Decorator(std::move(table)),m_pockets(pockets)
{}

void PocketDecorator::draw(QPainter &painter) const{
    m_table->draw(painter);
    for(const auto* item : *m_pockets){
        item->draw(painter);
    }
}

int PocketDecorator::whichStage()
{
    return 2;
}

vector<Decoration *> PocketDecorator::getDecorations() const
{
    vector<Decoration *> temp;
    for(auto* item : *m_pockets){
        temp.push_back(
                    static_cast<Decoration*>(item));
    }
    return temp;
}
