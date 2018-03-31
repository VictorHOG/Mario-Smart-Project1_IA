#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <list>
#include <queue>
#include <stack>

#include "nodo.h"
#include "mariosmart.h"

class Busqueda
{
public:
    Busqueda();
    Nodo amplitud(int estado[]);
    Nodo profundidad(int estado[]);
    Nodo costeUniforme(int estado[]);
    Nodo avara();
    Nodo aEstrella();

    bool isInList(list lista, int estado[]);
    bool isInQueue(queue cola, int estado[]);
    bool isInStack(stack pila, int estado[]);

private:

    MarioSmart problema;
};

#endif // BUSQUEDA_H
