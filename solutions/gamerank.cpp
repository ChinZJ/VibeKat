#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string str;
    cin >> str;
    
    unordered_map<int, int> promo;
    for (int i=21;i<=25;i++) {
        promo[i] = 2;
    }
    for (int i=16; i<=20;i++) {
        promo[i] = 3;
    }
    for (int i=11;i<=15;i++) {
        promo[i] = 4;
    }
    for (int i=1;i<=10;i++) {
        promo[i] = 5;
    }
    int consec=0;
    int curr=0;
    int currr=25;
    int gain;
    
    for (auto& c : str) {
        if (c == 'W') {
            consec++;
            gain = 1;
            if (consec >= 3 && currr >= 6) {
                gain++;
            }
            
            curr += gain;
            
            while (curr > promo[currr]) {    
                curr -= promo[currr];
                currr--;
                if (currr == 0) {
                    cout << "Legend\n";
                    return 0;
                }
            } 
        } else {
            consec=0;
            if (currr <= 20) {
                curr--;
                if (curr < 0) {
                    if (currr == 20) {
                        curr = 0;
                    } else {
                        currr++;
                        curr = promo[currr] - 1;
                    }
                }
            }
                
        }
    }
    cout << currr << '\n';
    return 0;
}