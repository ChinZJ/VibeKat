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

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     * Explore first half 
     * Explore second half
     * Merge together
     */

    int n; ll L; cin >> n >> L;
    vector<vll> adj(n, vll(n,0));
    FOR(i,0,n) {
        FOR(j,0,n) {
            cin >> adj[i][j];
        }
    }

    vector<vector<vll>> fwd((1 << n), vector<vll>(n)); fwd[1][0].pb(0);
    vector<vector<vll>> bwd((1 << n), vector<vll>(n)); 
    FOR(i,1,n) {
        bwd[(1 << i)][i].pb(adj[i][0]);
    }
    int mid = max(2, (n+2)/2); int inv=n-mid+1;
    int hi = max(mid, inv);
    
    FOR(mask, 0, (1 << n)) {
        if (__builtin_popcount(mask) > hi) continue;

        int tmp=mask;
        if ((mask & 1) == 1) {
            if (__builtin_popcount(mask) > mid) continue;

            // Save memory
            FOR(i,0,n) {
                auto& vv = fwd[mask][i];
                sort(ALL(vv));
                vv.erase(unique(ALL(vv)), vv.end());
            }

            if (__builtin_popcount(mask) < mid) { 
                for (int pos = LSOne(tmp); pos != 0; pos = (LSOne(tmp))) {
                    tmp ^= pos;
                    int idx = __builtin_ctz(pos);
                    FOR(i,0,n) {
                        if ((mask & (1 << i)) == 0) {
                            for (auto val : fwd[mask][idx]) {
                                // Save memory
                                if (val + adj[idx][i] <= L) fwd[(mask | (1 << i))][i].pb(val + adj[idx][i]);
                            }
                        }
                    }
                }
            }
            if (__builtin_popcount(mask) < mid) {
                FOR(i,0,n) { fwd[mask][i].clear(); fwd[mask][i].shrink_to_fit(); }
            }
        } else {
            // Save memory
            FOR(i,1,n) {
                auto& vv = bwd[mask][i];
                sort(ALL(vv));
                vv.erase(unique(ALL(vv)), vv.end());
            }

            if (__builtin_popcount(mask) < inv) {
                for (int pos = LSOne(tmp); pos != 0; pos = (LSOne(tmp))) {
                    tmp ^= pos;
                    int idx = __builtin_ctz(pos);

                    FOR(i,1,n) {
                        if ((mask & (1 << i)) == 0) {
                            for (auto val : bwd[mask][idx]) {
                                // Save memory
                                if (val + adj[idx][i] <= L) bwd[(mask | (1 << i))][i].pb(val + adj[idx][i]);
                            }
                        }
                    }
                }
            }
            if (__builtin_popcount(mask) < inv) {
                FOR(i,0,n) { bwd[mask][i].clear(); bwd[mask][i].shrink_to_fit(); }
            }
        } 
    }

    FOR(mask, 0, (1 << n)) {
        int pc = __builtin_popcount(mask);
        bool keep_fwd = (mask & 1) == 1 && pc == mid;
        bool keep_bwd = (mask & 1) == 0 && pc == inv;

        if (keep_bwd) {
            FOR(i,1,n) {
                auto& vv = bwd[mask][i];
                sort(ALL(vv));
                vv.erase(unique(ALL(vv)), vv.end());
            }
        } else if (!keep_fwd) {
            FOR(i,0,n) { fwd[mask][i].clear(); fwd[mask][i].shrink_to_fit(); }
            FOR(i,0,n) { bwd[mask][i].clear(); bwd[mask][i].shrink_to_fit(); }
        }
    }

    bool ok=false;
    int fin = (1 << n)-1;
    FOR(mask, 0, (1 << n)) {
        if ((mask & 1) == 0 || __builtin_popcount(mask) != mid) continue;

        int tmask = (fin ^ mask);

        int tmp=mask; tmp ^= 1;
        for (int pos = LSOne(tmp); pos != 0; pos = (LSOne(tmp))) {
            tmp ^= pos;
            int idx = __builtin_ctz(pos);

            int augmask = (tmask | pos);
            auto& vv = bwd[augmask][idx];
            for (auto val : fwd[mask][idx]) {
                auto it = lower_bound(vv.begin(), vv.end(), L - val);
                if (it != vv.end() && (*it) == (L-val)) {
                    ok = true; break;
                }
            }
            if (ok) break;
        }
        if (ok) break;
    }
    cout << (ok ? "possible\n" : "impossible\n");

}