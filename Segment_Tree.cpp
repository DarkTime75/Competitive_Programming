#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int sz = 1;
    vector<int> arr;
    int NEUTRAL = 0;
    
    void init(int n) {
        while (sz < n) sz <<= 1;
        arr.resize(2 * sz, NEUTRAL);
    }

    int single(int v) {
        return v;
    }

    int merge(int a, int b) {
        return a + b;
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (rx-lx == 1) {
            if (lx < (int)a.size()) {
                arr[x] = single(a[lx]); 
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        arr[x] = merge(arr[2 * x + 1], arr[2 * x + 2]);
    }

    void build(vector<int>& a) {
        build(a, 0, 0, sz);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx-lx == 1) {
            arr[x] = single(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) set(i, v, 2 * x + 1, lx, m);
        else set(i, v, 2 * x + 2, m, rx);
        arr[x] = merge(arr[2 * x + 1], arr[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, sz);
    }

    int query(int l, int r, int x, int lx, int rx) {
        if (rx <= l || r <= lx) return NEUTRAL;
        if (l <= lx && rx <= r) return arr[x];
        int m = (lx + rx) / 2;
        int s1 = query(l, r, 2 * x + 1, lx, m);
        int s2 = query(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, sz);
    }
};

// gives answer in range [l, r)