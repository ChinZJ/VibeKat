#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    cin.tie(0)-> sync_with_stdio(0);
    
    int n;
    cin >> n;
    char c;
    ll cnt = 0;
    while (n) {
        cin >> c;
        if (c == 'O') cnt += (1LL << (n-1));
        n--;
    }
    cout << cnt << '\n';
}