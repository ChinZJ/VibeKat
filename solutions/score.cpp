#include <bits/stdc++.h>
using namespace std;

// Note that if there is a tie, neither teams are in the lead

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    vector<int> hi(2);
    int pos = -1;
    int hpt = 0, apt = 0, curr=0, cosec = 0, pt, mm, ss;
    char typ, col;
    vector<char> finans = {'H', 'A'};
    while (t--) {
        cin >> typ >> pt >> mm >> col >> ss;
        ss += (mm * 60);
        if (typ == 'H') {
            hpt += pt;
            if (pos == 1) {
                if (hpt >= apt) {
                    hi[1] += (ss - cosec);
                    cosec = ss;
                }
                
                if (hpt > apt) {
                    pos = 0;
                } else if (hpt == apt) {
                    pos = -1;
                }
                
                // last case when hpt < apt do nothing
            } else if (pos == -1 && hpt > apt) {
                pos = 0;
                cosec = ss;
            } // else pos = 0, already and still in the lead.
        } else {
            apt += pt;
            if (pos == 0) {
                if (apt >= hpt) {
                    hi[0] += (ss - cosec);
                    cosec = ss;
                }
                
                if (apt > hpt) {
                    pos = 1;
                } else if (hpt == apt) {
                    pos = -1;
                }
                
                // last case when apt < hpt do nothing
            } else if (pos == -1 && apt > hpt) {
                pos = 1;
                cosec = ss;
            } // else pos = 1, already and still in the lead.
        }
    }
    if (pos != -1) {
        hi[pos] += ((32*60) - cosec);
    }
    
    if (hpt > apt) {
        pos = 0;
    } else {
        pos = 1;
    }
    
    int fins = hi[0] % 60;
    int fin2s = hi[1] % 60;

    cout << finans[pos] << ' ' << (hi[0] / 60) << ':' << (fins < 10 ? "0" : "") << fins << ' ' 
        << (hi[1] / 60) << ':' << (fin2s < 10 ? "0" : "") << fin2s << '\n';
    return 0;
    
}