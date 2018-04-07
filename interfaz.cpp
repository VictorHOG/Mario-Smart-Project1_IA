#include "interfaz.h"
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QList>
#include <QTextStream>
#include <iostream>
#include <utility>
#include <QLayoutItem>
#include <windows.h>

#define MURO 1
#define MARIO 2
#define FLOR 3
#define TORTUGA 4
#define PEACH 5

Interfaz::Interfaz(vector< pair< pair<int, int>, int> > camino, vector< vector<int> > tablero) {
    dibujarTablero(camino, tablero);
    k = 1;
    this->camino = camino;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(avanzar()));
    timer->start(500);
}

void Interfaz::avanzar(){
    if(k >= camino.size()){
        this->close();
        return;
    }
    QPixmap marioFlor("../Images/marioFlor.png");
    QPixmap mario("../Images/mario.png");

    pair<int, int> coordenada = camino[k].first;
    int flor = camino[k].second;
    QLabel *imgMario = new QLabel(this);
    QLabel *imgNull = new QLabel(this);
    if(flor){
        imgMario->setPixmap(marioFlor);
    }else{
        imgMario->setPixmap(mario);
    }
    imgMario->setVisible(true);
    imgNull->setVisible(true);

    QLayoutItem *item = layout->itemAtPosition(coordenada.first, coordenada.second);
    layout->removeItem(item);
    item->widget()->setVisible(false);

    QLayoutItem *itemAnterior = layout->itemAtPosition(coordAnterior.first, coordAnterior.second);
    layout->removeItem(itemAnterior);
    itemAnterior->widget()->setVisible(false);

    layout->addWidget(imgNull, coordAnterior.first, coordAnterior.second, Qt::AlignHCenter);

    imgMario->setVisible(true);
    layout->addWidget(imgMario, coordenada.first, coordenada.second, Qt::AlignHCenter);

    coordAnterior = coordenada;
    k++;
    update();
}

void Interfaz::dibujarTablero(vector< pair< pair<int, int>, int> > camino,
                              vector<vector<int> > tablero) {

    int rows = 0, columns = 0;

    layout = new QGridLayout;

    QPixmap mario("../Images/mario.png");
    QPixmap ladrillo("../Images/ladrillo.png");
    QPixmap princesa("../Images/princesa.png");
    QPixmap flor("../Images/flor.png");
    QPixmap tortuga("../Images/tortuga.png");
    QPixmap marioInicio("../Images/marioInicio.png");

    QLabel *img = new QLabel(this);    
    QLabel *imgMarioInicio = new QLabel(this);
    QLabel *imgPrincesa = new QLabel(this);        
    QLabel *imgNull = new QLabel(this);        

    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::darkCyan));    
    //this->setFixedSize(QSize(850, 600));
    this->setFixedHeight(700);

    // agregar las imagenes a los labels
    img->setPixmap(mario);
    imgMarioInicio->setPixmap(marioInicio);    
    imgPrincesa->setPixmap(princesa);                

    img->setVisible(false);
    imgMarioInicio->setVisible(false);
    imgPrincesa->setVisible(false);
    imgNull->setVisible(false);

    rows = tablero.size();
    columns = tablero[0].size();

    for (int i = 0; (unsigned) i < rows; i++) {
        for (int j = 0; (unsigned) j < columns; j++) {
            if (tablero[i][j] == 1) {
                // 1 si es muro
                QLabel *imgLadrillo = new QLabel(this);
                imgLadrillo->setPixmap(ladrillo);                
                layout->addWidget(imgLadrillo, i, j, Qt::AlignHCenter);
                imgLadrillo->setVisible(true);                
            } else if (tablero[i][j] == 2) {
                // 2 si es el punto donde inicia Mario                
                layout->addWidget(imgMarioInicio, i, j, Qt::AlignHCenter);
                imgMarioInicio->setVisible(true);
            } else if (tablero[i][j] == 3) {
                // 3 si es una flor
                QLabel *imgFlor = new QLabel(this);
                imgFlor->setPixmap(flor);
                layout->addWidget(imgFlor, i, j, Qt::AlignHCenter);
                imgFlor->setVisible(true);
            } else if (tablero[i][j] == 4) {
                // 4 si es una tortuga
                QLabel *imgTortuga = new QLabel(this);
                imgTortuga->setPixmap(tortuga);
                layout->addWidget(imgTortuga, i, j, Qt::AlignHCenter);
                imgTortuga->setVisible(true);
            } else if (tablero[i][j] == 5) {
                // 5 si es la princesa
                layout->addWidget(imgPrincesa, i, j, Qt::AlignHCenter);
                imgPrincesa->setVisible(true);
            } else if (tablero[i][j] == 0) {
                layout->addWidget(imgNull, i, j, Qt::AlignHCenter);
                imgNull->setVisible(true);
            }
        }
    }    

    coordAnterior = camino[0].first;

    this->setLayout(layout);

}
