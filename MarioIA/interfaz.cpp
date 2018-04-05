#include "interfaz.h"
#include <QPixmap>
#include <QGridLayout>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QList>
#include <QTextStream>
#include <vector>
#include <iostream>
#include <QTimer>

using namespace std;

Interfaz::Interfaz(QString path) {
    vector< vector<int> > listaAux;
    listaAux = leerArchivo(path);

    dibujarTablero(listaAux);
}

void Interfaz::dibujarTablero(vector< vector<int> > lista) {
    int rows = 0, columns = 0;

    QGridLayout *layout = new QGridLayout;

    QPixmap mario("../Images/mario.png");
    QPixmap ladrillo("../Images/ladrillo.png");
    QPixmap princesa("../Images/princesa.png");
    QPixmap flor("../Images/flor.png");
    QPixmap tortuga("../Images/tortuga.png");

//    QLabel *img = new QLabel(this);
    QLabel *imgPrincesa = new QLabel(this);        
    QLabel *imgNull = new QLabel(this);        

    this->setAutoFillBackground(true);
    this->setPalette(QPalette(Qt::darkCyan));    
    //this->setFixedSize(QSize(850, 600));
    this->setFixedHeight(700);

    // agregar las imagenes a los labels
//    img->setPixmap(mario);
    imgPrincesa->setPixmap(princesa);                

    //img->setVisible(false);
    imgPrincesa->setVisible(false);
    imgNull->setVisible(false);

    rows = lista.size();
    columns = lista[0].size();

    for (int j = 0; (unsigned) j < rows; j++) {
        for (int i = 0; (unsigned) i < columns; i++) {
            if (lista[i][j] == 1) {
                // 1 si es muro
                QLabel *imgLadrillo = new QLabel(this);
                imgLadrillo->setPixmap(ladrillo);                
                layout->addWidget(imgLadrillo, j, i, Qt::AlignHCenter);
                imgLadrillo->setVisible(true);                
            } else if (lista[i][j] == 2) {
                // 2 si es el punto donde inicia Mario
                QLabel *img = new QLabel(this);
                img->setPixmap(mario);
                layout->addWidget(img, j, i, Qt::AlignHCenter);
                img->setVisible(true);
            } else if (lista[i][j] == 3) {
                // 3 si es una flor
                QLabel *imgFlor = new QLabel(this);
                imgFlor->setPixmap(flor);
                layout->addWidget(imgFlor, j, i, Qt::AlignHCenter);
                imgFlor->setVisible(true);
            } else if (lista[i][j] == 4) {
                // 4 si es una tortuga
                QLabel *imgTortuga = new QLabel(this);
                imgTortuga->setPixmap(tortuga);
                layout->addWidget(imgTortuga, j, i, Qt::AlignHCenter);
                imgTortuga->setVisible(true);
            } else if (lista[i][j] == 5) {
                // 5 si es la princesa
                layout->addWidget(imgPrincesa, j, i, Qt::AlignHCenter);
                imgPrincesa->setVisible(true);
            } else if (lista[i][j] == 0) {
                layout->addWidget(imgNull, j, i, Qt::AlignHCenter);
                imgNull->setVisible(true);
            }
        }
    }

    timer.start(1000);
    QLabel *img = new QLabel(this);
    img->setPixmap(mario);
    layout->addWidget(img, 4, 0, Qt::AlignHCenter);
    img->setVisible(true);
    timer.stop();

    this->setLayout(layout);
}

void Interfaz::dibujarCamino(string path, int filas, int columnas) {

//    for (int j = 0; (unsigned) j < filas; j++) {
//         for (int i = 0; (unsigned) i < columnas; i++) {
             timer.start(1000);
             qDebug()<<"cambiar la pos de mario";
             //img->setVisible(false);
 //            layout->addWidget(img, 0, 0, Qt::AlignHCenter);
 //            img->setVisible(true);
             timer.stop();
//         }
//     }
}

vector< vector<int> > Interfaz::leerArchivo(QString filePath) {
    QStringList lista, lista2;
    vector< vector<int> > listaArchivo;
    vector< int > listaFilasColumnas;
    int filas, columnas;
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Not open";
    }
    QTextStream in(&file);

    QString mfile = in.readAll();    
    lista = mfile.split("\n");
    filas = lista.length(); //número de filas para el tablero    

    QString aux = lista.first();
    lista2 = aux.split(" ");
    columnas = lista2.length(); //número de columnas para el tablero

    listaArchivo.assign(filas, vector<int>(columnas));
    listaArchivo.push_back(listaFilasColumnas);

    for (int j = 0; j < filas; j++) {
        QStringList listaAux;
        QString cadenaAux;
        cadenaAux = lista.at(j);        
        listaAux = cadenaAux.split(" ");

        for (int i = 0; i < columnas; i++) {
            QString first = listaAux.at(i);
            listaArchivo[i][j] = first.toInt();
        }
    }    

    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            cout << listaArchivo[j] [i] << "  ";
        }
        cout << endl;
    }

    file.close();

    return listaArchivo;
}
