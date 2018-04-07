/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   busqueda.h
 * Author: invitado
 *
 * Created on 5 de abril de 2018, 06:33 PM
 */

#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <queue>
#include <vector>
#include <stack>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "nodo.h"
using namespace std;
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
    busqueda(int filas, int columnas, vector< vector<int> > tablero, int xInicial, int yInicial, int xFinal, int yFina);
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

