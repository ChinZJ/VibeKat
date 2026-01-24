#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int r, c;
    cin >> r >> c;
    char arr[r][c];
    string str;
    for (int i = 0; i < r; i++) {
        cin >> str;
        for (int j =0; j < c; j++) {
            arr[i][j] = str.at(j);
        }
    }
    int stx = 0, sty = 0, cnt = 0;
    while (1) {
        char tmp = arr[stx][sty];
        arr[stx][sty] = 'v';
        switch (tmp) {
            case 'E':   
                sty++;
                break;
            case 'N':
                stx--;
                break;
            case 'S':
                stx++;
                break;
            case 'W':
                sty--;
                break;
            case 'T':
                cout << cnt << '\n';
                return 0;
            case 'v':
                cout << "Lost\n";
                return 0;
        }
        cnt++;
        if ((stx > r - 1) || (stx < 0) || (sty > c - 1) || (sty < 0)) {
            cout << "Out\n";
            return 0;
        }
    }
}