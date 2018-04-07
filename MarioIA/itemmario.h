#ifndef ITEMMARIO_H
#define ITEMMARIO_H

#include <QPainter>
#include <QGraphicsItem>
#include <vector>
#include <utility>

using namespace std;

class itemMario: public QGraphicsItem
{
public:
    itemMario(vector< pair<int,int> > camino);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);

private:
    int velocidad;
};

#endif // ITEMMARIO_H
