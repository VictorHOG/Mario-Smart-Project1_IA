/*
* CARLOS FELIPE MONTOYA - 1535038
* DIANA MELISSA MILLARES - 1526062
* VICTOR HUGO ORTEGA - 1532342
*/

#include "nodo.h"

nodo::nodo() {
    costo = profundidad = posX = posY = costoAux = 0;
    flor = false;
    padre = NULL;
}

bool nodo::operator <(const nodo& B) const{
    return costo > B.costo;
}

nodo nodo::operator =(const nodo &B){
    this->posX = B.posX;
    this->posY = B.posY;
    this->padre = B.padre;
    this->profundidad = B.profundidad;
    this->costoAux = B.costoAux;
    this->costo = B.costo;
    this->flor = B.flor;

    return B;
}

