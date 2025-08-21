#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef struct blocks{
    set<pair<int,int>> d0;
    set<pair<int,int>> d1;
} blocks;

const int maxn = 1e5+2;
const int inf = 1e9;
set<int> S, W, P, U;
set<int> Wn[maxn], Un[maxn];
vector<int> F[maxn];
vector<pii> adj[maxn];
int k, n, M;
int d[maxn];
int dest[maxn];
int sub[maxn];
//int pai[maxn];

void dfs(int st, int pai = -1){  // fazer iterativa depois?
    sub[st] = 1;
    for (int i : F[st]){
        //if(i==pai) continue;
        dfs(i, st);
        sub[st] += sub[i];
    }
}

void initialize(int M, int B) {}

void dell(int a, int b) {}

void insert(int a, int b) {}

void split() {}

void batchPrepend() {}

void pull() {}

void findPivots(int bound){
    W.clear(); P.clear();
    W.insert(S.begin(), S.end());
    Wn[0].insert(S.begin(), S.end());

    for(int i=0;i<k;i++){
        Wn[0].clear();
        for(int u: Wn[i-1]){
            for(auto [v, w] : adj[u]){
                int nd = dest[u] + w;
                if(nd <= d[v]){
                    dest[v] = nd;
                    if(nd < bound) Wn[i].insert(v);
                }
            }
        }
        W.insert(Wn[i].begin(), Wn[i].end());
        if (W.size() > k*S.size()){
            P.insert(S.begin(), S.end());
            return;
        }
    }

    for(int u : W){
        for(auto [v, w] : adj[u]){
            if(W.count(v) && d[v] == d[u] + w) F[u].push_back(v);
        }
    }
    for(int u : S) {
        dfs(u);
        if(sub[u]>=k) P.insert(u);
    }
}

int baseCase(int B){
    Un[0].insert(S.end(), S.begin());
    priority_queue<pii, vector<pii>, greater<pii>> H;

    H.push({dest[*S.begin()], *S.begin()});
    while(!H.empty() && Un[0].size()< k+1){
        auto [u, p] = H.top(); H.pop();
        Un[0].insert(u);
        for(auto [v, w] : adj[u]){
            if(dest[u]+w<=dest[u] && dest[u]+w<B){
                dest[v] = dest[u] + w;
                H.push({v,dest[v]});
            }
        }
    }
    if(Un[0].size()<=k) {
        U.insert(Un[0].begin(), Un[0].end());
        return B;
    }
    else{
        int Bl = *max_element(dest, dest+n);
        for(int u : Un[0]){
            if(dest[u]<Bl) U.insert(u);
        }
        return Bl;
    }
}

int BMSSP(int l, int B){
    if (!l) return baseCase(B);
    findPivots(B);
    initialize(M, B); // M = pow(2,l-1)



}

int main(){
    k = floor(pow(log2(n),1/3));
    for(int i=0;i<=n;i++){
        d[i] = inf;
        dest[i] = inf;
    }
    return 0;
}