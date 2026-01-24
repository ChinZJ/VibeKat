#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<string> stk;
    unordered_map<string, int> visit;  
    
    while (n--) {
        char c;
        cin >> c;
        
        if (c == 'E') {
            string str;
            cin >> str;
            visit[str] = stk.size();
            stk.push_back(str);
        } else if (c == 'D') {
            int r;
            cin >> r;
            while (r-- > 0 && !stk.empty()) {
                visit[stk.back()] = -1;
                stk.pop_back();
            }
        } else { // 'S'
            int k;
            cin >> k;
            
            int minDream = 0;     // minimum events to dream away
            int maxKeep = -1;     // maximum position that must be kept
            bool plotError = false;
            
            for (int i = 0; i < k; i++) {
                string str;
                cin >> str;
                if (plotError) continue;
                
                if (str[0] == '!') { // Event did NOT occur
                    string event = str.substr(1);
                    auto it = visit.find(event);
                    if (it != visit.end() && it->second >= 0) {
                        // Event happened, need to dream it (and all events after it) away
                        minDream = max(minDream, (int)stk.size() - it->second);
                    }
                } else { // Event occurred
                    auto it = visit.find(str);
                    if (it == visit.end() || it->second < 0) {
                        // Event never happened - Plot Error
                        plotError = true;
                    } else {
                        // Event must be kept
                        maxKeep = max(maxKeep, it->second);
                    }
                }
            }
            
            if (plotError) {
                cout << "Plot Error\n";
            } else if (minDream == 0) {
                cout << "Yes\n";
            } else {
                // Check if we can dream away minDream without removing required events
                int threshold = stk.size() - minDream;
                if (maxKeep >= threshold) {
                    // A required event would be dreamed away
                    cout << "Plot Error\n";
                } else {
                    cout << minDream << " Just A Dream\n";
                }
            }
        }
    }
    return 0;
}