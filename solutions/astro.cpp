#include <bits/stdc++.h>
using namespace std;

int hlp(int h, int m) {
    return 60 * h + m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<string> DAYS = {"Saturday", "Sunday", "Monday",
                        "Tuesday", "Wednesday", "Thursday", "Friday"};
    
    vector<int> arr(3e6);
    
    int h1,h2,m1,m2,th1,th2,tm1,tm2;
    char c;
    cin >> h1 >> c >> m1;
    cin >> h2 >> c >> m2;
    cin >> th1 >> c >> tm1;
    cin >> th2 >> c >> tm2;
    
    int p1 = hlp(h1, m1),p2 = hlp(h2, m2),f1 = hlp(th1, tm1),f2 = hlp(th2, tm2);
    
    for (int i=p1;i<=arr.size();i += f1) {
        arr[i] = 1;
    }
    for (int i=p2;i<=arr.size();i += f2) {
        if (arr[i]) {
            int day = (i / (24 * 60)) % 7;
            int h = (i / 60) % 24;
            int m = i % 60;
            cout << DAYS[day] << '\n';
            cout << setw(2) << setfill('0') << h << ':';
            cout << setw(2) << setfill('0') << m << '\n';
            return 0;
        }
    }
    cout << "Never\n";
    return 0;
}