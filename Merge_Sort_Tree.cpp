#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
    vector<vector<int>> tree;
    vector<vector<int>> pref;
    int sz = 1;
    void init(int n) {
        while (sz < n) sz <<= 1;
        tree.resize(2 * sz);
        pref.resize(2 * sz);
    }
    void build(int lx, int rx, int x, vector<int>& a) {
        if (rx - lx == 1) {
            if (lx < a.size()) {
                tree[x].push_back(a[lx]);
                pref[x].assign(2, 0);
                pref[x][1] = a[lx];
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(lx, m, 2 * x + 1, a);
        build(m, rx, 2 * x + 2, a);
        auto &L = tree[2 * x + 1];
        auto &R = tree[2 * x + 2];
        tree[x].resize(L.size() + R.size());
        merge(L.begin(), L.end(), R.begin(), R.end(), tree[x].begin());
        pref[x].assign(tree[x].size() + 1, 0ll);
        for (int i = 0; i < tree[x].size(); i++) {
            pref[x][i + 1] = pref[x][i] + tree[x][i];
        }
    }
    void build(vector<int>& a) {
        build(0, sz, 0, a);
    }
    int query_less_eq(int l, int r, int value, int lx, int rx, int x) {
        if (rx <= l || r <= lx) return 0;
        if (l <= lx && rx <= r) {
            int ind = upper_bound(tree[x].begin(), tree[x].end(), value) - tree[x].begin();
            return ind;
        }
        int m = (lx + rx) >> 1;
        int L = query_less_eq(l, r, value, lx, m, 2 * x + 1);
        int R = query_less_eq(l, r, value, m, rx, 2 * x + 2);
        return L + R;
    }
    int query_less_eq(int l, int r, int value) {
        return query_less_eq(l, r, value, 0, sz, 0);
    }
    int query_less(int l, int r, int value, int lx, int rx, int x) {
        if (rx <= l || r <= lx) return 0;
        if (l <= lx && rx <= r) {
            int ind = lower_bound(tree[x].begin(), tree[x].end(), value) - tree[x].begin();
            return ind;
        }
        int m = (lx + rx) >> 1;
        int L = query_less(l, r, value, lx, m, 2 * x + 1);
        int R = query_less(l, r, value, m, rx, 2 * x + 2);
        return L + R;
    }
    int query_less(int l, int r, int value) {
        return query_less(l, r, value, 0, sz, 0);
    }
    int query_kth(int l, int r, int k, int lx, int rx, int x) {
        assert(!tree[0].empty() && l <= r && k > 0 && k <= r - l + 1);
        int low = tree[0][0], high = tree[0].back();
        int ans = -1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            int count = query_less_eq(l, r, mid);
            if (count >= k) ans = mid, high = mid - 1;
            else low = mid + 1;
        }
        return ans;
    }
    int query_kth(int l, int r, int k) {
        return query_kth(l, r, k, 0, sz, 0);
    }
    int query_sum_less(int l, int r, int value, int lx, int rx, int x) {
        if (rx <= l || r <= lx) return 0;
        if (l <= lx && rx <= r) {
            int ind = lower_bound(tree[x].begin(), tree[x].end(), value) - tree[x].begin();
            return pref[x][ind]; // this is prefix sum of the first ind elements btw
        }
        int m = (lx + rx) >> 1;
        int L = query_sum_less(l, r, value, lx, m, 2 * x + 1);
        int R = query_sum_less(l, r, value, m, rx, 2 * x + 2);
        return L + R;
    }
    int query_sum_less(int l, int r, int value) {
        return query_sum_less(l, r, value, 0, sz, 0);
    }
};

// gives answer in [l, r)