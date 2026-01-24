#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int fh, sh, fm, sm, fs, ss;
    char c;
    cin >> fh >> c >> fm >> c >> fs;
    cin >> sh >> c >> sm >> c >> ss;
    
    long long ft = (fh * 60 * 60) + (fm * 60) + fs;
    long long st = (sh * 60 * 60) + (sm * 60) + ss;
    st -= ft;
    if (st <= 0) st += (24 * 60 * 60);
    long long lmins = st / 60;
    int fins = st % 60;
    int finmins = lmins % 60;
    int finans = lmins / 60;
    
    cout << (finans < 10 ? "0" : "") << finans << ':'
        << (finmins < 10 ? "0" : "") << finmins << ':'
        << (fins < 10 ? "0" : "") << fins << '\n';
    return 0;
}