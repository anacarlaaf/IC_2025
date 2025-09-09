#include <bits/stdc++.h>
#define int long long
using namespace std;

const int oo = 1e16;
struct bucket_2lvl
{
    vector<list<pair<int, int>>> b;
    vector<list<int>> blb;

    int nbuckets = -1;
    int ai = 0, aj = 0, r = 0, sz = 0, c = 0;
    bucket_2lvl(int c_)
    {
        c = c_;
        // c = 1e5;
        nbuckets = sqrt(c + 1) + 1;

        b.assign(nbuckets, {});
        blb.assign(nbuckets, {});
    };

    void clear()
    {
        ai = 0, aj = 0, r = 0, sz = 0;
        for (auto &l : b)
            l.clear();
        for (auto &l : blb)
            l.clear();
    }

    void insert(int u, int du, int w)
    {
        // assert(w <= c);
        int pi = du / nbuckets % nbuckets;
        int pj = du % nbuckets;

        if (pi != ai)
            b[pi].push_back({u, pj});
        else
            blb[pj].push_back(u);

        sz++;
    }

    void update()
    {
        while (aj < nbuckets && blb[aj].size() == 0)
            aj++;
        if (aj < nbuckets)
            return;

        int bg = ai;
        do
        {
            ai++;
            if (ai == nbuckets)
                ai = 0, r++;

            if (b[ai].size())
            {

                aj = nbuckets;
                for (const auto [x, pos] : b[ai])
                {
                    blb[pos].push_back(x);
                    if (pos < aj)
                        aj = pos;
                }

                b[ai].clear();

                return;
            }
        } while (ai != bg);

        assert(false);
    }

    pair<int, int> extract_min()
    {
        update();

        int u = blb[aj].front();
        int du = r * nbuckets * nbuckets + ai * nbuckets + aj; // check this
        blb[aj].pop_front();
        sz--;

        return {du, u};
    }

    bool empty()
    {
        return sz == 0;
    }
};

void init_dijkstra(auto &d, auto &p, bucket_2lvl &q, const int n, const int s)
{
    d = vector<int>(n, oo);
    p = vector<int>(n, -1);
    d[s] = 0;
    q.clear();
    q.insert(s, 0, 0);
}

void dijkstra(const auto &adj, auto &d, auto &p, bucket_2lvl &q)
{
    while (!q.empty())
    {
        auto [du, u] = q.extract_min();
        if (d[u] < du)
            continue;

        for (auto [v, w] : adj[u])
        {
            if (d[v] > d[u] + w)
            {
                p[v] = u;
                d[v] = d[u] + w;
                q.insert(v, d[v], w);
            }
        }
    }
};

int32_t main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 2);
    while (m--)
    {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        adj[a].push_back({b, w});
    }
    vector<int> d(n), p(n);
    bucket_2lvl pq(1e5);
    init_dijkstra(d, p, pq, n, 0);
    dijkstra(adj, d, p, pq);
    for (int i = 0; i < n; i++)
        cout << d[i] << " ";
    cout << endl;
}