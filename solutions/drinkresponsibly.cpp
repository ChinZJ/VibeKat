#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, int, int> tiii;

#define pb push_back
#define fi first
#define se second

#define elif else if

#define sz(x) (int)(x).size()

#define FOR(i, a, b) for (int i = int(a); i < int(b); i++)
#define REP(i, a, b) for (int i = int(a); i <= int(b); i++)
#define REF(i, a, b) for (int i = int(a); i >= int(b); i--)

#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

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

// Read K values and ignore the rest
// cin >> a >> b >> c;
// cin.ignore(numeric_limits<streamsize>::max(), '\n');
// Use cin.ignore() before getline()

// cout << fixed << setprecision(8) << ... for decimal precision


// cout << setw(10) << 42 << "\n";           // "        42" (right-aligned)
// cout << left << setw(10) << 42 << "\n";   // "42        " (left-aligned)
// cout << setfill('0') << setw(5) << 42 << "\n";  // "00042" (zero-padded)

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    double a,b; cin >> a >> b;
    int m=(int)round(a*100), u=(int)round(b*30), d; cin >> d;

    unordered_map<string,int> name; unordered_map<int,string> revname; int uid=0;
    string s;
    unordered_map<int,pii> dstats;
    int str,sze,cst;
    FOR(i,0,d) {
        cin >> s;
        if (name.find(s)==name.end()) {
            name[s]=uid;
            revname[uid]=s;
        }
        cin >> str >> s >> a;
        if (s[2]=='1') sze=30;
        elif (s[2]=='2') sze=15;
        else sze=10;
        cst=(int)round(a*100);
        dstats[uid++]={str*sze,cst};
    }

    vector<vector<vi>> dp(m+1,vector<vi>(u+1,vi(uid+1,0))); dp[0][0][uid]=1;
    REP(i,0,m) {
        REP(j,0,u) {
            if (dp[i][j][uid]) {
                FOR(k,0,uid) {
                    auto& [dun,dcst]=dstats[k];
                    int ncst=dcst+i;
                    int nun=dun+j;
                    if (ncst<=m && nun<=u) {
                        FOR(l,0,uid) {
                            dp[ncst][nun][l]=dp[i][j][l];
                        }
                        dp[ncst][nun][k]++;
                        dp[ncst][nun][uid]=1;
                    }
                    if (dp[m][u][uid]) break;
                }
            }
            if (dp[m][u][uid]) break;
        }
        if (dp[m][u][uid]) break;
    }

    if (dp[m][u][uid]) {
        FOR(a,0,uid) {
            if (dp[m][u][a]) {
                cout << revname[a] << ' ' << dp[m][u][a] << '\n';
            }
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }
}