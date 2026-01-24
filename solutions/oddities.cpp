#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    int d;
    while (n--) {
        cin >> d;
        if (d % 2) {
            cout << d << " is odd\n";
        } else {
            cout << d << " is even\n";
        }
    }
}