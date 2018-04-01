#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>
#include <cstring>
#include <vector>
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
	
	//~nodo(){
	//	delete padre;
	//}
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
 				int filas, int columnas, int xObjetivo, int yObjetivo, int xInicial, int yInicial){
	int nodosExpandidos, profundidadDelArbol;
	nodosExpandidos = profundidadDelArbol = 0;
	queue<nodo> cola;
	nodo inicial;
	inicial.posX = xInicial;
	inicial.posY = yInicial;
	cola.push(inicial);
	nodosVisitados[xInicial][yInicial] = 1;
	nodosExpandidos = 0;
	while(!cola.empty()){
		nodo aExpandir = cola.front();
		profundidadDelArbol = max(profundidadDelArbol,aExpandir.profundidad);
		int xNodo, yNodo;
		xNodo = aExpandir.posX;
		yNodo = aExpandir.posY;
		if(xNodo == xObjetivo && yNodo == yObjetivo){
			break;
		}
		if(tablero[xNodo][yNodo] == FLOR){
			aExpandir.flor = true;
		}
		cola.pop();
		if(xNodo-1 >= 0 && tablero[xNodo-1][yNodo] != 1 && 
				nodosVisitados[xNodo-1][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo-1][yNodo] != 3){
			nodosVisitados[xNodo-1][yNodo] += aExpandir.flor + 1;
			nodo hijo;
			hijo.posX = xNodo-1;
			hijo.posY = yNodo;
			hijo.padre = new nodo(aExpandir);
			hijo.profundidad = aExpandir.profundidad + 1;
			hijo.costo = aExpandir.costo + 1;
			hijo.flor = aExpandir.flor;
			if(tablero[xNodo-1][yNodo] == 4 && hijo.flor == false){
				hijo.costo += 7;
			}
			nodosExpandidos++;
			cola.push(hijo);
		}
		if(xNodo+1 < filas && tablero[xNodo+1][yNodo] != 1  && 
				nodosVisitados[xNodo+11][yNodo] != aExpandir.flor + 1 && nodosVisitados[xNodo+1][yNodo] != 3){
			nodosVisitados[xNodo+1][yNodo] += aExpandir.flor + 1;
			nodo hijo;
			hijo.posX = xNodo+1;
			hijo.posY = yNodo;
			hijo.padre = new nodo(aExpandir);
			hijo.profundidad = aExpandir.profundidad + 1;
			hijo.flor = aExpandir.flor;
			hijo.costo = aExpandir.costo + 1;
			if(tablero[xNodo+1][yNodo] == 4 && hijo.flor == false){
				hijo.costo += 7;
			}
			nodosExpandidos++;
			cola.push(hijo);
		}
		
		if(yNodo - 1 >= 0 && tablero[xNodo][yNodo-1] != 1  && 
				nodosVisitados[xNodo][yNodo-1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo-1] != 3){
			nodosVisitados[xNodo][yNodo-1] += aExpandir.flor + 1;
			nodo hijo;
			hijo.posX = xNodo;
			hijo.posY = yNodo-1;
			hijo.padre = new nodo(aExpandir);
			hijo.profundidad = aExpandir.profundidad + 1;
			hijo.flor = aExpandir.flor;
			hijo.costo = aExpandir.costo + 1;
			if(tablero[xNodo][yNodo-1] == 4 && hijo.flor == false){
				hijo.costo += 7;
			}
			nodosExpandidos++;
			cola.push(hijo);
		}
		
		if(yNodo + 1 >= 0 && tablero[xNodo][yNodo+1] != 1  && 
				nodosVisitados[xNodo][yNodo+1] != aExpandir.flor + 1 && nodosVisitados[xNodo][yNodo+1] != 3){
			nodosVisitados[xNodo][yNodo+1] += aExpandir.flor + 1;
			nodo hijo;
			hijo.posX = xNodo;
			hijo.posY = yNodo+1;
			hijo.padre = new nodo(aExpandir);
			hijo.profundidad = aExpandir.profundidad + 1;
			hijo.costo = aExpandir.costo + 1;
			hijo.flor = aExpandir.flor;
			if(tablero[xNodo][yNodo+1] == 4 && hijo.flor == false){
				hijo.costo += 7;
			}
			nodosExpandidos++;
			cola.push(hijo);
		}
	}
	printf("El total de nodos expandidos es: %d\n", nodosExpandidos);
	printf("La profundidad del arbol es: %d\n", profundidadDelArbol);
	if(cola.size() > 0){
		printf("La princesa fue rescatada, el costo de la solucion es %d\n", cola.front().costo);
		printf("La solución al camino fue:\n");
		printPath(&cola.front());
	}else{
		printf("La princesa no fue rescatada\n");
	}
}

int main(int argc, char** argv) {
	freopen("Prueba1.txt","r",stdin);
	int filas, columnas, xObjetivo, yObjetivo, xInicial, yInicial;
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
			}else if(tablero [i][j] == PEACH){
				xObjetivo = i;
				yObjetivo = j;
			}
		}
	}
	
	amplitud(tablero,nodosVisitados,filas,columnas,xObjetivo,yObjetivo,xInicial,yInicial);
	
	return 0;
}
