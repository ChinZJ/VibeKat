#include <bits/stdc++.h>
using namespace std;

double price(int k, double p, double a, double b, double c, double d) {
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double p, a, b, c, d;
    int n;
    cin >> p >> a >> b >> c >> d >> n;
    
    double maxP = price(1, p, a, b, c, d);
    double maxD = 0;
    
    for (int k = 2; k <= n; k++) {
        double currP = price(k, p, a, b, c, d);
        maxD = max(maxD, maxP - currP);
        maxP = max(maxP, currP);
    }
    
    cout << fixed << setprecision(6) << maxD << '\n';
    
    return 0;
}