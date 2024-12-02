//Algoritmo de dijkstra para el grafo
//Compilador en linea: https://www.onlinegdb.com/online_c++_compiler
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int inicio, vector<vector<pair<int, int>>>& grafo, vector<int>& distancias) {
    int n = grafo.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distancias[inicio] = 0;
    pq.push({0, inicio}); // {distancia, nodo}
    
    while (!pq.empty()) {
        int distancia_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();
        
        if (distancia_actual > distancias[nodo_actual])
            continue;

        for (auto& vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            int peso_arista = vecino.second;
            
            if (distancias[nodo_actual] + peso_arista < distancias[nodo_vecino]) {
                distancias[nodo_vecino] = distancias[nodo_actual] + peso_arista;
                pq.push({distancias[nodo_vecino], nodo_vecino});
            }
        }
    }
}

int main() {
    int nodos = 7;
    vector<vector<pair<int, int>>> grafo(nodos + 1);
    
    // Definir el grafo dirigido con las distancias
    grafo[1].push_back({2, 10});
    grafo[1].push_back({5, 6});
    grafo[2].push_back({4, 2});
    grafo[2].push_back({3, 5});
    grafo[4].push_back({1, 5});
    grafo[3].push_back({4, 4});
    grafo[5].push_back({6, 9});
    grafo[5].push_back({7, 1});
    grafo[6].push_back({7, 8});
    grafo[6].push_back({4, 3});
    grafo[6].push_back({3, 2});
    
    vector<int> distancias(nodos + 1, INF);

    dijkstra(1, grafo, distancias);

    for (int i = 1; i <= nodos; ++i) {
        cout << "Distancia minima desde el Nodo 1 hacia el Nodo " << i << ": " << (distancias[i] == INF ? -1 : distancias[i]) << endl;
    }

    return 0;
}