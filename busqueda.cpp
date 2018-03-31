/**
 * @authors
 * Melissa Millares
 * Felipe Montoya
 * Victor Hugo Ortega Gomez
 */

#include <string>
#include "busqueda.h"

using namespace std;

Busqueda::Busqueda(){

}

bool Busqueda::isInList(list lista, int estado[]){

}

bool Busqueda::isInQueue(queue cola, int estado[]){

}

bool Busqueda::isInStack(stack pila, int estado[]){

}

Nodo Busqueda::amplitud(int estado[]){

    Nodo nodoRaiz(int estado[]);

    queue <Nodo> cola;
    list <int[]> listaExplorada;
    list <string> acciones;
    list <string>::iterator i;

    cola.push(nodoRaiz);

    while (!cola.empty()) {

        Nodo nodo = cola.front();
        cola.pop();

        if (problema.esObjetivo(nodo.getEstado))
            Return nodo;

        listaExplorada.push_back(nodo.getEstado());

        acciones = problema.acciones(nodo.getEstado());

        for ( i = acciones.begin(); i =! acciones.end(); ++i) {

            Nodo hijo(nodo, *i);

            if (!isInList(listaExplorada, hijo.getEstado()) and
                    !isInQueue(cola, hijo.getEstado()))
                cola.push(hijo);

        }
    }

    return NULL;
}

Nodo Busqueda::costeUniforme(int estado[]){

    Nodo nodoRaiz(int estado[]);

    queue <Nodo> cola;
    list <int[]> listaExplorada;
    list <string> acciones;
    list <string>::iterator i;

    cola.push(nodoRaiz);

    while (!cola.empty()) {

        Nodo nodo = cola.front();
        cola.pop();

        if (problema.esObjetivo(nodo.getEstado))
            Return nodo;

        listaExplorada.push_back(nodo.getEstado());

        acciones = problema.acciones(nodo.getEstado());

        for ( i = acciones.begin(); i =! acciones.end(); ++i) {

            Nodo hijo(nodo, *i);

            if (!isInList(listaExplorada, hijo.getEstado()) and
                    !isInQueue(cola, hijo.getEstado()))
                cola.push(hijo);

        }
    }

    return NULL;
}

Nodo Busqueda::profundidad() {

}

Nodo Busqueda::avara() {

}

Nodo Busqueda::aEstrella(){

}
