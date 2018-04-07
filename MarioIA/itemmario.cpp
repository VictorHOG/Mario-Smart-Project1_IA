#include "itemmario.h"
#include <vector>
#include <utility>
#include <QPixmap>

using namespace std;

itemMario::itemMario(vector< pair< int,int > > camino){
    QPainter *painter;
    QPixmap mario("../Images/mario.png");
    qreal x;
    qreal y;
    // pixeles a la vez
    velocidad = 10;

    for (int i = 0;(unsigned) i < camino.size(); i++){
        pair<int,int> posicion = camino[i];
        x = posicion.first;
        y = posicion.second;

        setPos(mapToParent(x, y));
        painter->drawPixmap(x, y, mario);
    }
}

void itemMario::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

}

void itemMario::advance(int phase){
    if (!phase) return;

    QPointF pos = this->pos();

    setPos(mapToParent(0, -(velocidad)));
}

