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

#define unordered_map umap

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

const ll MOD = 998'244'353;
const int MAXN = 100'005;

vi adj[MAXN];
ll a[MAXN];
int dfn[MAXN], fa[MAXN], low[MAXN]; // depth first number (discovery time)
                                    // parent array (father)
                                    // highest ancestor that can be reached from node subtree
                                        // When low[v] > dfn[u], child v has no way to loop back up
                                        // If low[v] <= dfn[u] then edge is aprt of a cycle
                                        // skip the tree merge (see below) and let mini DP handle it
int timer=0;                        // global clock

struct State {
    // count, sum of all sets and sum of squared sets
    ll c,s,sq;
};

State dp[MAXN][2];

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     * DP on cactus graph (connected graph where every edge lies in at most one simple cycle)
     * 
     * First consider a Tree DP (no cycles, start from leaves)
     *      Two states to be maintained
     *      dp[u][0]: size of maximum independent set in the subtree rooted at u but u is EXCLUDED from the set
     *      dp[u][1]: size of ...   but u is INCLUDED in the set
     * 
     *      1. Look at all its children v
     *      2.1 If (include u) 
     *          Strictly forbidden from including any of its direct children v
     *          Thus take the state where the child is excluded
     *          dp[u][1] = 1 + sum(dp[v][0]) for all children v
     *      2.2 Else (exclude u)
     *          Children v can either be included or excluded
     *          dp[u][0] = sum(max(dp[v][0], dp[v][1])) for all children v
     * 
     *      Final answer will simply be max(dp[1][0], dp[1][1])
     * 
     * Now considering the existence of simple cycles
     *      Suppose we explore a branch that reaches a node w that points back to u, 
     *      this cycle can easily be traced backwards from w to u to get the exact sequence
     * 
     *      Pull said cycle into a flat array and run a mini dp on this array
     *          Case 1: exclude u 
     *              Then the rest of the array v_1, ..., w behaves like a standard line graph
     *          Case 2: include u
     *              Then v_1 and w must strictly be excluded, the rest of the nodes can behave normally
     * 
     *      Once both cases have been computed, store them directly into dp[u][0] and dp[u][1] 
     */

    int n,m; cin >> n >> m;

    FOR(i,1,n+1) cin >> a[i];

    FOR(i,0,m) {
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // Add two disjoint sets of valid indpenedent sets together
    auto addState = [&](State A, State B) -> State {
        State res;
        res.c = (A.c + B.c) % MOD;
        res.s = (A.s + B.s) % MOD;
        res.sq = (A.sq + B.sq) % MOD;
        return res;
    };

    /**
     * Merge child subtree into parent subtree
     * 
     * When we attach a child subtree to a parent subtree, 
     *      any valid set from the parent (U) can be paired with 
     *      any valid set from the child (V)
     * 
     * The total score can thus be seen as 
     *      (sum from i = 1 to cA) (sum from j = 1 to cB) (x_i + y_j)^2
     *          (x_i + y_j)^2 = x_i^2 + 2x_i y_j + y_j^2
     *          Split into 3 parts
     *              The first part becomes cB * sqA
     *              The second becomes 2 * sA * sB
     *              The last part becomes cA * sqB
     * 
     * The problem asks for the sum of squares of all these new combinations
     * Compress the information into the State struct {c, s, sq}
     *      sq new = (sqA * cB) + (2 * sA * sB) + (cA * sqB)
     */
    auto mergeState = [&](State A, State B) -> State {
        State res;
        res.c = (A.c * B.c) % MOD;
        res.s = ((A.s * B.c) % MOD + (A.c * B.s) % MOD) % MOD;

        // sq = A.sq * B.c + 2 * A.s * B.s + A.c * B.sq
        ll term1 = (A.sq * B.c) % MOD;
        ll term2 = (2LL * A.s % MOD * B.s) % MOD;
        ll term3 = (A.c * B.sq) % MOD;
        res.sq = (term1 + term2 + term3) % MOD;
        
        return res;
    };

    auto dfs = [&](auto& self, int u, int p) -> void {
        dfn[u] = low[u] = ++timer;
        fa[u] = p;

        // Base case just node by itself
        dp[u][0] = {1,0,0};

        // Included
        dp[u][1] = {1, a[u]%MOD, (a[u]%MOD * a[u]%MOD) % MOD};

        for (int v : adj[u]) {
            if (v==p) continue;

            if (dfn[v] == 0) { // unvisited
                self(self, v, u);
                low[u] = min(low[u], low[v]); // Update what ancestor can be reached

                // Only merge immediately if this is a pure tree edge
                if (low[v] > dfn[u]) {
                    // If u is excluded, v can be anything
                    State childAny = addState(dp[v][0], dp[v][1]);
                    dp[u][0] = mergeState(dp[u][0], childAny);

                    // If u is included, v must be excluded
                    dp[u][1] = mergeState(dp[u][1], dp[v][0]);
                }   
            } else {
                // Back edge detected, cycle is found
                // Update low to register the cycle
                low[u] = min(low[u], dfn[v]);
            }
        }

        // Cycle mini DP
        for (int v : adj[u]) {
            // if dfn[v] > dfn[u] and not parent, v is a descendent that points back
            // u is thus the top of the cycle and v is the bottom
            if (dfn[v] > dfn[u] && fa[v] != u) {
                // Extract cycle into flat array
                vi cycle; cycle.reserve(n);
                int curr = v;
                while (curr != u) {
                    cycle.pb(curr);
                    curr = fa[curr];
                }
                // cycle starts from v and traces back to u. 
                // note that u is NOT in the cycle

                int k = sz(cycle);

                // Run mini dp
                // Case 1: top node u is excluded, cycle array acts like normal line graph
                State f0 = dp[cycle[0]][0]; // if current node is excluded
                State f1 = dp[cycle[0]][1]; // if current node is included

                FOR(i,1,k) {
                    int node = cycle[i];
                    // if current node is excluded, previous node in chain can be anything (add f0 and f1)
                    State nextf0 = mergeState(dp[node][0], addState(f0, f1));
                    // if current node included, previous node must be excluded
                    State nextf1 = mergeState(dp[node][1], f0);
                    f0 = nextf0;
                    f1 = nextf1;
                }
                State cycleResExcl = addState(f0, f1);
                dp[u][0] = mergeState(dp[u][0], cycleResExcl);

                // Case 2: top node u is included
                f0 = dp[cycle[0]][0];
                f1 = {0,0,0}; // forbid cycle[0] from being included
                              // Any state trying to build off cycle[0] being included multiplies 0 and dies off

                FOR(i,1,k) {
                    int node = cycle[i];
                    State nextf0 = mergeState(dp[node][0], addState(f0,f1));
                    State nextf1 = mergeState(dp[node][1], f0);
                    f0 = nextf0;
                    f1 = nextf1;
                }
                State cycleResIncl = f0; // Take f0 to force cycle[k-1] to be excluded
                                         // f1 represents the chain where the node before u is included (cannot have this!)
                dp[u][1] = mergeState(dp[u][1], cycleResIncl);
            }
        }
    };


    dfs(dfs, 1,0);
    State finalState = addState(dp[1][0], dp[1][1]);
    cout << finalState.sq << '\n';
    
}