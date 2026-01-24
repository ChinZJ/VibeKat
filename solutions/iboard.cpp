#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string str;
    int val, cnt;
    while (getline(cin, str)) {
        bool otog = false, ztog = false;
        for (char& c : str) {
            val = int(c); // 7 bits
            
            for (int i = 0; i < 7; i++) { 
                if (val & 1) {
                    otog = !otog;
                } else {
                    ztog = !ztog;
                }
                val >>= 1;
            }
        }
        if (!otog && !ztog) {
            cout << "free\n";
        } else {
            cout << "trapped\n";
        }
    }
    return 0;
}