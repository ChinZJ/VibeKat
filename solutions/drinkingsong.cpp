#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    n++;
    string str, nplu, n1plu;
    cin >> str;
    while (n--) {
        if (n == 0) break;
        if (n == 1) {
            nplu = "bottle";
            n1plu = "bottles";
        } else if (n == 2) {
            nplu = "bottles";
            n1plu = "bottle";
        } else {
            nplu = "bottles";
            n1plu = "bottles";
        }
        
        cout << n << ' ' << nplu << " of " << str << " on the wall, ";
        cout << n << ' ' << nplu << " of " << str << ".\nTake ";
        
        if (n - 1 == 0) {
            cout << "it down, pass it around, " << "no more " << n1plu << " of " << str << ".\n";
        } else {
            cout << "one down, pass it around, "<< n - 1 << ' ' << n1plu << " of " << str << " on the wall.\n\n";
        }
    }
}