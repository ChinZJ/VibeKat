#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    deque<int> front;
    deque<int> back;
    int t, val;
    cin >> t;
    string cmd;
    while (t--) {
        cin >> cmd >> val;
        if (cmd == "push_back") {
            if (back.size() > front.size()) {
                front.push_back(back[0]);
                back.pop_front();
            }
            back.push_back(val);
        } else if (cmd == "push_front") {
            if (front.size() > back.size()) {
                back.push_front(front[front.size() - 1]);
                front.pop_back();
            }
            front.push_front(val);
        } else if (cmd == "push_middle") {
            int mid = (front.size() + back.size() + 1) / 2;
            if (front.size() < mid) {
                front.push_back(back[0]);
                back.pop_front();
            }
            back.push_front(val);
        } else { // get
            if (val > (int)front.size() - 1) {
                cout << back[val - front.size()] << '\n';
            } else {
                cout << front[val] << '\n';
            }
        }
    }
}