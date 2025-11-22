#include <bits/stdc++.h>
using namespace std;

static constexpr int MOD = 998244353;

struct Binom {
    long long inv[30];

    Binom() {
        for(int i = 1; i < 30; i++){
            inv[i] = modInv(i, MOD);
        }
    }

    static long long modExp(long long base, long long exp, int m) {
        long long res = 1 % m;
        while(exp > 0) {
            if(exp & 1) res = (res * base) % m;
            base = (base * base) % m;
            exp >>= 1;
        }
        return res;
    }

    static long long modInv(long long a, int m) {
        return modExp(a, m - 2, m);
    }

    long long binom(long long n, int r) {
        if(r < 0 || r > n) return 0;
        long long res = 1;
        for(int i = 0; i < r; i++){
            long long top = (n - i) % MOD;
            res = (res * top) % MOD;
            res = (res * inv[i + 1]) % MOD;
        }
        return res;
    }
};

int main() {
    
    static Binom binomCalc;

    //binomCalc.binom
    //binomCalc.modExp

    return 0;
}
