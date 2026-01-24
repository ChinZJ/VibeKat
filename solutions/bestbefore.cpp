#include <bits/stdc++.h>
using namespace std;

bool isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

int daysInMonth(int month, int year) {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month];
}

int normalizeYear(int y) {
    if (y >= 0 && y <= 99) return 2000 + y;
    if (y >= 2000 && y <= 2999) return y;
    return -1;
}

bool isValidDate(int year, int month, int day) {
    int y = normalizeYear(year);
    if (y == -1) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, y)) return false;
    return true;
}

int main() {
    string input;
    cin >> input;
    
    int a, b, c;
    char slash;
    stringstream ss(input);
    ss >> a >> slash >> b >> slash >> c;
    
    int vals[3] = {a, b, c};
    vector<tuple<int, int, int>> validDates;
    
    sort(vals, vals + 3);
    do {
        int day = vals[0];
        int month = vals[1];
        int year = vals[2];
        
        if (isValidDate(year, month, day)) {
            int normYear = normalizeYear(year);
            validDates.push_back({normYear, month, day});
        }
    } while (next_permutation(vals, vals + 3));
    
    if (validDates.empty()) {
        cout << input << " is illegal" << endl;
    } else {
        // Find earliest date (tuple comparison works chronologically)
        auto earliest = *min_element(validDates.begin(), validDates.end());
        
        int y = get<0>(earliest);
        int m = get<1>(earliest);
        int d = get<2>(earliest);
        
        printf("%04d-%02d-%02d\n", y, m, d);
    }
    
    return 0;
}