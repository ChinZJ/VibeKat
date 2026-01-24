#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<unordered_map<string, int>> days(8);
    int day = 0, prevday, top;
    
    string str;
    while (cin >> str) {
        if (str == "<text>") {
            int prevday = (day + 7) % 8;
            days[prevday].clear();
            
            while (cin >> str) {
                if (str == "</text>") break;
                if (str.size() < 4) continue;
                
                for (int i = 0; i < 7; i++) {
                    days[(day + i) % 8][str]++;
                }
            }
            day++;
        } else {
            cin >> top >> str;
            
            vector<pair<string, int>> revmap(days[(day + 7) % 8].begin(), days[(day+7) % 8].end());
            
            sort(revmap.begin(), revmap.end(), [](auto& a, auto& b) {
                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
            });
            
            cout << "<top " << top << ">\n";
            if (!revmap.empty()) {
                int nth_freq;
                if ((size_t)top <= revmap.size()) {
                    nth_freq = revmap[top - 1].second;
                } else {
                    nth_freq = revmap.back().second;
                }
                
                for (const auto& [word, freq] : revmap) {
                    if (freq >= nth_freq) {
                        cout << word << ' ' << freq << '\n';
                    } else {
                        break;
                    }
                }
            }
            cout << "</top>\n";
        }
    }
    return 0;
}