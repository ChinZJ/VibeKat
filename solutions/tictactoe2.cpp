#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    while (n--) {
        vector<string> board(3);
        int totx = 0, toto = 0;
        
        for (int i = 0; i < 3; i++) {
            cin >> board[i];
            for (char c : board[i]) {
                if (c == 'X') totx++;
                else if (c == 'O') toto++;
            }
        }
        
        if (totx != toto && totx != toto + 1) {
            cout << "no\n";
            continue;
        }
        
        int horiX = 0, vertX = 0, diagX = 0, horiO = 0, vertO = 0, diagO = 0;
        
        
        for (int i = 0; i < 3; i++) {
            // Check rows
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                if (board[i][0] == 'X') horiX++;
                else if (board[i][0] == 'O') horiO++;
            }
            
            // Check columns
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                if (board[0][i] == 'X') vertX++;
                else if (board[0][i] == 'O') vertO++;
            }
        }
        
        
        // Check diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == 'X') diagX++;
            else if (board[0][0] == 'O') diagO++;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == 'X') diagX++;
            else if (board[0][2] == 'O') diagO++;
        }
        
        int xWins = horiX + vertX + diagX;
        int oWins = horiO + vertO  + diagO;
        bool valid = true;
        
        // Both cannot win
        if (xWins > 0 && oWins > 0) {
            // Both can't win - game stops at first win
            valid = false;
        } else if (xWins > 0) {
            // X can win at most 2
            if (xWins > 2) {
                valid = false;
            } 
            
            if (totx != toto + 1) { 
                valid = false;
            }
            
            // either 2 diag 
            // or 2 choose (diag, hori, vert)
            if (xWins == 2) {
                if (horiX >= 2 || vertX >= 2) {
                    valid = false;
                }
            }
        } else if (oWins > 0) {
            if (oWins > 1) {
                valid = false;
            }
            
            if (totx != toto) {
                valid = false;
            }
        }
        
        cout << (valid ? "yes" : "no") << '\n';
    }
    
    return 0;
}