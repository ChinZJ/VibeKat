#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n;
    while (cin >> n) {
        if (n == "END") break;
        
        if (n == "1") {
            cout << "1\n";
            continue;
        } 
        long long len = n.length();
        long long curr = to_string(len).length();
        int i = 2;
        while (curr != len) {
            len = curr;
            curr = to_string(len).length();
            i++;
        }
        cout << i << '\n';
    }
}