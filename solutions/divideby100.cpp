#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n, m;
    cin >> n >> m;
    
    int nl = n.size();
    int ml = m.size() - 1; // number decimals to move back
    
    int nptr = n.size() - 1;
    
    // Count trailing zeroes
    while (nptr >= 0) {
        if (n.at(nptr) == '0') {
            nptr--;
        } else {
            break;
        }
    }
    
    int trailzero = nl - (nptr + 1);
    if (trailzero > ml) {
        cout << n.substr(0, nl - ml);
        return 0;
    } else {
        int rm = ml - trailzero;
        int nleft = nl - trailzero;
        if (nleft > rm) {
            cout << n.substr(0, nleft - rm) << '.' << n.substr(nleft - rm, rm) << '\n';
        } else {
            int bfr = rm - nleft;
            cout << "0." << string(bfr, '0') << n.substr(0, nptr + 1) <<'\n';
        }
    }
    
    
    
    
}