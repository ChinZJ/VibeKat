#include <bits/stdc++.h>
using namespace std;

long long fastexp(int a, int b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main() {
    cin.tie(0)-> sync_with_stdio(0);
    
    int n;
    cin >> n;
    
    int tog = __builtin_popcount(n);
    cout << fastexp(2, tog);
}