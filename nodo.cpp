/**
 * @authors
 * Melissa Millares
 * Felipe Montoya
 * Victor Hugo Ortega Gomez
 */

#include "nodo.h"

Nodo::Nodo(){

}

Nodo::Nodo(int estado[]){

    accion = "";
    coste = 0;
    this->estado[] = estado[];
    padre = NULL;
}

Nodo::Nodo(Nodo nodo, string accion){

    this->accion = accion;
    coste = nodo.getCoste();
    estado[];//determinarEstado(nodo.getEstado(), accion);
    padre = nodo;
}

int Nodo::getCoste() {
    return coste;
}

int Nodo::getEstado(){
    return punteroEstado;
}

void Nodo::determinarEstado(int estado[], string accion){

    if (accion) {

    } else if(){

    } else if(){

    } else if(){

    }
}
