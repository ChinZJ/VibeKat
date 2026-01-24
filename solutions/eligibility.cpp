#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cr;
    cin >> n;

    string nm, st, en;

    while (n--) {
        cin >> nm >> st >> en >> cr;
        
        bool isLate = false, isBorn = false, isEight = false;

        if (stoi(st.substr(0, 4)) >= 2010) isLate = true;
        if (stoi(en.substr(0, 4)) >= 1991) isBorn = true;
        if (cr >= 41) isEight = true;

        cout << nm;

        if (isLate || isBorn) {
            cout << " eligible\n";
        } else if (!isLate && !isBorn && isEight) {
            cout << " ineligible\n";
        } else {
            cout << " coach petitions\n";
        }
    }
}