#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    bool first_image = true;
    
    while (getline(cin, line)) {
        vector<vector<char>> board;
        map<char, pair<int, int>> pos;
        
        if (line.empty()) continue;
        
        board.push_back(vector<char>());
        for (int j = 0; j < line.size(); j++) {
            char c = line[j];
            board[0].push_back(c);
            if (c != '.') {
                pos[c] = {0, j};
            }
        }
        
        // Read remaining lines of the image
        while (getline(cin, line) && !line.empty()) {
            int row = board.size();
            board.push_back(vector<char>());
            for (int j = 0; j < line.size(); j++) {
                char c = line[j];
                board[row].push_back(c);
                if (c != '.') {
                    pos[c] = {row, j};
                }
            }
        }
        
        // Create sequence of dots: 0-9, a-z, A-Z
        vector<char> sequence;
        for (char c = '0'; c <= '9'; c++) {
            if (pos.count(c)) sequence.push_back(c);
            else break;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            if (pos.count(c)) sequence.push_back(c);
            else break;
        }
        for (char c = 'A'; c <= 'Z'; c++) {
            if (pos.count(c)) sequence.push_back(c);
            else break;
        }
        
        // Connect consecutive dots
        for (int i = 0; i < (int)sequence.size() - 1; i++) {
            char c1 = sequence[i];
            char c2 = sequence[i + 1];
            
            int r1 = pos[c1].first, col1 = pos[c1].second;
            int r2 = pos[c2].first, col2 = pos[c2].second;
            
            if (r1 == r2) {
                int start = min(col1, col2);
                int end = max(col1, col2);
                for (int j = start + 1; j < end; j++) {
                    if (board[r1][j] == '.') {
                        board[r1][j] = '-';
                    } else if (board[r1][j] == '|') {
                        board[r1][j] = '+';
                    }
                }
            } else if (col1 == col2) {
                int start = min(r1, r2);
                int end = max(r1, r2);
                for (int j = start + 1; j < end; j++) {
                    if (board[j][col1] == '.') {
                        board[j][col1] = '|';
                    } else if (board[j][col1] == '-') {
                        board[j][col1] = '+';
                    }
                }
            }
        }
        
        // Print output with blank line between images
        if (!first_image) cout << '\n';
        first_image = false;
        
        for (auto& row : board) {
            for (char c : row) {
                cout << c;
            }
            cout << '\n';
        }
    }
    
    return 0;
}