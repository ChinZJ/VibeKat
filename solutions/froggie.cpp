#include <bits/stdc++.h>
using namespace std;

vector<int> os, is, ss;
int P; // position from left
int L, W; // number lanes and width

bool isCollide(int l, int t) {
    if (l <= 0 || l > L) return false;
    // get lane above
    int o = os[l]; 
    int i = is[l]; 
    int s = ss[l];
    
    bool movesRight = (L - l) % 2 == 0;
    
    if (movesRight) {
        // Car ends at: (o + t*s) + k*i
        // Swept range per car: [carEnd - s + 1, carEnd]
        int carEnd = o + t * s;
        int diff = P - carEnd;
        int mod = ((diff % i) + i) % i;
        // Collision if mod in {0, i-1, i-2, ..., i-s+1} (within s cells of car end)
        return (mod == 0) || (s > 0 && mod > i - s);
    } else {
        // Car ends at: (W-1-o) - t*s + k*i  
        // Swept range per car: [carEnd, carEnd + s - 1]
        int carEnd = (W - 1 - o) - t * s;
        int diff = P - carEnd;
        int mod = ((diff % i) + i) % i;
        // Collision if mod in {0, 1, ..., s-1}
        return (mod == 0) || (s > 0 && mod < s);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> L >> W;
    
    int O, I, S; // offset, interval, speed
    os.resize(L+1); is.resize(L+1); ss.resize(L+1);
    for (int i=L;i>=1;i--) {
        cin >> os[i] >> is[i] >> ss[i];
    }
    
    string str; // cmd
    cin >> P >> str;
    int t=1, l = 1;
    for (char& c : str) {
        if (c == 'U') {
            if (isCollide(l, t)) {
                cout << "squish\n";
                return 0;
            }
            l++;
            
        } else if (c == 'R') {
            if (P == W - 1) {
                cout << "squish\n";
                return 0;
            }
            
            P++;
            if (isCollide(l-1, t)) {
                cout << "squish\n";
                return 0;
            }
            
        } else if (c == 'L') {
            if (P == 0) {
                cout << "squish\n";
                return 0;
            }
            
            P--;
            if (isCollide(l-1, t)) {
                cout << "squish\n";
                return 0;
            }
        } else { // D
            if (isCollide(l-2, t)) {
                cout << "squish\n";
                return 0;
            }
            l--;
        }
        t++;
    }
    if (l <= L) {
        cout << "squish\n";
    } else {
        cout << "safe\n";
    }
    return 0;
}   
