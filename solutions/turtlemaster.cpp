#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<vector<char>> board(8, vector<char>(8));
    string tmp;
    int ia[] = {0, 1, 0, -1}; // right down left up
    int ja[] = {1, 0, -1, 0}; // right up left up
    int x = 7, y = 0, dir = 0;
    int dx, dy;
    for (int i=0;i<8;i++) {
        cin >> tmp;
        for (int j=0;j<8;j++) {
            board[i][j] = tmp[j];
        }
    }
    
    cin >> tmp;
    for (char c : tmp) {
        if (c == 'F') {
            dx = x + ia[dir];
            dy = y + ja[dir];
            if (dx >= 0 && dx < 8 && dy >= 0 && dy < 8) {
                if (board[dx][dy] == 'C' || board[dx][dy] == 'I') {
                    cout << "Bug!\n";
                    return 0;
                }
                x = dx; y = dy;
            } else {
                cout << "Bug!\n";
                return 0;
            }
        } else if (c == 'R') {
            dir = (dir + 1) % 4;
        } else if (c == 'L') {
            dir = (dir + 3) % 4;
        } else {
            dx = x + ia[dir];
            dy = y + ja[dir];
            if (dx >= 0 && dx < 8 && dy >= 0 && dy < 8) {
                if (board[dx][dy] != 'I') {
                    cout << "Bug!\n";
                    return 0;
                } else {
                    board[dx][dy] = '.';
                }
            } else {
                cout << "Bug!\n";
                return 0;
            }
        }
    }
    if (board[x][y] == 'D') {
        cout << "Diamond!\n";
    } else {
        cout << "Bug!\n";
    }
    return 0;
}