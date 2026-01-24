#include <bits/stdc++.h>
using namespace std;

// wo, bo, wd, bd
int nxt = 5;
vector<int> rnk = {1, 2, 3, 4};
vector<int> players = {0, 1, 2, 3};
queue<int> q;
int stk = -1, stkcnt = 0, hi = 0;
vector<pair<int, int>> wins(5);
int winidx = 0;

// offset either 0 or 1
void solve(int offset) {
    // check if dynasty
    if (offset == stk) {
        stkcnt++;
        if (stkcnt > hi) {
            hi = stkcnt;
            winidx = 1;
            if (rnk[offset] < rnk[offset + 2]) {
                wins[0] = {players[offset], players[offset + 2]};
            } else {
                wins[0] = {players[offset + 2], players[offset]};
            }
        } else if (stkcnt == hi) {
            if (rnk[offset] < rnk[offset + 2]) {
                wins[winidx] = {players[offset], players[offset + 2]};
            } else {
                wins[winidx] = {players[offset + 2], players[offset]};
            }
            
            winidx++;
        }
    } else { // new dynasty
        stkcnt = 1;
        stk = offset;
        
        if (stkcnt > hi) {
            hi = stkcnt;
            winidx = 1;
            if (rnk[offset] < rnk[offset + 2]) {
                wins[0] = {players[offset], players[offset + 2]};
            } else {
                wins[0] = {players[offset + 2], players[offset]};
            }
        } else if (stkcnt == hi) {
            if (rnk[offset] < rnk[offset + 2]) {
                wins[winidx] = {players[offset], players[offset + 2]};
            } else {
                wins[winidx] = {players[offset + 2], players[offset]};
            }
            
            winidx++;
        }
    }
    
    // swap pos of winning
    swap(rnk[offset], rnk[offset + 2]);
    swap(players[offset], players[offset+2]);
    
    int lidx = (offset + 1) % 2; 
    q.push(players[lidx+2]); // lose def join queue
    
    players[lidx + 2] = players[lidx]; // lose off go def
    rnk[lidx + 2] = rnk[lidx];
    
    players[lidx] = q.front(); // q become lose off
    rnk[lidx] = nxt;
    nxt++;
    
    q.pop();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // win
        // offense and defense swap
    // lose
        // offsense becomes defense
        // defense to back ot queue
        // front of queue becomes offense
    // streak -> dynasty 
        // broken when opposing team scores
    // winner creates longest dynasty
    int n;
    cin >> n;
    vector<string> nms(n);
    string cmd;
    
    for (int i=0;i<n;i++) {
        if (i > 3) q.push(i);
        cin >> nms[i];
    }
    
    cin >> cmd;
    for (char& c : cmd) {
        if (c == 'W') {
            solve(0);
        } else {
            solve (1);
        }
    }
    for (int i=0;i<winidx;i++) {
        cout << nms[wins[i].first] << ' ' << nms[wins[i].second] << '\n';
    }
    
}