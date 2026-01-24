#include <bits/stdc++.h>
using namespace std;

#define pb push_back

vector<int> vals {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
    20, 30, 40, 50, 60, 70, 80, 90, 100,
    200, 300, 400, 500, 600, 700, 800, 900, 1000
};
vector<string> chars {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC", "C", 
    "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM", "M"
};
vector<pair<string, int>> nnn;
vector<int> pos(1001);

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    // Preprocessing
    
    // Setup brute force 1 - 999
    for (int i=1;i<=999;i++) {
        int tmp = i;
        string str = "";
        int j = 27;
        while (tmp || j) {
            if (tmp >= vals[j]) {
                str += chars[j];
                tmp -= vals[j];
            } else {
                j--;
            }
        }
        nnn.pb({str, i});
    }
    
    // Sort and update rev values
    sort(nnn.begin(), nnn.end());
    
    // Create pos array
    for (int i=0;i<945;i++) {
        pos[nnn[i].second] = i + 1;
    }
    
    // update rev values
    int id = -1;
    for (int i=998;i>=945;i--) {
        pos[nnn[i].second] = id;
        --id;
    }
    
    // Main algo
    int n;
    int t;
    cin >> n;
    while (n--) {
        cin >> t;
        if (t <= 999) {
            cout << pos[t] << '\n';
            continue;
        }
        
        // Starts with M
        int k = t / 1000; // Number of M
        int r = t % 1000; // Remaining value
        
        if (r == 0) {
            cout << k * 946 << '\n';
        } else if (pos[r] > 0) {
            cout << (k * 946) + pos[r] << '\n';
        } else {
            cout << pos[r] - (k * 54) << '\n';
        }
    }
    
    return 0;
}