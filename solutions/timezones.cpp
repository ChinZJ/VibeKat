#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<string, int> mapper;
    mapper["UTC"] = 0 * 60;
    mapper["GMT"] = 0 * 60;
    mapper["WET"] = 0 * 60;
    
    mapper["BST"] = 1 * 60;
    mapper["IST"] = 1 * 60;
    mapper["WEST"] = 1 * 60;
    mapper["CET"] = 1 * 60;
    
    mapper["CEST"] = 2 * 60;
    mapper["EET"] = 2 * 60;
    
    mapper["EEST"] = 3 * 60;
    mapper["MSK"] = 3 * 60;
    
    mapper["MSD"] = 4 * 60;
    
    mapper["AWST"] = 8 * 60;
    
    mapper["ACST"] = 95 * 6;
    
    mapper["AEST"] = 10 * 60;
    
    mapper["ACDT"] = 105 * 6;
    
    mapper["AEDT"] = 11 * 60;
    
    mapper["HST"] = -10 * 60;
    
    mapper["AKST"] = -9 * 60;
    
    mapper["PST"] = -8 * 60;
    mapper["AKDT"] = -8 * 60;
    
    mapper["MST"] = -7 * 60;
    mapper["PDT"] = -7 * 60;
    
    mapper["CST"] = -6 * 60;
    mapper["MDT"] = -6 * 60;
    
    mapper["EST"] = -5 * 60;
    mapper["CDT"] = -5 * 60;
    
    mapper["AST"] = -4 * 60;
    mapper["EDT"] = -4 * 60;
    
    mapper["ADT"] = -3 * 60;
    
    mapper["NST"] = -35 * 6;
    
    mapper["NDT"] = -25 * 6;
    
    int n;
    cin >> n;
    string str;
    string pd;
    int th, tm, dh, dm, adder, minadd;
    bool back = false;
    for (int i=0;i<n;i++) {
        cin >> str;
        if (str[0] == 'n') {
            th = 12;
            tm = 0;
        } else if (str[0] == 'm') {
            th = 0;
            tm = 0;
        } else {
            cin >> pd;
            if (str.size() == 4) {
                th = str[0] - '0';
                tm = stoi(str.substr(2));
            } else {
                th = stoi(str.substr(0,2));
                tm = stoi(str.substr(3));
            }
            if (pd[0] == 'a') {
                if (th == 12) th = 0;
            } else {
                if (th != 12) th += 12;
            }
        }
        
        int totMin = th * 60 + tm;
        
        cin >> str >> pd;
        totMin = totMin - mapper[str] + mapper[pd];
        
        int fd = 24 * 60;
        totMin = ((totMin % fd) + fd) % fd;
        
        int outh = totMin / 60;
        int outm = totMin % 60;

        if (outm == 0) {
            if (outh == 12) {
                cout << "noon\n";
                continue;
            } else if (outh == 0) {
                cout << "midnight\n";
                continue;
            }
        }
        
        
        if (outh == 0) {
            cout << "12:";
        } else if (outh > 12) {
            cout << outh - 12 << ':';
        } else {
            cout << outh << ':';
        }
        
        if (outm < 10) {
            cout << '0' << outm << ' ';
        } else {
            cout << outm << ' ';
        }
        
        if (outh >= 12) {
            cout << "p.m.\n";
        } else {
            cout << "a.m.\n";
        }
    }
    return 0;
}