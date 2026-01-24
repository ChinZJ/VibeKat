#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string str;
    int ch, cm, cs, ct, pt;
    double spd = -1.0;
    double track = 0.0;
    char c;
    while (getline(cin, str)) {
        stringstream ss(str);
        ss >> ch >> c >> cm >> c >> cs;
        ct = (ch * 60 * 60) + (cm * 60) + cs;
        
        if (spd > 0.0) {
            track += (spd * (ct - pt));
        }
        pt = ct;
        
        if (str.length() > 8) { // change
            ss >> spd;
            spd = spd / (60 * 60);
        } else {
            cout << str << ' ' << fixed << setprecision(2) << track  << " km\n";
        }
    }
    return 0;
}