#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int n;
    cin >> n;
    
    vector<ll> t(n);
    for (int i=0;i<n;i++) {
        cin >> t[i];
    }
    
    vector<pair<ll, ll>> s(n);
    ll tmp;
    for (int i=0;i<n;i++) {
        cin >> tmp;
        s[i] = {tmp, t[i]};
    }

    sort(s.begin(), s.end());

    ll res = 0;
    ll com = 1;
    ll tm = 0;
    for (int i=0;i<n;i++) {
        if (s[i].first == -1) continue;

        ll req = s[i].second;
        ll hv = (s[i].first - tm) * com;
        if (hv >= req) {
            res += hv - req;
        } else { // hv < req
            while (hv + res < req) {
                com++;
                res += s[i].first;
            }
            
            res -= (req - hv);
        }
        tm = s[i].first;
    }
    cout << com << '\n';
    return 0;
}