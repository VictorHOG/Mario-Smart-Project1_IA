/**
 * @authors
 * Melissa Millares
 * Felipe Montoya
 * Victor Hugo Ortega Gomez
 */

#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo
{
public:
    Nodo();
    Nodo crearNodo();
    void expandirNodo();

private:
    string accion;
    int coste;
    int estado[];
    Nodo padre;

};

#endif // NODO_H
