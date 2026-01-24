#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    int p1, p2;
    string m1, m2;
    while (cin >> n && n != 0) {
        cin >> k;
        vector<int> warr(n + 1, 0);
        vector<int> wlarr(n + 1, 0);
        for (int i=0;i<((k * n * (n-1))/2);i++) {
            cin >> p1 >> m1 >> p2 >> m2;
            
            if (m1 == "rock") {
                if (m2 == "paper") {
                    warr[p2]++;
                    wlarr[p1]++;
                    wlarr[p2]++;
                } else if (m2 == "scissors") {
                    warr[p1]++;
                    wlarr[p1]++;
                    wlarr[p2]++;
                }
            } else if (m1 == "paper") {
                if (m2 == "rock") {
                    warr[p1]++;
                    wlarr[p1]++;
                    wlarr[p2]++;
                } else if (m2 == "scissors") {
                    warr[p2]++;
                    wlarr[p1]++;
                    wlarr[p2]++;
                }
            } else if (m1 == "scissors") {
                if (m2 == "paper") {
                    warr[p1]++;
                    wlarr[p1]++;
                    wlarr[p2]++;
                } else if (m2 == "rock") {
                    warr[p2]++;
                    wlarr[p1]++;
                    wlarr[p2]++;
                }
            }
        }
        
        for (int i=1;i<=n;i++) {
            if (wlarr[i] == 0) {
                cout << "-\n";
            } else {
                cout << fixed << setprecision(3) << (double)warr[i] / (double)wlarr[i] << '\n';
            }
        }
        cout << '\n';
    }
}