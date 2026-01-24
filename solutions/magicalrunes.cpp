#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string a;
    ll n;
    cin >> a >> n;
    
    ll res = 0;
    
    for (int i=(int)a.size() - 1;i>=0;i--) {
        res <<= 1;
        if (a[i] == 'B') {
            res++;
        }
    }
    res += n;
    int cnt=0;
    while (res != 0) {
        if (res & 1) cout << 'B';
        else cout << 'A';
        res >>= 1;
        cnt++;
    }
    
    cout << string(a.size() - cnt, 'A');
    cout << '\n';
}