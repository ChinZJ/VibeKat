#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> mapper = {9, 4, 4, 4, 7};
    string line;
    double totCal = 0, totFat = 0;
    bool hasData = false;
    
    while (getline(cin, line)) {
        if (line == "-") {
            if (hasData) {
                cout << (int)round(totFat / totCal * 100) << "%\n";
                totCal = 0; totFat = 0; hasData = false;
            } else {
                break;
            }
            continue;
        }
        
        hasData = true;
        stringstream ss(line);
        double v[5]; char c[5];
        for (int i = 0; i < 5; i++) ss >> v[i] >> c[i];
        
        double cal = 0, per = 0, fatCal = 0;
        for (int i = 0; i < 5; i++) {
            if (c[i] == 'g') {
                double cals = v[i] * mapper[i];
                cal += cals;
                if (i == 0) fatCal += cals;
            } else if (c[i] == 'C') {
                cal += v[i];
                if (i == 0) fatCal += v[i];
            } else {  // '%'
                per += v[i];
            }
        }
        
        double lineCal = cal * 100 / (100 - per);
        if (c[0] == '%') fatCal = lineCal * v[0] / 100;
        
        totCal += lineCal;
        totFat += fatCal;
    }
    return 0;
}