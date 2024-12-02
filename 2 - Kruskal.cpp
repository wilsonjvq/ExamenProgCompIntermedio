//Algoritmo de Kruskal para el grafo
//Compilador en linea: https://www.onlinegdb.com/online_c++_compiler
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Arista {
    int origen, destino, peso;
};

bool compararAristas(Arista a, Arista b) {
    return a.peso < b.peso;
}

int encontrar(int nodo, vector<int>& padre) {
    if (padre[nodo] != nodo)
        padre[nodo] = encontrar(padre[nodo], padre); // Compresion de camino
    return padre[nodo];
}

void unir(int nodo1, int nodo2, vector<int>& padre, vector<int>& rango) {
    int raiz1 = encontrar(nodo1, padre);
    int raiz2 = encontrar(nodo2, padre);
    
    if (raiz1 != raiz2) {
        if (rango[raiz1] < rango[raiz2]) {
            padre[raiz1] = raiz2;
        } else if (rango[raiz1] > rango[raiz2]) {
            padre[raiz2] = raiz1;
        } else {
            padre[raiz2] = raiz1;
            rango[raiz1]++;
        }
    }
}

int main() {
    int nodos = 7;
    vector<Arista> aristas = {
        {1, 2, 10}, {1, 5, 6}, {2, 4, 2}, {2, 3, 5},
        {4, 1, 5}, {3, 4, 4}, {5, 6, 9}, {5, 7, 1},
        {6, 7, 8}, {6, 4, 3}, {6, 3, 2}
    };

    // Ordenar las aristas por peso
    sort(aristas.begin(), aristas.end(), compararAristas);

    vector<int> padre(nodos + 1), rango(nodos + 1, 0);
    for (int i = 1; i <= nodos; ++i)
        padre[i] = i;

    vector<Arista> mst;
    int peso_total = 0;

    for (Arista& arista : aristas) {
        if (encontrar(arista.origen, padre) != encontrar(arista.destino, padre)) {
            unir(arista.origen, arista.destino, padre, rango);
            mst.push_back(arista);
            peso_total += arista.peso;
        }
    }

    cout << "Arbol de expansion minima (Kruskal):\n";
    for (Arista& arista : mst) {
        cout << arista.origen << " - " << arista.destino << " = " << arista.peso << endl;
    }
    cout << "Peso total del MST: " << peso_total << endl;

    return 0;
}
