#include <bits/stdc++.h>
using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month - 1];
}

// Convert datetime to total minutes from reference
long long toMinutes(int year, int month, int day, int hour, int minute) {
    long long total = 0;
    for (int y = 1; y < year; y++) {
        total += isLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < month; m++) {
        total += daysInMonth(m, year);
    }
    total += day - 1;
    return total * 24 * 60 + hour * 60 + minute;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, cleaningTime;
        cin >> n >> cleaningTime;
        
        // Events: (time, type) where type = +1 for arrival, -1 for departure
        vector<pair<long long, int>> events;
        
        for (int i = 0; i < n; i++) {
            string code;
            int y1, m1, d1, h1, min1;
            int y2, m2, d2, h2, min2;
            char dash, colon;
            
            cin >> code;
            cin >> y1 >> dash >> m1 >> dash >> d1 >> h1 >> colon >> min1;
            cin >> y2 >> dash >> m2 >> dash >> d2 >> h2 >> colon >> min2;
            
            long long start = toMinutes(y1, m1, d1, h1, min1);
            long long end = toMinutes(y2, m2, d2, h2, min2) + cleaningTime;
            
            events.push_back({start, +1});  // arrival
            events.push_back({end, -1});    // departure (after cleaning)
        }
        
        // Sort by time, with departures (-1) before arrivals (+1) at same time
        std::sort(events.begin(), events.end(), [](const auto& a, const auto& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;  // -1 before +1
        });
        
        int current = 0, maxRooms = 0;
        for (const auto& e : events) {
            current += e.second;
            maxRooms = max(maxRooms, current);
        }
        
        cout << maxRooms << "\n";
    }
    
    return 0;
}