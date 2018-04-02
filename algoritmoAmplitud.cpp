#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>
#include <cstring>
#include <vector>
#include <ctime>
using namespace std;
#define MURO 1
#define MARIO 2
#define FLOR 3
#define TORTUGA 4
#define PEACH 5

struct nodo{
    int posX, posY;
    int costo;
    int profundidad;
    bool flor;
    nodo * padre;

    nodo(){
	costo = profundidad = posX = posY = 0;
    	flor = false;
    	padre = NULL;
    }
    
    bool operator < (const nodo &B) const{
        return costo > B.costo;
    }
};

void printPath(nodo * aux){
    if(aux->padre == NULL){
    	printf("%d %d\n", aux->posX, aux->posY);
    	return;
    }
    printPath(aux->padre);
    printf("%d %d\n", aux->posX, aux->posY);
}

void amplitud(vector< vector<int> > tablero, vector< vector<int> > nodosVisitados,
                int filas, int columnas, int xInicial, int yInicial){
    clock_t tiempo = clock();
    int nodosExpandidos, profundidadDelArbol;
    nodosExpandidos = profundidadDelArbol = 0;
    queue<nodo> cola;
    nodo inicial;
    inicial.posX = xInicial;
    inicial.posY = yInicial;
    cola.push(inicial);
    nodosVisitados[xInicial][yInicial] = 1;
    nodosExpandidos++;
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
        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && 
                nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            nodosVisitados[xNodo-1][yNodo] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo-1;
            hijo.posY = yNodo;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.costo = aExpandir.costo + 1;
            hijo.flor = aExpandir.flor;
            if(tablero[xNodo-1][yNodo] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            cola.push(hijo);
        }
        
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO  &&
                nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            nodosVisitados[xNodo+1][yNodo] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo+1;
            hijo.posY = yNodo;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.flor = aExpandir.flor;
            hijo.costo = aExpandir.costo + 1;
            if(tablero[xNodo+1][yNodo] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            cola.push(hijo);
        }
        if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != MURO  && 
				nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
			nodosVisitados[xNodo][yNodo-1] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo;
            hijo.posY = yNodo-1;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.flor = aExpandir.flor;
            hijo.costo = aExpandir.costo + 1;
            if(tablero[xNodo][yNodo-1] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            cola.push(hijo);
        }
        if(yNodo + 1 < columnas && tablero[xNodo][yNodo+1] != MURO  &&
                nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            nodosVisitados[xNodo][yNodo+1] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo;
            hijo.posY = yNodo+1;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.costo = aExpandir.costo + 1;
            hijo.flor = aExpandir.flor;
            if(tablero[xNodo][yNodo+1] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            cola.push(hijo);
        }
    }
    printf("El total de nodos expandidos es: %d\n", nodosExpandidos);
    printf("La profundidad del arbol es: %d\n", profundidadDelArbol);
    printf("Tiempo total de ejecución: %.10lf\n", (double)(clock() - tiempo)/CLOCKS_PER_SEC);
    if(cola.size() > 0){
        printf("La princesa fue rescatada, el costo de la solucion es %d\n", cola.front().costo);
        printf("La solución al camino fue:\n");
        printPath(&cola.front());
    }else{
        printf("La princesa no fue rescatada\n");
    }
}

void profundidadSinCiclo(vector< vector<int> > tablero, vector< vector<int> > nodosVisitados,
                int filas, int columnas, int xInicial, int yInicial){
    clock_t tiempo = clock();
    int nodosExpandidos, profundidadDelArbol;
    nodosExpandidos = profundidadDelArbol = 0;
    stack<nodo> pila;
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
        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && 
                nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            nodosVisitados[xNodo-1][yNodo] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo-1;
            hijo.posY = yNodo;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.costo = aExpandir.costo + 1;
            hijo.flor = aExpandir.flor;
            if(tablero[xNodo-1][yNodo] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            pila.push(hijo);
        }
        
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO  &&
                nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            nodosVisitados[xNodo+1][yNodo] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo+1;
            hijo.posY = yNodo;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.flor = aExpandir.flor;
            hijo.costo = aExpandir.costo + 1;
            if(tablero[xNodo+1][yNodo] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            pila.push(hijo);
        }
        if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != MURO  && 
				nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
			nodosVisitados[xNodo][yNodo-1] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo;
            hijo.posY = yNodo-1;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.flor = aExpandir.flor;
            hijo.costo = aExpandir.costo + 1;
            if(tablero[xNodo][yNodo-1] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            pila.push(hijo);
        }
        if(yNodo + 1 < columnas && tablero[xNodo][yNodo+1] != MURO  &&
                nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            nodosVisitados[xNodo][yNodo+1] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo;
            hijo.posY = yNodo+1;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.costo = aExpandir.costo + 1;
            hijo.flor = aExpandir.flor;
            if(tablero[xNodo][yNodo+1] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            pila.push(hijo);
        }
    }
    printf("El total de nodos expandidos es: %d\n", nodosExpandidos);
    printf("La profundidad del arbol es: %d\n", profundidadDelArbol);
    printf("Tiempo total de ejecución: %.10lf\n", (double)(clock() - tiempo)/CLOCKS_PER_SEC);
    if(pila.size() > 0){
        printf("La princesa fue rescatada, el costo de la solucion es %d\n", pila.top().costo);
        printf("La solución al camino fue:\n");
        printPath(&pila.top());
    }else{
        printf("La princesa no fue rescatada\n");
    }
}

void costoUniforme(vector< vector<int> > tablero, vector< vector<int> > nodosVisitados,
                int filas, int columnas, int xInicial, int yInicial){
    clock_t tiempo = clock();
    int nodosExpandidos, profundidadDelArbol;
    nodosExpandidos = profundidadDelArbol = 0;
    priority_queue<nodo> colaDePrioridad;
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
        if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != MURO && 
                nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
            nodosVisitados[xNodo-1][yNodo] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo-1;
            hijo.posY = yNodo;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.costo = aExpandir.costo + 1;
            hijo.flor = aExpandir.flor;
            if(tablero[xNodo-1][yNodo] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            colaDePrioridad.push(hijo);
        }
        
        if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != MURO  &&
                nodosVisitados[xNodo+1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
            nodosVisitados[xNodo+1][yNodo] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo+1;
            hijo.posY = yNodo;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.flor = aExpandir.flor;
            hijo.costo = aExpandir.costo + 1;
            if(tablero[xNodo+1][yNodo] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            colaDePrioridad.push(hijo);
        }
        if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != MURO  && 
				nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
			nodosVisitados[xNodo][yNodo-1] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo;
            hijo.posY = yNodo-1;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.flor = aExpandir.flor;
            hijo.costo = aExpandir.costo + 1;
            if(tablero[xNodo][yNodo-1] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            colaDePrioridad.push(hijo);
        }
        if(yNodo + 1 < columnas && tablero[xNodo][yNodo+1] != MURO  &&
                nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
            nodosVisitados[xNodo][yNodo+1] += aExpandir.flor + 1;
            nodo hijo;
            hijo.posX = xNodo;
            hijo.posY = yNodo+1;
            hijo.padre = new nodo(aExpandir);
            hijo.profundidad = aExpandir.profundidad + 1;
            hijo.costo = aExpandir.costo + 1;
            hijo.flor = aExpandir.flor;
            if(tablero[xNodo][yNodo+1] == TORTUGA && hijo.flor == false){
                hijo.costo += 7;
            }
            nodosExpandidos++;
            colaDePrioridad.push(hijo);
        }
    }
    printf("El total de nodos expandidos es: %d\n", nodosExpandidos);
    printf("La profundidad del arbol es: %d\n", profundidadDelArbol);
    printf("Tiempo total de ejecución: %.10lf\n", (double)(clock() - tiempo)/CLOCKS_PER_SEC);
    if(colaDePrioridad.size() > 0){
        printf("La princesa fue rescatada, el costo de la solucion es %d\n", colaDePrioridad.top().costo);
        printf("La solución al camino fue:\n");
        nodo solucion = colaDePrioridad.top();
        printPath(&solucion);
    }else{
        printf("La princesa no fue rescatada\n");
    }
}

int main(int argc, char** argv) {
    freopen("Prueba2.txt","r",stdin);
    int filas, columnas, xInicial, yInicial;
    scanf("%d %d", &filas, &columnas);
    vector< vector<int> > tablero, nodosVisitados;
    tablero.assign(filas, vector<int>(columnas));
    nodosVisitados.assign(filas, vector<int>(columnas,0));
    	
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            scanf("%d", &tablero[i][j]);
            if(tablero[i][j] == MARIO){
                xInicial = i;
                yInicial = j;
            }
        }
    }
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            printf("%d  ", tablero[i][j]);
        }
        printf("\n");
    }
    amplitud(tablero,nodosVisitados,filas,columnas,xInicial,yInicial);
    costoUniforme(tablero,nodosVisitados,filas,columnas,xInicial,yInicial);
    profundidadSinCiclo(tablero,nodosVisitados,filas,columnas,xInicial,yInicial); 
    return 0;
}
