/**
 * @authors
 * Melissa Millares
 * Felipe Montoya
 * Victor Hugo Ortega Gomez
 */

#ifndef ARCHIVO_H
#define ARCHIVO_H

class Archivo
{
public:
    Archivo();
    void leerArchivo(string filePath);

    int getColumns();
    int getRows();

private:
    int colums;
    int rows;
    int posicionJugador[];
};

#endif // ARCHIVO_H
