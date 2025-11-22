#include <bits/stdc++.h>
using namespace std;

static constexpr int MOD = 1e9 + 7;
static constexpr int N = 1e5;

vector<long long>fact(N + 1), inv(N + 1);

long long modExp(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
            b--;
        } else {
            a = (a * a) % mod;
            b >>= 1;
        }
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i)
        fact[i] = (fact[i - 1] * i) % MOD;

    inv[N] = modExp(fact[N], MOD - 2, MOD);
    for (int i = N - 1; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

long long comb(long long n, long long k) {
    if (k > n) return 0;
    return ((fact[n] * inv[k] % MOD) * inv[n - k]) % MOD;
}

/**
 * For leetcode: make sure to set a static bool flag to avoid continuous precomp
    static bool fl = false;
    if (!fl) {
         fl = true;
         precompute();
    }
 */