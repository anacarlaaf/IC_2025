#include<iostream>
#include<queue>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include <windows.h>
#include <cstdint>
#define int long long

using namespace std;

const int INF = 1e15;
const int MAXN = 1e7;
int distancias[MAXN];
vector<pair<int,int>> adjacencias[MAXN];

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void dijkstra(int origem){

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
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

    string filename = "USA-road-d_cleaned.csv";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return 1;
    }

    string line;

    getline(file, line);
    istringstream iss(line);
    int n, m;
    iss >> n >> m;

    while (getline(file, line)) {
        istringstream iss(line);
        int a, b, c;
        
        // Lê os 3 inteiros da linha
        if (iss >> a >> b >> c) {
            adjacencias[a].push_back({c,b});
            adjacencias[b].push_back({c,a});
        } else {
            cerr << "Formato inválido na linha: " << line << endl;
        }
    }

    file.close();

    for(int i=0;i<MAXN;i++) distancias[i] = INF;

    LARGE_INTEGER frequencia, inicio, fim;
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);
        dijkstra(1);
    QueryPerformanceCounter(&fim);
    double duracao = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequencia.QuadPart;
    
    cout << "Tempo de execucao (Binary Heap): " << duracao << " milissegundos" << "\n";

    cout << "1\n";
    return 0;
}