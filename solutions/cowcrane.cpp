#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll m, l;
    ll M, L;
    ll tm, tl;
    cin >> m >> l >> M >> L >> tm >> tl;
    
    ll om = abs(m - 0);
    ll omM = om + abs(M - m);
    ll omMlL = omM + abs(M - l) + abs(L - l);
    
    if (omM <= tm && omMlL <= tl) {
        cout << "possible\n";
        return 0;
    }

    ll oml = abs(m - 0) + abs(m - l);
    ll omlL = oml + abs(L - l);
    ll omlLmM = omlL + abs(L - l) + abs(M - l);
    
    if (omlL <= tl && omlLmM <= tm) {
        cout << "possible\n";
        return 0;
    }
    
    ll ol = abs(l - 0);
    ll olL = ol + abs(L - l);
    ll olLmM = olL + abs(L - m) + abs(M - m);
    
    if (olL <= tl && olLmM <= tm) {
        cout << "possible\n";
        return 0;
    }
    
    ll olm = abs(l - 0) + abs(l - m);
    ll olmM = olm + abs(M - m);
    ll olmMlL = olmM + abs(M - m) + abs(L - m);
    
    if (olmM <= tm && olmMlL <= tl) {
        cout << "possible\n";
        return 0;
    }
    
    cout << "impossible\n";
    return 0;
}