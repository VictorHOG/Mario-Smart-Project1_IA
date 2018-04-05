#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <QWidget>
#include <QLabel>
#include <QFile>
#include <vector>
#include <QTimer>

using namespace std;

class Interfaz: public QWidget {
    Q_OBJECT

public:
    Interfaz(QString path);
    vector< vector<int> > leerArchivo(QString filePath);
    void dibujarTablero(vector< vector<int> > lista);
    void dibujarCamino(string path, int filas, int columnas);

private:
    QTimer timer;
};

#endif // INTERFAZ_H
