#include<bits/stdc++.h> // alterar depois pra só incluir bibliotecas úteis
 
using namespace std;
using ll = long long;
 
const ll INFdist = 1e15;
const int INFpeso = 1e9+10;
const int maxn = 1e5+2;
vector<pair<int,int>> adj[maxn];
ll dist[maxn];
int maxC, sqrtC, at, ab;
vector<pair<int,ll>> Bb[31624], Bt[31624]; // 31622 == um pouco mais da raiz de 1e9
 
void inserir(pair<int,ll> v){
    int i = (v.second/sqrtC) % sqrtC;
    int j = v.second % sqrtC;
    
    if(i==at) Bb[j].push_back(v);
    else Bt[i].push_back(v);
}
 
void two_level(int st){
    dist[st] = 0;
    Bb[0].push_back({st,0});
    int aux = 0, cont = 0, cont2;
 
    while(true){ // enquanto houver vértices em algum lugar
        aux = cont;
        while(Bb[cont].empty()){ // procura um bottom-bucket não-vazio
            cont = (cont+1) % sqrtC;
            if(cont == aux) break;
        }
 
         // se não encontra, Expand (encontra um top-bucket não-vazio e distribui nos bottom-buckets)
        if (Bb[cont].empty()){
            cont2 = at+1;
            while(Bt[cont2].empty() && cont2 != at){
                cont2 = (cont2+1) % sqrtC;
            }
            if (Bt[cont2].empty()) return;
 
            at = cont2;
 
            auto temp = Bt[cont2]; // cópia dos que serão redistribuidos
            Bt[cont2].clear(); // limpa pra não dar loop infinito
 
            for (auto &elem : temp) {
                Bb[elem.second % sqrtC].push_back({elem});
            }
            continue;
        }
 
        // se encontrar, relaxar os adjacentes
        int v = Bb[cont].back().first;
        Bb[cont].pop_back();
 
        for(auto [u, w] : adj[v]){
            ll novaDist = dist[v] + w;
            if (novaDist < dist[u]){
                dist[u] = novaDist;
                inserir({u, w}); //insere na estrutura
            }
        }
    }
}
 
int main(){
 
    int n, m, a, b, c;
    maxC = -INFpeso;
    cin >> n >> m;
    
    at = 0;
    for(int i=0;i<=n;i++) dist[i] = INFdist;
 
    for(int i=0;i<m;i++){
        cin >> a >> b >> c;
        maxC = max(maxC, c);
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
 
    sqrtC = sqrt(maxC+1);
    two_level(1);
 
    for(int i=1;i<=n;i++){
        cout << dist[i] << " ";
    } cout << "\n";
 
    return 0;
}