/*
* CARLOS FELIPE MONTOYA - 1535038
* DIANA MELISSA MILLARES - 1526062
* VICTOR HUGO ORTEGA - 1532342
*/

#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <queue>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include "nodo.h"

using namespace std;
typedef long long int64;
typedef unsigned long long uint64;
#define MURO 1
#define MARIO 2
#define FLOR 3
#define TORTUGA 4
#define PEACH 5

class busqueda{
public:
    vector< vector<int> > nodosVisitados;
    vector< vector<int> > tablero;
    vector< pair< pair<int,int> ,int > > camino;
    queue <nodo> cola;
    stack <nodo> pila;
    priority_queue <nodo> colaDePrioridad;
    int filas;
    int columnas;
    int xInicial;
    int yInicial;
    int xFinal;
    int yFinal;
    int nodosExpandidos;
    int profundidadDelArbol;
    double tiempoTotal;
    busqueda(int filas, int columnas, vector< vector<int> > tablero, int xInicial, int yInicial, int xFinal, int yFina);
    uint64 getTimeMs64();
    void obtenerCamino(nodo * nodoCamino);
    nodo expandirInformada(int xNodo, int yNodo, nodo aExpandir);
    nodo expandirNoInformada(int xNodo, int yNodo, nodo aExpandir);
    vector< pair<pair<int,int>,int> > amplitud();
    vector< pair<pair<int,int>,int> > profundidad();
    vector< pair<pair<int,int>,int> > costoUniforme();
    vector< pair<pair<int,int>,int> > avara();
    vector< pair<pair<int,int>,int> > aEstrella();
};


#endif /* BUSQUEDA_H */

