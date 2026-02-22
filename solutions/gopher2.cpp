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

// Read K values and ignore the rest
// cin >> a >> b >> c;
// cin.ignore(numeric_limits<streamsize>::max(), '\n');
// Use cin.ignore() before getline()

// cout << fixed << setprecision(8) << ... for decimal precision


// cout << setw(10) << 42 << "\n";           // "        42" (right-aligned)
// cout << left << setw(10) << 42 << "\n";   // "42        " (left-aligned)
// cout << setfill('0') << setw(5) << 42 << "\n";  // "00042" (zero-padded)

// Prevents misuse of raw edge
struct EdgeRef {
    int from; // source vertex of forward edge
    int idx;  // index into adj[from]
};

template<typename T>
struct Dinic {
    // Raw edge to be used by Dinic
    struct Edge {
        int to;  // destination vertex
        int rev; // index of reverse edge
                     
        T c;     // current residual capacity
        T oc;    // original capacity
                     
        [[nodiscard]] T flow() const { return max(oc - c, T(0)); }
    };

    struct FlowEdge {
        int from;
        int to;

        T flow;
        T capacity;
    };
    
    vector<int> lvl, ptr, q;
    vector<vector<Edge>> adj;
    
    explicit Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    
    // Adds edge a - b with capacity c and b - a with capacity rcap
    EdgeRef addEdge(int a, int b, T c, T rcap = 0) {
        int const idx = static_cast<int>(adj[a].size());
        adj[a].push_back({b, static_cast<int>(adj[b].size()), c, c});
        adj[b].push_back({a, idx, rcap, rcap});
        return {a, idx};
    }

    // Modify capacity of an existing edge
        // Adjusts residual capacity to preserve current flow where possible
        // If newCap < current flow, residual goes negative
        // (Call resetFlow() + calc() to restore a valid flow)
    // Returns true if resetFlow() is required before calling calc()
    [[nodiscard]] bool updateEdge(EdgeRef ref, T newCap) {
        Edge& e = adj[ref.from][ref.idx];
        T const currentFlow = e.oc - e.c; // Flow currently pushed
        e.oc = newCap;
        e.c = newCap - currentFlow;

        return newCap < currentFlow;
    }

    // Query flow on a specific edge
    [[nodiscard]] T getFlow(EdgeRef ref) const {
        return adj[ref.from][ref.idx].flow();
    }

    // Reset all flows to zero
    void resetFlow() {
        for (auto& edges : adj) {
            for (auto& e : edges) {
                e.c = e.oc;
            }
        }
    }

    // Trace all active flows
    // Callback signature: void(int from, int to, T flow, T capacity)
    template<typename Func>
    void forEachFlow(Func&& func) const {
        for (int u = 0; u < static_cast<int>(adj.size()); ++u) {
            for (auto const& e : adj[u]) {
                if (T const f = e.flow(); f > 0 && e.oc > 0) {
                    func(u, e.to, f, e.oc);
                }
            }
        }
    }

    // Decompose flow into individual paths
    // Note: Only works for DAGs
    // TODO relaxation from DAG to general graphs
    [[nodiscard]] std::vector<std::vector<EdgeRef>> decomposePaths(int s, int t) const {
        std::vector<std::vector<T>> flows(adj.size());
        for (int u = 0; u < static_cast<int>(adj.size()); ++u) {
            flows[u].resize(adj[u].size());
            for (int i = 0; i < static_cast<int>(adj[u].size()); ++i) {
                auto const& e = adj[u][i];
                T const f = e.oc - e.c;
                flows[u][i] = (e.oc > 0) ? std::max(f, T(0)) : T(0);
            }
        }

        std::vector<std::vector<EdgeRef>> paths;

        while (true) {
            std::vector<EdgeRef> path;
            std::vector<bool> visited(adj.size(), false);

            auto dfs = [&](auto&& self, int u) -> bool {
                if (u == t) return true;
                
                visited[u] = true;
                for (int i = 0; i < static_cast<int>(adj[u].size()); ++i) {
                    auto const& e = adj[u][i];
                    if (!visited[e.to] && flows[u][i] > 0) {
                        path.push_back({u,i});
                        if (self(self, e.to)) return true;

                        path.pop_back();
                    }
                }
                return false;
            };

            if (!dfs(dfs, s)) break;

            T bottleneck = std::numeric_limits<T>::max();
            for (auto const& ref : path) {
                bottleneck = std::min(bottleneck, flows[ref.from][ref.idx]);
            }

            for (auto const& ref: path) {
                flows[ref.from][ref.idx] -= bottleneck;
            }

            paths.push_back(std::move(path));
        }
        
        return paths;
    }
    

    T dfs(int v, int t, T f) {
        if (v == t || !f) return f; // Either reach sink
                                    // Or no flow
        for (int& i = ptr[v]; i < static_cast<int>(adj[v].size()); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1) { // Only follow level graph
                if (T p = dfs(e.to, t, min(f, e.c)); p) {
                    e.c -= p; // Decrease forward edge
                    adj[e.to][e.rev].c += p; // Increase backward edge
                    return p;
                }
            }
        }
        return 0;
    }
    
    T calc(int s, int t) {
        T flow = 0;
        q[0] = s;
        for (int L = 0; L < 31; L++) { // Scaling optimization
                                       // Consider edges with large capacity, then smaller edges to reduce number of augmenting paths required
            do {
                // BFS to build level graph
                lvl.assign(adj.size(), 0); // Distance from source, 0 = unreachable
                ptr.assign(adj.size(), 0); // Tracks which edges (in the form of indices to adj) to try
                int qi = 0, qe = 1; // manual queue
                lvl[s] = 1;
                while (qi < qe && !lvl[t]) {
                    int v = q[qi++];
                    for (Edge& e : adj[v]) { // Note that for each iteration, edge is constantly being updated, previous paths will not be considered
                        if (!lvl[e.to] && e.c >> (30 - L)) { // simple check will just be e.c > 0 instead of optimization
                            q[qe++] = e.to;
                            lvl[e.to] = lvl[v] + 1;
                        }
                    }
                }
                
                // Without optimization will require additional line
                // if (!lvl[t]) break;

                // DFS to find blocking flow
                while (T const p = dfs(s, t, numeric_limits<T>::max())) {
                    flow += p;
                }
            } while (lvl[t]); // lvl[t] is non zero if reachable from source
        }
        return flow;
    }
    
    [[nodiscard]] bool leftOfMinCut(int a) const { return lvl[a] != 0; }

    // Returns edges crossing the min cut
    [[nodiscard]] std::vector<FlowEdge> minCutEdges() const {
        std::vector<FlowEdge> cut;
        for (int u = 0; u < static_cast<int>(adj.size()); ++u) {
            if (!leftOfMinCut(u)) continue;
            for (auto const& e : adj[u]) {
                if (!leftOfMinCut(e.to) && e.oc > 0) {
                    cut.push_back({u, e.to, e.flow(), e.oc});
                }
            }
        }
        return cut;
    }
};

// auto IN=[&](int t, int i, int j) { return 2*(t*n*n + i*n + j);};
// auto OUT=[&](int t, int i, int j) { return 2*(t*n*n + i*n + j) + 1;};

const ll MOD1 = 998244353;
const ll MOD2 = 1000000007;

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n,m; double s,v;
    while (cin >> n >> m >> s >> v) {
        double x,y;

        auto IN=[&](int a) { return a+n; };

        Dinic<ll> flow(2+n+m+m);
        int src=0,snk=1+n+m+m;
        for (int j=1; j<=m; ++j) {
            flow.addEdge(IN(j), snk, 1);
        }

        vector<pair<double, double>> glocs(n+1);
        for (int i=1; i<=n; ++i) {
            cin >> x >> y;
            glocs[i]={x,y};
            flow.addEdge(src,i,1);
        }

        for (int i=1; i<=m; ++i) {
            cin >> x >> y;
            for (int j=1; j<=n; ++j) {
                auto [xx,yy]=glocs[j];
                if (sqrt((x-xx)*(x-xx) + (y-yy)*(y-yy)) / v <= s) {
                    flow.addEdge(j,IN(i),1);
                }
            }
        }

        cout << n-flow.calc(src,snk) << '\n';
    }

}