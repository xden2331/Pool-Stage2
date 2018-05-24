#include "simpletable.h"
#include <QBrush>
#include <QPolygon>

SimpleTable::SimpleTable(const QSize& dim, const QColor& color, float friction)
: Table(dim, friction), color(color) {}

void SimpleTable::draw(QPainter& painter) const {
	QBrush brush(this->color);
	painter.setBrush(brush);
    painter.drawRect(QRect(QPoint(), this->dimension));
}

int SimpleTable::whichStage()
{
    return 1;
}

vector<Decoration *> SimpleTable::getDecorations() const
{
    vector<Decoration *> temp;
    return temp;
}
