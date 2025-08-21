#include <bits/stdc++.h>
#define int long long int

using namespace std;

const int INF = 10e15;
const int maxn = 1e5+2;
vector<pair<int, int>> adjacencias[maxn];
int distancia[maxn];

void dial(int origem, int pesoMax)
{
    vector<int> buckets[pesoMax];
    buckets[0].push_back(origem); // add origem no bucket 0
    distancia[origem] = 0;
    int cont = 0, aux = 0, verticeAtu; // bucket atual

    while (cont <= pesoMax)
    {
        aux = cont;
        while (buckets[cont].empty())
        { // até achar um bucket não vazio ou chegar no mesmo lugar
            cont = (cont + 1) % pesoMax;
            if (cont == aux) break;
        }
        if (buckets[cont].empty()) break;

        verticeAtu = buckets[cont].back();
        buckets[cont].pop_back();
        for (const auto [peso, ver] : adjacencias[verticeAtu])
        {
            int newDist = distancia[verticeAtu] + peso;
            if (newDist < distancia[ver])
            {
                buckets[newDist % pesoMax].push_back(ver); // atualizar posição nos buckets
                distancia[ver] = newDist;                   // atualiza distancia
            }
        }
    }
}

int32_t main()
{
    int qtdVertices, qtdArestas;
    cin >> qtdVertices >> qtdArestas;

    int a, b, c, pesoMax = -1;
    for (int i = 0; i < qtdArestas; i++)
    {
        cin >> a >> b >> c;
        pesoMax = max(pesoMax, c);
        adjacencias[a].push_back({c, b});
    }

    for(int i=1;i<=qtdVertices;i++) distancia[i] = INF;

    dial(1, (int)sqrt(pesoMax));

    for (int i = 1; i < qtdVertices + 1; i++) cout << distancia[i] << " ";
    cout << "\n";

    return 0;
}