#include <bits/stdc++.h>
using namespace std;

class DSU {
    int n;
    vector<int> par, size;
  public:
    DSU(int n) {
      size.resize(n + 1, 1);
      par.resize(n + 1);
      iota(par.begin(), par.end(), 0);
    }

    int find(int u) {
      if (par[u] == u) return u;
      return par[u] = find(par[u]);
    }

    void uni(int u, int v) {
      int pu = find(u), pv = find(v);
      if (pu == pv) return;

      if (size[pu] > size[pv]) {
        par[pv] = pu;
        size[pu] += size[pv];
      } else {
        par[pu] = pv;
        size[pv] += size[pu];
      }
    }
  
    int get(int u) {
      return size[find(u)];
    }

    bool is(int u, int v) {
      return find(u) == find(v);
    }
};