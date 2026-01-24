#include <bits/stdc++.h>
using namespace std;

void printBoxLine(int lenn) {
    cout << "| ";
    for (int i=0;i<lenn;i++) {
        cout << "+---";
    }
    cout << "+ |\n";
}

void printBox(int row, int col, 
    string& sn, string& sm, string& vertires,
    int pos) {
    
    // print top layer
    if (!pos) { 
        printBoxLine(sn.length());
    }
    
    vector<int> ans(sn.length());
    for (int i=0;i<sn.length();i++) {
        ans[i] = (sn[i] - '0') * (sm[pos] - '0');
    }
    
    // Print upper tri
    cout << '|';
    if (pos > 0 && vertires[pos - 1] != ' ') {
        cout << '/';
    } else {
        cout << ' ';
    }
    for (int i=0;i<sn.length();i++) {
        cout << '|' << ans[i] / 10 << " /";
    }
    cout << "| |\n";
    
    // Print mid
    cout << "| ";
    for (int i=0;i<sn.length();i++) {
        cout << "| / ";
    }
    cout << '|' << sm[pos] << "|\n";
    
    // Print lower tri - check if vertires exists
    cout << '|' << vertires[pos];
    for (int i=0;i<sn.length();i++) {
        
        cout << "|/ " << ans[i] % 10;
    }
    cout << "| |\n";
    
    // Print box line
    printBoxLine(sn.length());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string sn, sm, sres, vertires, horires;
    int n, m, lenn, lenm, row, col, res;
    while (cin >> sn >> sm) {
        n = stoi(sn); m = stoi(sm); res = n * m;
        
        if (n == 0 && m == 0) break;
        
        lenn = sn.length(); lenm = sm.length();
        
        sres = to_string(res);
        vertires.reserve(lenm);
        vertires = sres.substr(0, sres.length() - lenn);
        vertires = string(lenm - vertires.length(), ' ') + vertires;
        horires = sres.substr(sres.length() - lenn);
        
        row = 4 + 5 + 4 * (lenm - 1);
        col = 4 + 5 + 4 * (lenn - 1);
        
        // Top border
        cout << '+' << string(col-2, '-') << "+\n";
        
        // n
        cout << '|';
        for (int a=0;a<lenn;a++) {
            cout << "   " << sn[a];
        }
        cout << "   |\n";
        
        // Boxes
        for (int a=0;a<lenm;a++) {
            printBox(row,col,sn,sm,vertires,a);
        }
        
        // horires
        cout << '|';
        // only case with no diagonal
        if (lenn == 1 && sres.length() == 1) {
            cout << "  " << horires << "    ";
        } else {
            for (char c : horires) {
                cout << "/ " << c << ' ';
            }
            cout << string(col - 2 - (4 * horires.length()), ' ');
        }
        cout << "|\n";
        
        // Bot border
        cout << '+' << string(col-2, '-') << "+\n";
    }
    return 0;
}