#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<char, vector<pair<char, int>>> wm;
    unordered_map<char, vector<pair<char, int>>> bm;
    
    string str;
    int row = 8;
    char col, tmp;
    
    for (int i = 0; i < 17; i++) {
        cin >> str;
        if (i % 2 == 0) {
            continue;  // Skip border lines
        }
        
        col = 'a';
        for (int j = 2; j <= 30; j += 4) {
            tmp = str[j];
            if (tmp != '.' && tmp != ':') {
                if (isupper(tmp)) {
                    wm[tmp].emplace_back(col, row);
                } else {
                    bm[tmp].emplace_back(col, row);
                }
            }
            col++;
        }
        row--;
    }
    
    vector<char> witn = {'K', 'Q', 'R', 'B', 'N', 'P'};
    vector<char> bitn = {'k', 'q', 'r', 'b', 'n', 'p'};
    
    // White pieces: sort by row ascending, then column ascending
    for (auto& [piece, positions] : wm) {
        sort(positions.begin(), positions.end(), [](auto& a, auto& b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
        });
    }
    
    // Black pieces: sort by row descending, then column ascending
    for (auto& [piece, positions] : bm) {
        sort(positions.begin(), positions.end(), [](auto& a, auto& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    }
    
    cout << "White: ";
    bool isComma = false;
    for (auto& c : witn) {
        if (wm.find(c) != wm.end()) {
            for (auto& pos : wm[c]) {
                if (isComma) cout << ',';
                if (c == 'P') {
                    cout << pos.first << pos.second; 
                } else {
                    cout << c << pos.first << pos.second; 
                }
                
                isComma = true;
            }
        }
    }
    
    cout << "\nBlack: ";
    isComma = false;
    for (auto& c : bitn) {
        if (bm.find(c) != bm.end()) {
            for (auto& pos : bm[c]) {
                if (isComma) cout << ',';
                if (c == 'p') {
                    cout << pos.first << pos.second; 
                } else {
                    cout << c << pos.first << pos.second; 
                }
                
                isComma = true;
            }
        }
    }
    cout << '\n';
}