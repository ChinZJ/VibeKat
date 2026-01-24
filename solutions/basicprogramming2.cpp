#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, t;
    cin >> N >> t;
    
    switch (t) {
        case 1:
            {
                // two sum 7777, no x == y
                unordered_map<int, int> hm;
                int tmp;
                for (int i=0;i<N;i++) {
                    cin >> tmp;
                    if (hm.find(7777 - tmp) != hm.end()) {
                        cout << "Yes\n";
                        return 0;
                    }
                    hm[tmp] = 1;
                }
                cout << "No\n";
                return 0;
            }
        case 2:
            // all unique
            {
                unordered_map<int, int> ans;
                int tmp;
                for (int i=0;i<N;i++) {
                    cin >> tmp;
                    if (ans.find(tmp) != ans.end()) {
                        cout << "Contains duplicate\n";
                        return 0;
                    }
                    ans[tmp] = 1;
                }
                cout << "Unique\n";
                return 0;
            }
        case 3:
            // integer appearing > N / 2
            {
                int half;
                if (N%2) {
                    half = (N+1)/2;
                } else {
                    half = (N/2) + 1;
                }
                unordered_map<int, int> ans;
                int tmp;
                for (int i=0;i<N;i++) {
                    cin >> tmp;
                    ans[tmp]++;
                    if (ans[tmp] >= half) {
                        cout << tmp << '\n';
                        return 0;
                    }
                }
                cout << -1 << '\n';
                return 0;
            }
        case 4:
            // median
            {
                vector<int> arr(N);
                for (int i=0;i<N;i++) {
                    cin >> arr[i];
                }
                sort(arr.begin(), arr.end());
                if (N%2 == 0) {
                    cout << arr[N/2 - 1] << ' ' << arr[N/2] << '\n';
                } else {
                    cout << arr[N/2] << '\n';
                }
                return 0;
            }
        case 5:
            // within range 100 to 999 in sorted
            {
                vector<int> ans;
                int tmp;
                for (int i=0;i<N;i++) {
                    cin >> tmp;
                    if (tmp >= 100 && tmp <= 999) ans.push_back(tmp);
                }
                sort(ans.begin(), ans.end());
                bool touch = false;
                for (int x : ans) {
                    if (touch) {
                        cout << ' ';
                    }
                    cout << x;
                    touch = true;
                }
                cout << '\n';
            }
    }
    return 0;
}