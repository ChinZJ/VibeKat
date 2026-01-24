#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    int left = 0;
    while (left < n - 1 && v[left] <= v[left + 1]) {
        left++;
    }
    
    if (left == n - 1) {
        cout << "1 1\n";
        return 0;
    }
    
    while (left > 0 && v[left - 1] == v[left]) {
        left--;
    }
    
    int right = n - 1;
    while (right > 0 && v[right - 1] <= v[right]) {
        right--;
    }
    while (right < n - 1 && v[right] == v[right + 1]) {
        right++;
    }
    
    bool valid = true;
    for (int i = left; i < right; i++) {
        if (v[i] < v[i + 1]) {
            valid = false;
            break;
        }
    }
    
    if (valid && left > 0 && v[left - 1] > v[right]) {
        valid = false;
    }
    if (valid && right < n - 1 && v[left] > v[right + 1]) {
        valid = false;
    }
    
    if (valid) {
        cout << left + 1 << ' ' << right + 1 << '\n';
    } else {
        cout << "impossible\n";
    }
    
    return 0;
}