#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int g, s, c;
    cin >> g >> s >> c;

    int tot = (g * 3) + (s * 2) + (c);
    string s;

    if (tot >= 6) {
        s = "Gold";
    } else if (tot >= 3) {
        s = "Silver";
    } else {
        s = "Copper";
    }

    if (tot >= 8) {
        cout << "Province or ";
    } else if (tot >= 5) {
        cout << "Duchy or ";
    } else if (tot >= 2) {
        cout << "Estate or ";
    }
    
    cout << s << '\n';
}