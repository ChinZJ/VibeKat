#include <bits/stdc++.h>
using namespace std;

int main() {
    double d;
    cin >> d;
    d = d * 1000 *5280 / 4854;
    cout << (int)round(d) << '\n';
}