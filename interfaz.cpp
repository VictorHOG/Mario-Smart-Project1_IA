/*
* CARLOS FELIPE MONTOYA - 1535038
* DIANA MELISSA MILLARES - 1526062
* VICTOR HUGO ORTEGA - 1532342
*/

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
#include <QMessageBox>

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
    int flor = camino[k].second; //se asigna el segundo valor a flor
    QLabel *imgMario = new QLabel(this);
    QLabel *imgNull = new QLabel(this);
    if(flor){ //si hay flor
        imgMario->setPixmap(marioFlor);
    }else{
        imgMario->setPixmap(mario);
    }
    imgMario->setVisible(true);
    imgNull->setVisible(true);
    //quitar el item por donde pasa Mario
    QLayoutItem *item = layout->itemAtPosition(coordenada.first, coordenada.second);
    //cout<<coordenada.first<<","<<coordenada.second<<"; ";
    layout->removeItem(item);
    item->widget()->setVisible(false);

    QLayoutItem *itemAnterior = layout->itemAtPosition(coordAnterior.first, coordAnterior.second);
    //cout<<coordAnterior.first<<","<<coordAnterior.second<<"; ";
    layout->removeItem(itemAnterior);
    itemAnterior->widget()->setVisible(false);

    layout->addWidget(imgNull, coordAnterior.first, coordAnterior.second, Qt::AlignHCenter);

    imgMario->setVisible(true);
    layout->addWidget(imgMario, coordenada.first, coordenada.second, Qt::AlignHCenter);

    coordAnterior = coordenada;    

    k++;
    update();

    /** //mensaje si hay flor
       if(camino[k].second == 1){
           QMessageBox::information(NULL,tr("¿Hay flor?"),tr("¡Flor!"));
           return;
       }
   //fin **/
    /**
    if(camino[k].first.first == 0 && camino[k].first.second == 8){
        QMessageBox::information(NULL,tr("¿Posición (0,8)?"),tr("Pasa la posicion (0,8)"));
        return;
    }**/
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

    //si en la casilla antes de la meta hay tortuga
    pair<int, int> coordPrueba;
    /** for(int l = 0; l < camino.size(); l++) {
        coordPrueba = camino[l-1].first;
    }
    if(tablero[coordPrueba.first][coordPrueba.second] == 4) {
        //cout<<"tortuga";
        QMessageBox::information(NULL,tr("¿Hay tortuga?"),tr("¡Tortuga!"));
    }
    //fin

    //# de tortugas en el camino
    int numTortuga = 0;
    for(int l = 0; l < camino.size(); l++) {
            coordPrueba = camino[l].first;
            if(tablero[coordPrueba.first][coordPrueba.second] == 4){
                numTortuga++;
            }
    }
    cout<<"# tortugas "<<numTortuga;
    //fin **/

    coordAnterior = camino[0].first;

    /** //veces que va a der, izq, aba, arr
    int arr, aba, izq, der;
        arr=aba=izq=der=0;
        for(int m=0;m<camino.size();m++){
        //arriba
        if(camino[m].first.first-1 == camino[m+1].first.first
                && camino[m].first.second == camino[m+1].first.second){
            arr++;            
        }
        //abajo
        if(camino[m].first.first+1 == camino[m+1].first.first
                  && camino[m].first.second == camino[m+1].first.second){
            aba++;
        }
        //izquierda
        if(camino[m].first.first == camino[m+1].first.first
                  && camino[m].first.second-1 == camino[m+1].first.second){
            izq++;
        }
        //derecha
        if(camino[m].first.first == camino[m+1].first.first
                  && camino[m].first.second+1 == camino[m+1].first.second){
            der++;
        }
    }
    QMessageBox::information(NULL,tr("direcciones"),tr("Arriba ")+QString::number(arr)+tr("\n")+
                             tr("Abajo ")+QString::number(aba)+tr("\n")+
                             tr("Derecha ")+QString::number(der)+tr("\n")+
                             tr("Izquierda ")+QString::number(izq)+tr("\n"));
    //fin **/

    this->setLayout(layout);
}
