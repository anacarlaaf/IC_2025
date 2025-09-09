#include <bits/stdc++.h> // alterar depois pra só incluir bibliotecas úteis

using namespace std;
using ll = long long;

const ll INFdist = 2e15 + 10;
const ll INFpeso = 2e15 + 10;
const ll maxn = 1e5 + 2;
vector<pair<ll, ll>> adj[maxn];
ll dist[maxn];
ll maxC, sqrtC, at, ab;
vector<pair<ll, ll>> Bb[31624], Bt[31624]; // 31622 == um pouco mais da raiz de 1e9

void inserir(pair<ll, ll> v)
{
    ll i = (v.second / sqrtC) % sqrtC;
    ll j = v.second % sqrtC;

    if (i == at)
        Bb[j].push_back(v);
    else
        Bt[i].push_back(v);
}

void two_level(ll st)
{
    dist[st] = 0;
    Bb[0].push_back({st, 0});
    ll cont = 0, cont2;

    while (true)
    { // enquanto houver vértices em algum lugar
        for(;cont<sqrtC;cont++){
            if(!Bb[cont].empty()) break;
        }
        // se não encontra, Expand (encontra um top-bucket não-vazio e distribui nos bottom-buckets)
        if (Bb[cont].empty())
        {
            cont2 = at;
            while (Bt[cont2].empty() && cont2 != at)
            {
                cont2 = (cont2 + 1) % sqrtC;
            }
            if (Bt[cont2].empty())
                return;

            at = cont2+1;

            auto temp = Bt[cont2]; // cópia dos que serão redistribuidos
            Bt[cont2].clear();     // limpa pra não dar loop infinito

            //int minmod = -1;
            for (auto &elem : temp)
            {
                //minmod = min(minmod, (int)(elem.second%sqrtC));
                Bb[elem.second % sqrtC].push_back({elem});
            }
            cont = 0; //ajustar depois
            continue;
        }

        // se encontrar, relaxar os adjacentes
        ll v = Bb[cont].back().first;
        ll dv = Bb[cont].back().second;
        Bb[cont].pop_back();
        // if (dv > dist[v])
        //     continue; 

        for (auto [u, w] : adj[v])
        {
            ll novaDist = dist[v] + w;
            if (novaDist < dist[u])
            {
                dist[u] = novaDist;
                inserir({u, dist[u]}); // insere na estrutura
            }
        }
    }
}

int main()
{

    ll n, m, a, b, c;
    maxC = -INFpeso;
    cin >> n >> m;

    at = 0;
    for (ll i = 0; i <= n; i++)
        dist[i] = INFdist;

    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        maxC = max(maxC, c);
        adj[a].push_back({b, c});
    }

    sqrtC = sqrt(maxC + 1) + 1; // arredondar pra cima pra garantir
    two_level(1);

    for (ll i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }
    cout << "\n";

    return 0;
}