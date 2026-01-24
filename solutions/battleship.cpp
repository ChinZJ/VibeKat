#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int w, h, n;
        cin >> w >> h >> n;
        
        vector<vector<int>> p1(h, vector<int>(w, 0));
        vector<vector<int>> p2(h, vector<int>(w, 0));
        
        int tot1 = 0, tot2 = 0;
        bool gameOver = false;
        bool finalRound = false; 
        bool isP1Turn = true;
        
        string str;
        
        for (int i = h-1; i >= 0; i--) {
            cin >> str;
            for (int j = 0; j < w; j++) {
                if (str[j] == '#') {
                    p1[i][j] = 1;
                    tot1++;
                }
            }
        }
        
        for (int i = h-1; i >= 0; i--) {
            cin >> str;
            for (int j = 0; j < w; j++) {
                if (str[j] == '#') {
                    p2[i][j] = 1;
                    tot2++;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            
            if (gameOver) continue;
            
            if (isP1Turn) {
                if (p2[y][x] == 1) {
                    p2[y][x] = -1;
                    tot2--;
                    
                    if (tot2 == 0) {
                        if (finalRound) {
                            gameOver = true; 
                        } else {
                            finalRound = true;
                            isP1Turn = false;
                        }
                    }
                    
                } else {
                    if (finalRound) {
                        gameOver = true;
                    } else {
                        isP1Turn = false;
                    }
                }
                
            } else {
                if (p1[y][x] == 1) {
                    p1[y][x] = -1;
                    tot1--;
                    
                    if (tot1 == 0) {
                        gameOver = true;
                    }
                    
                } else {
                    if (finalRound) {
                        gameOver = true;
                    } else {
                        isP1Turn = true;
                    }
                }
            }
        }
        
        if (tot1 == 0 && tot2 == 0) {
            cout << "draw\n";
        } else if (tot1 == 0) {
            cout << "player two wins\n";
        } else if (tot2 == 0) {
            cout << "player one wins\n";
        } else {
            cout << "draw\n";
        }
    }
    
    return 0;
}