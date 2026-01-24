#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    if (n == 1) {
        string tmp;
        cin >> tmp;
        cout << tmp << '\n';
        return 0;

    }
    
    vector<string> str(n + 1);
    vector<int> nxt(n + 1, 0);
    vector<int> tail(n + 1);
    
    for (int i=1;i<=n;i++) {
        cin >> str[i];
        tail[i] = i;
    }
    int a, b;
    for (int i=0;i<n-1;i++) {
        cin >> a >> b;
        nxt[tail[a]] = b;
        tail[a] = tail[b];
    }
    
    while (a != 0) {
        cout << str[a];
        a = nxt[a];
    }
    cout << '\n';
    return 0;
}