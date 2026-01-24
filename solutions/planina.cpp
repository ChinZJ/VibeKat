#include <bits/stdc++.h>
using namespace std;

unordered_map<int, long long> hm;

int main() {
    int n;
    hm[1] = 3;
    hm[2] = 5;
    hm[3] = 9;
    hm[4] = 17;
    scanf("%d", &n);
    
    if (hm.find(n) == hm.end()) {
        for (int i = 5; i <= n; i++) {
            if (hm.find(i) == hm.end()) {
                hm[i] = hm[i-1] + (1 << (i-1));
            }
        }
    }
    printf("%lld\n", hm[n] * hm[n]);
}