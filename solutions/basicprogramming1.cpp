#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, t;
    cin >> n >> t;
    int arr[n];
    int chararr[n];
    long long tot = 0;
    long long evTot = 0;
    int visit[n] = { 0 };
    for (int i=0;i<n;i++) {
        cin >> arr[i];
        tot += arr[i];
        chararr[i] = arr[i] % 26;
        if (arr[i]%2 == 0) {
            evTot += arr[i];
        }
    }
    
    switch (t) {
        case 1:
            cout << 7 << '\n';
            break;
        case 2:
            if (arr[0] > arr[1]) {
                cout << "Bigger\n";
            } else if (arr[0] == arr[1]) {
                cout << "Equal\n";
            } else {
                cout << "Smaller\n";
            }
            break;
        case 3:
            {
                int med[3] = {arr[0], arr[1], arr[2]};
                sort(med, med + 3);
                cout << med[1] << '\n';
            }
            break;
        case 4:
            cout << tot <<'\n';
            break;
        case 5:
            cout << evTot << '\n';
            break;
        case 6:
            for (int i=0;i<n;i++) {
                cout << (char)('a' + chararr[i]);  // ← FIXED: Cast to char
            }
            cout << '\n';
            break;
        case 7:
            {
                int i = 0;
                visit[i] = 1;
                while (1) {
                    i = arr[i];
                    if (i < 0 || i > n - 1) {
                        cout << "Out\n";
                        break;
                    } else if (i == n - 1) {
                        cout << "Done\n";
                        break;
                    } else if (visit[i]) {
                        cout << "Cyclic\n";
                        break;
                    } else {
                        visit[i] = 1;
                    }
                }
            }
            break;
    }
}