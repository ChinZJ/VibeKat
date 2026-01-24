#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string m;
    int d;
    cin >> m >> d;
    if ((m == "OCT" && d == 31) || (m == "DEC" && d == 25)) {
        cout << "yup\n";
    } else {
        cout << "nope\n";
    }
}