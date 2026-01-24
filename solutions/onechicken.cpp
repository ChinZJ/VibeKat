#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int diff;

    if (m >= n) {
        diff = m - n;
        if (diff == 1 || diff == 0) {
            cout << "Dr. Chaz will have " << diff << " piece of chicken left over!\n";
        } else {
            cout << "Dr. Chaz will have " << diff << " pieces of chicken left over!\n";
        }
    } else {
        diff = n - m;
        if (diff == 1 || diff == 0) {
            cout << "Dr. Chaz needs " << diff << " more piece of chicken!\n";
        } else {
            cout << "Dr. Chaz needs " << diff << " more pieces of chicken!\n";
        }
    }
}