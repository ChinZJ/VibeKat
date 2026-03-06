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
     * Requires LCA algorithm
     */

    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<vi> adj(n+1);
        int a,b;
        FOR(i,1,n) {
            cin >> a >> b;
            adj[a].pb(b); adj[b].pb(a);
        }

        vi seq(n);
        FOR(i,0,n) {
            cin >> seq[i];
        }

        /**
         * LCA algorithm - up[u][j]
         *      If i start at node u, and leap 2^j steps upward, what node do i land on
         *      Consider 2^0, that will be its immediate parent
         * 
         *      To jump, say 4 steps (2^2)
         *          First jump 2 steps (2^1), and then do another (2^1)
         *          The formula is thus up[u][j] = up[ up[u][j-1] ][j-1]
         */
        vector<vi> up(n+1, vi(17,0));
        vi depth(n+1);
        auto dfs=[&](auto& self, int u, int p, int d) -> void {
            depth[u] = d;

            // LCA base case
            up[u][0] = p;
            FOR(j,1,17) {
                up[u][j] = up[up[u][j-1]][j-1];
            }
            
            for (auto v  : adj[u]) {
                if (v != p) {
                    self(self, v, u, d+1);
                }
            }
        };

        dfs(dfs, 1, 1, 0);

        auto getLca=[&](int u, int v) -> int {
            if (depth[u] < depth[v]) swap(u,v);

            /**
             * If there is a difference (lopsided), 
             * need to bring the deeper node (u) up to the same depth as (v)
             */
            int diff = depth[u] - depth[v];
            // Binary leaping
            FOR(j,0,17) {
                if (diff >> j & 1) u = up[u][j];
            }

            // if u and v are now the same node, then v was the ancestor
            if (u == v) return u;

            /**
             * u and v are different nodes, leap together until they reach a shared parent
             * 
             * Greedily try the biggest leaps
             */
            REF(j,16,0) {
                if (up[u][j] != up[v][j]) { 
                    // Still different, meaning the leap was safe and they are still below the LCA
                    u = up[u][j];
                    v = up[v][j];
                }
                // Do not know if overshot and thus do not make the leap, try a smaller leap size
            }

            // Since we never make the final step, we will always be one single step below the true LCA
            return up[u][0];
        };


        bool ok=true;
        FOR(i,0,n-1) {
            if (depth[seq[i]] + depth[seq[i+1]] - (2 * depth[getLca(seq[i],seq[i+1])]) > 3) {
                ok = false; break;
            }
        }
        cout << (ok ? 1 : 0) << '\n';
    }
}