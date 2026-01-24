#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y;
    cin >> x >> y;

    if (y == 1) {
        if (x == 0) {
            cout << "ALL GOOD\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }

    } else {
        cout << fixed << setprecision(10) << ((double)x / (1.0 - y)) << '\n';
    }   
}