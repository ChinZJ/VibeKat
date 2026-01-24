#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string yay = "yay";
    string ay = "ay";
    
    string str, sub;
    bool first;
    while (cin >> str) {
        stringstream ss(str);
        first = true;
        while (ss >> sub) {
            if (!first) {
                cout << ' ';
            }
            first = false;
            if (sub[0] == 'a' || sub[0] == 'e' || sub[0] == 'i'
                    || sub[0] == 'o' || sub[0] == 'u' || sub[0] == 'y') {
                cout << sub << yay;
            } else {
                int i=0;
                for (i=0;i<sub.length();i++) {
                    if (sub[i] == 'a' || sub[i] == 'e' || sub[i] == 'i'
                            || sub[i] == 'o' || sub[i] == 'u' || sub[i] == 'y') {
                        cout << sub.substr(i) << sub.substr(0, i) << ay;
                        break;
                    }
                }
            }
        }
        cout << '\n';
    }
    return 0;
}