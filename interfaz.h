/*
* CARLOS FELIPE MONTOYA - 1535038
* DIANA MELISSA MILLARES - 1526062
* VICTOR HUGO ORTEGA - 1532342
*/

#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QTimer>
#include <QRect>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <QtCore>
#include <QCoreApplication>
#include <QTimer>
#include <utility>
//#include "itemmario.h"

using namespace std;

class Interfaz: public QWidget {
    Q_OBJECT

public:
    Interfaz(vector< pair< pair< int, int > ,int > > camino, vector< vector<int> > tablero);
    void dibujarTablero(vector< pair< pair< int, int >, int> > camino, vector< vector<int> > tablero);

public slots:
    //void iniciarAnimacion();
    void avanzar();

private:
    QTimer * timer;
    QGraphicsView vista;
    QPropertyAnimation *animacion;
    pair<int,int> coordAnterior;
    vector< pair < pair<int,int> , int > > camino;
    int k;
    QGridLayout *layout;
};

#endif // INTERFAZ_H
