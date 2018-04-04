#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <QWidget>
#include <QLabel>
#include <QFile>
#include <vector>

using namespace std;

class Interfaz: public QWidget {
    Q_OBJECT

public:
    Interfaz(QString path);
    vector< vector<int> > leerArchivo(QString filePath);
    void dibujarTablero(vector< vector<int> > lista);
};

#endif // INTERFAZ_H
