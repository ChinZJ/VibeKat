#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, d, tmp, cnt = 0; 
    cin >> n >> d;
    while (n--) {
        cin >> tmp;
        if (tmp > d) {
            cnt++;
        } else {
            cout << "It hadn't snowed this early in " << cnt << " years!\n";
            return 0;
        }
    }
    cout << "It had never snowed this early!\n";
}