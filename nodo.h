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
    Nodo(int estado[]);
    Nodo(Nodo nodo, string accion);

    void determinarEstado(int estado[], string accion);

    int getCoste();
    int *getEstado();

private:
    string accion;
    int coste;
    int estado[];
    int *punteroEstado;
    Nodo *padre;

};

#endif // NODO_H
