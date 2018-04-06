/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nodo.h
 * Author: invitado
 *
 * Created on 5 de abril de 2018, 06:19 PM
 */

#ifndef NODO_H
#define NODO_H

#include <cstdio>

class nodo{
public:
    nodo();
    int posX, posY;
    int costo, costoAux;
    int profundidad;
    bool flor;
    nodo * padre;
    bool operator < (const nodo &B) const;
    nodo operator = (const nodo &B);
};

#endif /* NODO_H */

