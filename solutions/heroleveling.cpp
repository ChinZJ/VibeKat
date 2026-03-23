#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef tuple<int, int, int> tiii;

#define umap unordered_map 

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

ll pow(ll a, ll b, ll mod=1) {
    ll res = 1; 
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res%mod;
}

long double pow(long double a, ll b) {
    bool mult=true;
    if (b<0) {
        b=-b; mult=false;
    }
    
    long double res=1;
    while (b > 0) {
        if (b&1) {
            res = (mult) ? (res*a) : (res/a);
        }
        a = (a*a);
        b >>= 1;
    }
    return res;
}

long long mul(ll x, ll y, ll MOD) { return (x%MOD) * (y%MOD) % MOD; }
long long add(ll x, ll y, ll MOD) { return (x+y) %MOD; }
long long sub (ll x, ll y, ll MOD) { return (x-y+MOD) % MOD; }


// Read K values and ignore the rest
// cin >> a >> b >> c;
// cin.ignore(numeric_limits<streamsize>::max(), '\n');
// Use cin.ignore() before getline()

// cout << fixed << setprecision(8) << ... for decimal precision


// cout << setw(10) << 42 << "\n";           // "        42" (right-aligned)
// cout << left << setw(10) << 42 << "\n";   // "42        " (left-aligned)
// cout << setfill('0') << setw(5) << 42 << "\n";  // "00042" (zero-padded)

const ll MOD1 = 998244353;
const ll MOD2 = 1000000007;
const ll EPS=1e-8;

const int MAXN=100'005;
const int B = 2160; // N^(2/3)


signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     */

    int n,k; ll l; cin >> n >> k >> l;

    vector<array<ll,3>> quests(n);
    FOR(i,0,n) cin >> quests[i][0] >> quests[i][1] >> quests[i][2];

    // Sort by M_i (min level required)
    // Optimal ordering on a subset of quests is always from easiest
    sort(quests.begin(), quests.end());

    int MAXT = 150;
    int MAXCOST = n * MAXT;
    ll ans = LLONG_MAX;

    // For a fixed t, each quest has independent cost c_i = max(0, T_i - t)
        // Find a feasible subset reaching level L that minimizes total cost
        // Candidate answer is K*t + total cost
    REP(t,0,MAXT) {
        /**
         * 0 - 1 knapsack
         * dp[j] = maximum level reachable using quest whose total cost sums to j
         */
        vll dp(MAXCOST+1, -1); dp[0] = 0;

        /**
         * For any fixed set S and any value of t
         * k * t _ sum( max(0, T_i - t) ) >= top K sum of S
         * A wrong t can never produce a value below the true answer and can only overcount
         */
        FOR(i,0,n) {
            ll minlvl = quests[i][0];
            ll xi = quests[i][1];
            int ci = max(0LL, quests[i][2] - t); // Cost under threshold t

            REF(j, MAXCOST - ci, 0) {
                /**
                 * Iterate j backwardds to ensure each quest used at most once
                 * Check dp[j] >= minlvl (enough level to do quest i)
                 *      If yes, transsition to dp[j + ci] with level dp[j] + xi
                 */
                if (dp[j] >= minlvl) {
                    dp[j+ci] = max(dp[j+ci], dp[j] + xi);
                }
            }
        }

        REP(j,0,MAXCOST) {
            if (dp[j] >= l) {
                ans = min(ans, (ll)k * t +j);
                break;
            }
        }
    }
    cout << ans << '\n';
}