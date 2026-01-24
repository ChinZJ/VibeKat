#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    int r, c, n;
    string tmp;
    while (t--) {
        cin >> r >> c >> n;
        
        vector<vector<int>> g1(r, vector<int>(c)), g2(r, vector<int>(c));
        
        unordered_map<char, int> mapper;
        mapper['R'] = 0;
        mapper['S'] = 1;
        mapper['P'] = 2;
        unordered_map<int, char> rev;
        rev[0] = 'R';
        rev[1] = 'S';
        rev[2] = 'P';
        
        for (int i=0;i<r;i++) {
            cin >> tmp;
            for (int j=0;j<c;j++) {
                g1[i][j] = mapper[tmp[j]];
            }
        }
        
        n = min(n, r + c);  // optimization: grid stabilizes
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        for (int a = 0; a < n; a++) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    g2[i][j] = g1[i][j];
                    
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];
                        
                        if (ni >= 0 && ni < r && nj >= 0 && nj < c) {
                            if ((g1[ni][nj] + 1) % 3 == g1[i][j]) {
                                g2[i][j] = g1[ni][nj];
                                break;
                            }
                        }
                    }
                }
            }
            swap(g1, g2);
        }
        
        for (int i=0;i<r;i++) {
            for (int j=0;j<c;j++) {
                cout << rev[g1[i][j]];
            }
            cout << '\n';
        }
        cout << '\n';
    }
}