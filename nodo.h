/*
* CARLOS FELIPE MONTOYA - 1535038
* DIANA MELISSA MILLARES - 1526062
* VICTOR HUGO ORTEGA - 1532342
*/

#ifndef NODO_H
#define NODO_H

#include <cstdio>

class nodo{
public:
    nodo();
    int der,izq,arr,aba;
    int posX, posY;
    int costo, costoAux;
    int profundidad;
    bool flor;
    nodo * padre;
    bool operator < (const nodo &B) const;
    nodo operator =(const nodo &B);
};

#endif /* NODO_H */

