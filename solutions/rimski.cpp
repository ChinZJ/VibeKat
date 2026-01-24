#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // I -> 1 (3 is III)
    // V -> 5 (4 is IV) (8 is VIII)
    // X -> 10 (9 is IX)
    // L -> 50 (40 is XL) (80 is LXXX)
    // C -> 100 (90 is XC)
    
    unordered_map<char, int> mapper;
    mapper['I'] = 0;
    mapper['V'] = 0;
    mapper['X'] = 0;
    mapper['L'] = 0;
    mapper['C'] = 0;
    
    string str;
    cin >> str;
    for (char c : str) {
        mapper[c]++;
    }
    
    bool tens = false;
    
    // Settle large to small
    if (mapper['C']) { // limit < 100
        cout << "XC";
        mapper['X']--;
        tens = true;
    }
    if (mapper['L']) {
        int numx = mapper['X'];
        if (numx == 0) {
            cout << 'L'; 
        } else if (numx == 1) {
            cout << "XL";
            mapper['X']--;
        } else if (numx == 2 && mapper['V'] == 0 && mapper['I'] == 1) {
            cout << "XL";
            mapper['X'] = 1;
        } else {
            cout << 'L' << string(numx, 'X');
            mapper['X'] = 0;
        }
        tens = true;
    }
    if (mapper['X']) {
        if (mapper['I'] == 1 && mapper['V'] == 0) {
            cout << string(mapper['X'] - 1, 'X');
            cout << "IX\n";
            return 0;
        }
        
        cout << string(mapper['X'], 'X');
    }
    if (mapper ['V']) {
        if (mapper['I'] == 1) {
            cout << "IV\n";
            return 0;
        } else {
            cout << 'V';
        }
    }
    if (mapper['I']) {
        cout << string(mapper['I'], 'I') << '\n';
        return 0;
    }
    cout << '\n';
    return 0;
}