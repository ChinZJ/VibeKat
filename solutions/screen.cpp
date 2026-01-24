#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<ll> vll;

#define pb push_back
#define fi first
#define se second

#define FOR(i, a, b) for (int i = int(a); i < int(b); i++)
#define REF(i, a, b) for (int i = int(a); i >= int(b); i--)


// Multiple by 2 use <<
// Divide by 2 use >>
#define isOn(S, j) (S & (1<<j))
#define setBit(S, j) (S |= (1<<j))                   // Turns ON bit j
#define clearBit(S, j) (S &= ~(1<<j))                // Turns OFF bit j
#define toggleBit(S, j) (S ^= (1<<j))                // Toggles bit j
#define LSOne(S) (S & (-S))                          // Finds least significant bit, returns 2^j
#define setAll(S, n) (S = (1<<n)-1)                  // turn ON ALL bits of size n

#define modulo(S, N) ((S) & (N-1))                   // returns S % N, where N is a power of 2 (2^N)
#define isPowerOfTwo(S) (!(S & (S-1)))               // Checks if S is a power of 2
#define nearestPowerOfTwo(S) (1<<lround(log2(S)))    // Finds the nearest power of 2
#define turnOffLastBit(S) ((S) & (S-1))              // Turns OFF the last bit
#define turnOnLastZero(S) ((S) | (S+1))              // Turns ON the last zero
#define turnOffLastConsecutiveBits(S) ((S) & (S+1))  // Turns OFF the last consecutive bits
#define turnOnLastConsecutiveZeroes(S) ((S) | (S-1)) // Turns ON the last consecutize zeroes

// __builtin_popcount(S): counts number of bits that are turned on in S
// __builtin_popcountll(S): ll version
// __builtin_ctz(S): counts number of trailing zeroes in S
// __builtin_clz(S): counts number of leading zeroes in S 


// 32bit ~ 2x10^9
// 64bit ~ 9x10^18

const int INF = INT_MAX;
const ll LLINF = LLONG_MAX;

// overloads cout for array printing
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) {
    for(auto &x : a) out << x << ' ';
    return out;
}; // allows cout << arr << "\n";

// From https://codeforces.com/blog/entry/62393
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// Example use: unordered_map<long long, int, custom_hash> safe_map;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b) * b);
}

ll pow(ll a, ll b) {
    ll res = 1; 
    while (b > 0) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    
}
// cout << fixed << setprecision(8) << ... for decimal precision

vector<vector<char>> grid;
queue<pair<int, int>> frac;
queue<pair<int, int>> sqt;
int R, C;
int c=0;
int r;
pii fracp;
pii sqtp;

int getval(int ipt = -1) {
    stringstream ss;
    if (ipt == -1) ipt = r;
    while (c < C && isdigit(grid[ipt][c])) {
        ss << grid[ipt][c];
        c++;
    }
    return stoi(ss.str());
}

int getsolve(stack<int> vals, stack<char> ops) {
    while (!ops.empty()) {
        int op1 = vals.top(); vals.pop();
        int op2 = vals.top(); vals.pop();
        if (ops.top() == '+') {
            vals.push(op2 + op1);
        } else {
            vals.push(op2 - op1);
        }
        ops.pop();
    }
    return vals.top();
}

int sfrac() {
    int st = fracp.se;
    int ed = fracp.se;
    while (!frac.empty() && frac.front().se == (ed+1)) {
        frac.pop();
        ed++;
    }

    stack<int> vals;
    stack<char> ops;
    int val;

    int tc = c;
    while (c <= ed) {
        if (isdigit(grid[0][c])) {
            val = getval(0);
        } else {
            if (grid[0][c] != ' ') ops.push(grid[0][c]);
            c++;
            continue;
        }

        if (!ops.empty() && ops.top() == '*') {
            ops.pop();
            int op1 = vals.top(); vals.pop();
            vals.push(op1 * val);
        } else if (!ops.empty() && ops.top() == '-') {
            ops.pop(); ops.push('+');
            vals.push(-val);
        } else {
            vals.push(val);
        }
    }

    int num = getsolve(vals, ops);
    while (!vals.empty()) vals.pop();
    while (!ops.empty()) ops.pop();
    c = tc;

    while (c <= ed) {
        if (isdigit(grid[2][c])) {
            val = getval(2);
        } else {
            if (grid[2][c] != ' ') ops.push(grid[2][c]);
            c++;
            continue;
        }

        if (!ops.empty() && ops.top() == '*') {
            ops.pop();
            int op1 = vals.top(); vals.pop();
            vals.push(op1 * val);
        } else if (!ops.empty() && ops.top() == '-') {
            ops.pop(); ops.push('+');
            vals.push(-val);
        } else {
            vals.push(val);
        }
    }
    int denom = getsolve(vals, ops);
    c = ed + 1;

    if (!frac.empty()) {
        fracp = frac.front(); frac.pop();
    }

    return (num / denom);
}

int ssqt() {
    int st = sqtp.se;
    int ed = sqtp.se;
    while (!sqt.empty() && sqt.front().se == (ed+1)) {
        sqt.pop();
        ed++;
    }

    stack<int> vals;
    stack<char> ops;
    int val;

    int tc = c;
    while (c <= ed) {
        if (isdigit(grid[r][c])) {
            val = getval();
        } else {
            if (grid[r][c] != ' ') ops.push(grid[r][c]);
            c++;
            continue;
        }

        if (!ops.empty() && ops.top() == '*') {
            ops.pop();
            int op1 = vals.top(); vals.pop();
            vals.push(op1 * val);
        } else if (!ops.empty() && ops.top() == '-') {
            ops.pop(); ops.push('+');
            vals.push(-val);
        } else {
            vals.push(val);
        }
    }

    int num = getsolve(vals, ops);
    c = ed + 1;

    if (!sqt.empty()) {
        sqtp = sqt.front(); sqt.pop();
    }

    return (int)sqrt(num);
}

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    cin >> R >> C;
    cin.ignore();

    // if 3 all is possible
    // if 2 no fraction
    // if 1 simple summation
    r = (R == 1) ? 0 : 1 ;

    grid.assign(R, vector<char>(C));

    string inpt;
    
    FOR(i, 0, R) {
        getline(cin, inpt);
        FOR(j, 0, C) {
            if (inpt[j] == '/' || inpt[j] == '\\') grid[i][j] = ' ';
            else grid[i][j] = inpt[j];
            
            if (grid[i][j] == '_') sqt.push({i, j});
            else if (grid[i][j] == '=') frac.push({i, j});
        }
    }

    fracp = {-1, -1};
    sqtp = {-1, -1};
    if (!sqt.empty()) {
        sqtp = sqt.front();
        sqt.pop();
    }
    if (!frac.empty()) {
        fracp = frac.front();
        frac.pop();
    }

    stack<int> vals;
    stack<char> ops;
    
    int val;
    char op;
    while (c < C) {
        if (c == fracp.se) val = sfrac();
        else if (c == sqtp.se) val = ssqt();
        else {
            if (isdigit(grid[r][c])) {
                val = getval();
            } else {
                if (grid[r][c] != ' ') ops.push(grid[r][c]);
                c++;
                continue;
            }
        }

        if (!ops.empty() && ops.top() == '*') {
            ops.pop();
            int op1 = vals.top(); vals.pop();
            vals.push(op1 * val);
        } else if (!ops.empty() && ops.top() == '-') {
            ops.pop(); ops.push('+');
            vals.push(-val);
        } else {
            vals.push(val);
        }
    }

    cout << getsolve(vals, ops) << '\n';

}