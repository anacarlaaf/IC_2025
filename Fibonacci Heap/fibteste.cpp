#include<boost/heap/fibonacci_heap.hpp>

#include <bits/stdc++.h> 
#define int long long int
const int INF = 10e15;

using namespace std;

void dijkstra(int origem, vector<int> &distancias, vector<vector<pair<int,int>>> &adjacencias){
    boost::heap::fibonacci_heap<pair<int,int>, boost::heap::compare<std::greater<pair<int,int>>>> q;
    distancias[origem] = 0;
    q.push({0,origem});

    while (!q.empty()){
        int distAtu = q.top().first;
        int verticeAtu = q.top().second;
        q.pop();

        if (distAtu <= distancias[verticeAtu]){
            for (const auto& vizinho : adjacencias[verticeAtu]){
                int distNova = vizinho.first;
                int verticeNovo = vizinho.second;
                int distCalc = distNova + distAtu;

                if (distCalc < distancias[verticeNovo]){
                    distancias[verticeNovo] = distCalc;
                    q.push({distCalc, verticeNovo});
                }
            }
        }
    }
}

int32_t main(){
    int qtdVertices, qtdArestas;
    cin >> qtdVertices >> qtdArestas;
    
    vector<vector<pair<int,int>>> adjacencias(qtdVertices+1);

    int a, b, c;
    for(int i=0; i<qtdArestas; i++){
        cin >> a >> b >> c;
        adjacencias[a].push_back({c,b});
    }

    vector<int> distancias(qtdVertices+1, INF);

    dijkstra(1, distancias, adjacencias);

    for (int i=1; i<qtdVertices+1; i++){
        cout << distancias[i] << " ";
    }
    cout << "\n";

    return 0;
}