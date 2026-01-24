#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    bool first = true;
    
    while (cin >> n && n != 0) {
        if (!first) cout << '\n';
        first = false;
        
        vector<array<double, 4>> boxes(n);
        vector<string> types(n);
        
        for (int i = 0; i < n; i++) {
            cin >> boxes[i][0] >> boxes[i][1] >> boxes[i][2] >> boxes[i][3] >> types[i];
        }
        
        int m;
        cin >> m;
        
        while (m--) {
            double px, py;
            string ptype;
            cin >> px >> py >> ptype;
            
            cout << ptype << ' ';
            
            bool found = false;
            for (int i = 0; i < n; i++) {
                double x1 = boxes[i][0], y1 = boxes[i][1];
                double x2 = boxes[i][2], y2 = boxes[i][3];
                
                if (px >= x1 && px <= x2 && py >= y1 && py <= y2) {
                    cout << (ptype == types[i] ? "correct" : types[i]) << '\n';
                    found = true;
                    break;
                }
            }
            
            if (!found) cout << "floor\n";
        }
    }
    
    return 0;
}