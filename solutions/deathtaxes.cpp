#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ll x, y;
    ll shr = 0;
    double avg = 0;
    string cmd;
    
    while (cin >> cmd) {
        if (cmd == "buy") {
            cin >> x >> y;
            double cost = shr * avg;
            shr += x;
            cost += (x * y);
            avg = cost / shr;
            
        } else if (cmd == "sell") {
            cin >> x >> y;
            shr -= x;
        } else if (cmd == "split") {
            cin >> x;
            shr *= x;
            avg /= x;
        } else if (cmd == "merge") {
            cin >> x;
            shr /= x;
            avg *= x;
        } else {
            cin >> y;
            double profit = shr * (y - avg);
            double tax = max(0.0, 0.3 * profit);
            double total = shr * y - tax;
            
            cout << fixed << setprecision(8) << total << '\n';
        }
    }
}