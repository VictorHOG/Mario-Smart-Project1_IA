/*
* CARLOS FELIPE MONTOYA - 1535038
* DIANA MELISSA MILLARES - 1526062
* VICTOR HUGO ORTEGA - 1532342
*/

#include "busqueda.h"

busqueda::busqueda(int filas, int columnas, vector< vector<int> > tablero, int xInicial, int yInicial, int xFinal, int yFinal){
    this->filas = filas;
    this->columnas = columnas;
    this->tablero = tablero;
    this->xInicial = xInicial;
    this->yInicial = yInicial;
    this->xFinal = xFinal;
    this->yFinal = yFinal;
    nodosExpandidos = 0;
    profundidadDelArbol = 0;
    tiempoTotal = 0.0;
    nodosVisitados.assign(filas,vector<int>(columnas,0));
    camino.clear();
}

uint64 busqueda::getTimeMs64(){
    FILETIME ft;
    LARGE_INTEGER li;

    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;

    uint64 ret = li.QuadPart;
    ret -= 116444736000000000LL;
    ret /= 10000;

    return ret;
}

void busqueda::obtenerCamino(nodo * nodoCamino){
    pair< pair<int,int> , int > temp; //asignar la dir al caminoS
    temp.first.first = nodoCamino->posX;
    temp.first.second = nodoCamino->posY;
    temp.second = nodoCamino->flor;
    
    if(nodoCamino->padre == NULL){
        camino.push_back(temp);
        return;
    }
    
    obtenerCamino(nodoCamino->padre);
    camino.push_back(temp);
}

nodo busqueda::expandirInformada(int xNodo, int yNodo, nodo aExpandir){
    if(tablero[xNodo][yNodo] != PEACH) nodosVisitados[xNodo][yNodo] += aExpandir.flor + 1;
    nodo hijo;
    hijo.posX = xNodo;
    hijo.posY = yNodo;
    hijo.padre = new nodo(aExpandir);
    hijo.profundidad = aExpandir.profundidad + 1;
    hijo.costo = aExpandir.costo + 1;
    hijo.flor = aExpandir.flor;
    if(tablero[xNodo][yNodo] == TORTUGA && hijo.flor == false){
        hijo.costo += 7;
    }
    return hijo;
}

nodo busqueda::expandirNoInformada(int xNodo, int yNodo, nodo aExpandir){
    if(tablero[xNodo][yNodo] != PEACH) nodosVisitados[xNodo][yNodo] += aExpandir.flor + 1;
    nodo hijo;
    hijo.posX = xNodo;
    hijo.posY = yNodo;
    hijo.padre = new nodo(aExpandir);
    hijo.profundidad = aExpandir.profundidad + 1;
    hijo.costoAux = aExpandir.costoAux +1;
    hijo.flor = aExpandir.flor;
    if(tablero[xNodo][yNodo] == TORTUGA && hijo.flor == false){
        hijo.costoAux  += 7;
    }
    return hijo;
}

bool busqueda::visitado(int xNodo,int yNodo, nodo * aExpandir, bool flor){
    //printf("HOLI ESTOY EN %d %d\n", aExpandir->posX, aExpandir->posY);
    if(aExpandir->padre == NULL){
        if(xNodo == aExpandir->posX && yNodo == aExpandir->posY && aExpandir->flor == flor){
            return true;
        }else{
            return false;
        }
    }

    if(xNodo == aExpandir->posX && yNodo == aExpandir->posY && aExpandir->flor == flor){
        return true;
    }else{
        return visitado(xNodo,yNodo,aExpandir->padre, flor);
    }
}

vector< pair<pair<int,int>,int> > busqueda::amplitud(){
    camino.clear();
    uint64 tiempo = getTimeMs64();
    nodosExpandidos = profundidadDelArbol = 0;
    nodo inicial;
    inicial.posX = xInicial;
    inicial.posY = yInicial;
    cola.push(inicial);
    nodosVisitados[xInicial][yInicial] = 1;
    nodosExpandidos++;
    int soluciones = 0;
    while(!cola.empty()){
        nodo aExpandir = cola.front();
        profundidadDelArbol = max(profundidadDelArbol,aExpandir.profundidad);
        int xNodo, yNodo;
        xNodo = aExpandir.posX;
        yNodo = aExpandir.posY;
        
        if(tablero[xNodo][yNodo] == PEACH){
            break;
        }
        if(tablero[xNodo][yNodo] == FLOR){
            aExpandir.flor = true;
        }
        
        cola.pop();

        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            if(tablero[xNodo-1][yNodo] == PEACH) soluciones++;
            nodo hijo;
            hijo = expandirInformada(xNodo-1,yNodo,aExpandir);
            cola.push(hijo);
            nodosExpandidos++;
        }
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO && nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            if(tablero[xNodo+1][yNodo] == PEACH) soluciones++;
            nodo hijo;
            hijo = expandirInformada(xNodo+1,yNodo,aExpandir);
            cola.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo-1 >= 0 && tablero[xNodo][yNodo-1] != MURO && nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
            if(tablero[xNodo][yNodo-1] == PEACH) soluciones++;
            nodo hijo;
            hijo = expandirInformada(xNodo,yNodo-1,aExpandir);
            cola.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo+1 < columnas && tablero[xNodo][yNodo+1] != MURO && nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            if(tablero[xNodo][yNodo+1] == PEACH) soluciones++;
            nodo hijo;
            hijo = expandirInformada(xNodo,yNodo+1,aExpandir);
            cola.push(hijo);
            nodosExpandidos++;
        }
    }
    if(cola.size() > 0){
        obtenerCamino(&cola.front());
        cout << "Cantidad de soluciones " << soluciones << endl;
        while(!cola.empty()) cola.pop();
    }else{
        cout << "La princesa no fue rescatada" << endl;
    }
    nodosVisitados.assign(filas,vector<int>(columnas,0));
    return camino;
}

vector< pair<pair<int,int>,int> > busqueda::profundidad(){
    camino.clear();
    uint64 tiempo = getTimeMs64();
    nodosExpandidos = profundidadDelArbol = 0;
    nodo inicial;
    inicial.posX = xInicial;
    inicial.posY = yInicial;
    pila.push(inicial);
    nodosVisitados[xInicial][yInicial] = 1;
    nodosExpandidos++;
    while(!pila.empty()){
        nodo aExpandir = pila.top();
        profundidadDelArbol = max(profundidadDelArbol,aExpandir.profundidad);
        int xNodo, yNodo;
        xNodo = aExpandir.posX;
        yNodo = aExpandir.posY;
        
        if(tablero[xNodo][yNodo] == PEACH){
            break;
        }
        if(tablero[xNodo][yNodo] == FLOR){
            aExpandir.flor = true;
        }
        
        pila.pop();
        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo-1,yNodo,aExpandir);
            pila.push(hijo);
            nodosExpandidos++;
            hijo.izq++;
        }
        
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO  && nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo+1,yNodo,aExpandir);
            pila.push(hijo);
            nodosExpandidos++;
            hijo.der++;
        }
        if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != MURO  && nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo,yNodo-1,aExpandir);
            pila.push(hijo);
            nodosExpandidos++;
            hijo.aba++;
        }
        if(yNodo + 1 < columnas && tablero[xNodo][yNodo+1] != MURO  && nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo,yNodo+1,aExpandir);
            pila.push(hijo);
            nodosExpandidos++;
            hijo.arr++;
        }
    }
    //printf("Tiempo total de ejecución: %.10lf\n", (double)(clock() - tiempo)/CLOCKS_PER_SEC);
    if(pila.size() > 0){
        obtenerCamino(&pila.top());
        while(!pila.empty()) pila.pop();
    }else{
        printf("La princesa no fue rescatada\n");
    }
    nodosVisitados.assign(filas,vector<int>(columnas,0));
    return camino;
}

vector< pair<pair<int,int>,int> > busqueda::costoUniforme(){
    camino.clear();
    uint64 tiempo = getTimeMs64();
    nodosExpandidos = profundidadDelArbol = 0;
    nodo inicial;
    inicial.posX = xInicial;
    inicial.posY = yInicial;
    colaDePrioridad.push(inicial);
    nodosVisitados[xInicial][yInicial] = 1;
    nodosExpandidos++;
    while(!colaDePrioridad.empty()){
        nodo aExpandir = colaDePrioridad.top();
        profundidadDelArbol = max(profundidadDelArbol,aExpandir.profundidad);
        int xNodo, yNodo;
        xNodo = aExpandir.posX;
        yNodo = aExpandir.posY;
        
        if(tablero[xNodo][yNodo] == PEACH){
            break;
        }
        if(tablero[xNodo][yNodo] == FLOR){
            aExpandir.flor = true;
        }
        
        colaDePrioridad.pop();
        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo-1,yNodo,aExpandir);
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO  && nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo+1,yNodo,aExpandir);
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != MURO  && nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo,yNodo-1,aExpandir);
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo + 1 < columnas && tablero[xNodo][yNodo+1] != MURO  && nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            nodo hijo;
            hijo = expandirInformada(xNodo,yNodo+1,aExpandir);
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
    }
    tiempoTotal = ((double)getTimeMs64() - tiempo)/10000;
    cout << setprecision(20);
    cout << fixed;
    cout << "El tiempo de ejecucion es : " << tiempoTotal << endl;
    cout << "El tiempo actual es : " << getTimeMs64() << endl;
    cout << "El tiempo antes de ejecucin es : " << tiempo << endl;
    if(colaDePrioridad.size() > 0){
        nodo solucion = colaDePrioridad.top();
        obtenerCamino(&solucion);
        while(!colaDePrioridad.empty()) colaDePrioridad.pop();
    }else{
        printf("La princesa no fue rescatada\n");
    }
    nodosVisitados.assign(filas,vector<int>(columnas,0));
    return camino;
}

vector< pair<pair<int,int>,int> > busqueda::avara(){
    camino.clear();
    uint64 tiempo = getTimeMs64();
    nodosExpandidos = profundidadDelArbol = 0;
    nodo inicial;
    inicial.posX = xInicial;
    inicial.posY = yInicial;
    int posTortugax=0;
    int posTortugay=0;
    int contador =0;
    colaDePrioridad.push(inicial);
    nodosVisitados[xInicial][yInicial] = 1;
    nodosExpandidos++;
    while(!colaDePrioridad.empty()){
        nodo aExpandir = colaDePrioridad.top();
        profundidadDelArbol = max(profundidadDelArbol,aExpandir.profundidad);
        int xNodo, yNodo;
        xNodo = aExpandir.posX;
        yNodo = aExpandir.posY;
        
        if(tablero[xNodo][yNodo] == PEACH){
            break;
        }
        if(tablero[xNodo][yNodo] == FLOR){
            aExpandir.flor = true;
        }
     /*   if (tablero[xNodo][yNodo] == TORTUGA && contador==0){
            posTortugax = xNodo;
            posTortugay = yNodo;
            contador++;
        }*/

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                if (tablero[i][j] == TORTUGA && contador==0){
                    posTortugax = i;
                    posTortugay = j;
                    contador++;

                }
            }
        }

        cout << "tortuga pos x" << posTortugax << "  pos y  " << posTortugay<< endl;
        
        colaDePrioridad.pop();
        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo-1,yNodo,aExpandir);
          //  hijo.costo = abs((xNodo-1) - xFinal) + abs(yNodo - yFinal);
            hijo.costo = abs((xNodo-1) - posTortugax) + abs(yNodo - posTortugay);
            cout << "posición mario     posx: " << xNodo-1 << "posy: " <<  yNodo << endl;
            cout << "heuristica:    "  << hijo.costo<< endl;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO  && nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo+1,yNodo,aExpandir);
          //  hijo.costo = abs((xNodo+1) - xFinal) + abs(yNodo - yFinal);
            hijo.costo = abs((xNodo+1) - posTortugax) + abs(yNodo - posTortugay);
            cout << "posición mario     posx: " << xNodo+1 << "posy: " <<  yNodo << endl;
            cout << "heuristica:    "  << hijo.costo<< endl;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != MURO  && nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo,yNodo-1,aExpandir);
          //  hijo.costo = abs(xNodo - xFinal) + abs((yNodo-1) - yFinal);
            hijo.costo = abs(xNodo - posTortugax) + abs((yNodo-1) - posTortugay);
            cout << "posición mario     posx: " << xNodo << "posy: " <<  yNodo-1 << endl;
            cout << "heuristica:    "  << hijo.costo<< endl;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo + 1 < columnas && tablero[xNodo][yNodo+1] != MURO  && nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo,yNodo+1,aExpandir);
         //   hijo.costo = abs(xNodo - xFinal) + abs((yNodo+1) - yFinal);
            hijo.costo = abs(xNodo - posTortugax) + abs((yNodo+1) - posTortugay);
            cout << "posición mario     posx: " << xNodo << "posy: " <<  yNodo+1 << endl;
            cout << "heuristica:    "  << hijo.costo<< endl;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
    }
    //printf("Tiempo total de ejecución: %.10lf\n", (double)(clock() - tiempo)/CLOCKS_PER_SEC);
    if(colaDePrioridad.size() > 0){
        nodo solucion = colaDePrioridad.top();
        obtenerCamino(&solucion);
        while(!colaDePrioridad.empty()) colaDePrioridad.pop();
    }else{
        printf("La princesa no fue rescatada\n");
    }
    nodosVisitados.assign(filas,vector<int>(columnas,0));
    return camino;
}

vector< pair<pair<int,int>,int> > busqueda::aEstrella(){
    camino.clear();
    uint64 tiempo = getTimeMs64();
    nodosExpandidos = profundidadDelArbol = 0;
    nodo inicial;
    inicial.posX = xInicial;
    inicial.posY = yInicial;
    colaDePrioridad.push(inicial);
    nodosVisitados[xInicial][yInicial] = 1;
    nodosExpandidos++;
    while(!colaDePrioridad.empty()){
        nodo aExpandir = colaDePrioridad.top();
        profundidadDelArbol = max(profundidadDelArbol,aExpandir.profundidad);
        int xNodo, yNodo;
        xNodo = aExpandir.posX;
        yNodo = aExpandir.posY;
        if(tablero[xNodo][yNodo] == PEACH){
            break;
        }
        if(tablero[xNodo][yNodo] == FLOR){
            aExpandir.flor = true;
        }
        
        colaDePrioridad.pop();
        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo-1,yNodo,aExpandir);
            hijo.costo = abs((xNodo-1) - xFinal) + abs(yNodo - yFinal) + hijo.costoAux;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO  && nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo+1,yNodo,aExpandir);
            hijo.costo = abs((xNodo+1) - xFinal) + abs(yNodo - yFinal) + hijo.costoAux;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != MURO  && nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo,yNodo-1,aExpandir);
            hijo.costo = abs(xNodo - xFinal) + abs((yNodo-1) - yFinal) + hijo.costoAux;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
        if(yNodo + 1 < columnas && tablero[xNodo][yNodo+1] != MURO  && nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            nodo hijo;
            hijo = expandirNoInformada(xNodo,yNodo+1,aExpandir);
            hijo.costo = abs(xNodo - xFinal) + abs((yNodo+1) - yFinal) + hijo.costoAux;
            colaDePrioridad.push(hijo);
            nodosExpandidos++;
        }
    }
    tiempoTotal = ((double)getTimeMs64() - tiempo)/10000;
    cout << setprecision(20);
    cout << fixed;
    cout << "El tiempo de ejecucion es : " << tiempoTotal << endl;
    cout << "El tiempo actual es : " << getTimeMs64() << endl;
    cout << "El tiempo antes de ejecucin es : " << tiempo << endl;
    if(colaDePrioridad.size() > 0){
        nodo solucion = colaDePrioridad.top();
        obtenerCamino(&solucion);
        while(!colaDePrioridad.empty()) colaDePrioridad.pop();
    }else{
        printf("La princesa no fue rescatada\n");
    }
    nodosVisitados.assign(filas,vector<int>(columnas,0));
    return camino;
}
