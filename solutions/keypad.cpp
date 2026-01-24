#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    int r, c;
    while (t--) {
        cin >> r >> c;
        vector<int> rows(r);
        vector<int> cols(c);
        vector<vector<int>> grid(r, vector<int>(c));
        string str;
        
        for (int i=0;i<r;i++) {
            cin >> str;
            for (int j=0;j<c;j++) {
                if (str.at(j) - '0' == 0) {
                    grid[i][j] = 0;
                } else {
                    grid[i][j] = 1;
                    rows[i]++;
                    cols[j]++;
                }
            }
        }
        
        vector<vector<char>> ans(r, vector<char>(c));
        bool valid = true;
        for (int i=0;i<r;i++) {
            if (!valid) break;
            for (int j=0;j<c;j++) {
                if (!valid) break;
                
                if (rows[i] > 0 && cols[j] > 0 && grid[i][j] == 0) {
                    valid = false;
                }
                
                if (grid[i][j] == 0) {
                    ans[i][j] = 'N';
                } else if (grid[i][j] == 1) {
                    if (rows[i] == 1 || cols[j] == 1) {
                        ans[i][j] = 'P';
                    } else {
                        ans[i][j] = 'I';
                    }
                }
            }
        }
        
        if (valid) {
            for (int i=0;i<r;i++) {
                for (int j=0;j<c;j++) {
                    cout << ans[i][j];
                }
                cout << '\n';
            }
        } else {
            cout << "impossible\n";
        }
        
        cout << "----------\n";
    }
}