#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> arr;
    bool valid = true;
    int start, tmp;
    
    int n;
    while (cin>> n) {
        valid = true;
        cin >> start;
        vector<int> arr(n + 1, 0);
        arr[0] = 1;
        
        for (int i=1;i<n;i++) {
            cin >> tmp;
            int diff = abs(start - tmp);
            if (diff >= n || arr[diff]) {
                valid = false;
            } else {
                arr[diff] = 1;
            }
            
            start = tmp;
            
        }
        if (valid) {
            cout << "Jolly\n";
        } else {
            cout << "Not jolly\n";
        }
        
    }
}