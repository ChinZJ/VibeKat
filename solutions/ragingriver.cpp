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

#include <bits/stdc++.h>
#include <bits/extc++.h>  // for __gnu_pbds::priority_queue
using namespace std;

// Prevents misuse of raw edge indices
struct EdgeRef {
    int from; // source vertex of forward edge
    int idx;  // index into ed[from]
};

template<typename T>
struct MCMF {
    static constexpr T INF = numeric_limits<T>::max() / 4;
    
    struct Edge {
        int from; // source
        int to;   // destination
        int rev;  // index of reverse edge
                           
                            
        T cap;    // capacity
        T cost;   // cost per unit flow
        T flow;   // current flow

        [[nodiscard]] T residual() const { return cap - flow; }
    };

    struct FlowEdge {
        int from, to;
        T flow, capacity, cost;
    };
    
    int N;                      // number of vertices
    vector<vector<Edge>> ed;    // adjacency list
    vector<int> seen;           // visited flags for Dijkstra
    vector<T> dist;             // shortest distance in Dijkstra
    vector<T> pi;               // potential function (for handling negative costs)
    vector<Edge*> par;          // parent edge pointers (to reconstruct path)
    
    explicit MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}
    
    // Add edge from -> to with capacity cap, cost cost
    // Returns EdgeRef for queries / updates
    EdgeRef addEdge(int from, int to, T cap, T cost) {
        if (from == to) return {-1,-1};  // no self loops
        int const idx = static_cast<int>(ed[from].size());
        ed[from].push_back(Edge{from, to, static_cast<int>(ed[to].size()), cap, cost, 0});
        ed[to].push_back(Edge{to, from, idx, 0, -cost, 0});
        return {from, idx};
    }

    // Modify capacity of an existing edge
        // Adjusts capacity while preserving current flow where possible
        // Returns true if resetFlow() needs to be called prior to maxFlow()
    [[nodiscard]] bool updateEdge(EdgeRef ref, T newCap) {
        if (ref.from < 0) return false;
        Edge& e = ed[ref.from][ref.idx];
        T const currentFlow = e.flow;
        e.cap = newCap;

        // Reverse edge capacity is always 0 for forward edges in MCMF
            // Thus no adjustment is required, residual graphs stays consistent 
            // (residual = cap - flow)
        return newCap < currentFlow;
    }

    // Query flow on a specific edge
    [[nodiscard]] T getFlow(EdgeRef ref) const {
        if (ref.from < 0) return 0;
        return max(ed[ref.from][ref.idx].flow, T(0));
    }

    // Qeury cost of a specific edge
    [[nodiscard]] T getCost(EdgeRef ref) const {
        if (ref.from < 0) return 0;
        return ed[ref.from][ref.idx].cost;
    }

    // Reset all flows to zero (including potentials)
    void resetFlow() {
        for (auto& edges : ed) {
            for (auto& e : edges) {
                e.flow = 0;
            }
        }
        fill(pi.begin(), pi.end(), T(0));
    }

    // Iterate over all edges carrying positive flow.
    // Callback signature: void(int from, int to, T flow, T capacity, T cost)
    template<typename Func>
    void forEachFlow(Func&& func) const {
        for (int u = 0; u < N; ++u) {
            for (auto const& e : ed[u]) {
                if (e.flow > 0 && e.cap > 0) {
                    func(u, e.to, e.flow, e.cap, e.cost);
                }
            }
        }
    }

    // Decompose flow into individual paths
    // Note: Only works for DAGs
    // TODO relaxation from DAG to general graphs
    [[nodiscard]] vector<vector<EdgeRef>> decomposePaths(int s, int t) const {
        vector<vector<T>> flows(N);
        for (int u = 0; u < N; ++u) {
            flows[u].resize(ed[u].size());
            for (int i = 0; i < static_cast<int>(ed[u].size()); ++i) {
                auto const& e = ed[u][i];
                flows[u][i] = (e.cap > 0) ? max(e.flow, T(0)) : T(0);
            }
        }

        vector<vector<EdgeRef>> paths;

        while (true) {
            vector<EdgeRef> path;
            vector<bool> visited(N, false);

            auto dfs = [&](auto&& self, int u) -> bool {
                if (u == t) return true;
                visited[u] = true;
                for (int i = 0; i < static_cast<int>(ed[u].size()); ++i) {
                    auto const& e = ed[u][i];
                    if (!visited[e.to] && flows[u][i] > 0) {
                        path.push_back({u, i});
                        if (self(self, e.to)) return true;
                        path.pop_back();
                    }
                }
                return false;
            };

            if (!dfs(dfs, s)) break;

            T bottleneck = numeric_limits<T>::max();
            for (auto const& ref : path) {
                bottleneck = min(bottleneck, flows[ref.from][ref.idx]);
            }
            for (auto const& ref : path) {
                flows[ref.from][ref.idx] -= bottleneck;
            }

            paths.push_back(std::move(path));
        }

        return paths;
    }

    // Returns true if vertex a is on the source side of the min cut
        // Usable after calling maxflow()
    [[nodiscard]] bool leftOfMinCut(int a) const {
        return seen[a];
    }

    // Returns all edges crossing the min cut
    [[nodiscard]] vector<FlowEdge> minCutEdges() const {
        vector<FlowEdge> cut;
        for (int u = 0; u < N; ++u) {
            if (!leftOfMinCut(u)) continue;

            for (auto const& e : ed[u]) {
                if (!leftOfMinCut(e.to) && e.cap > 0) {
                    cut.push_back({u, e.to, e.flow, e.cap, e.cost});
                }
            }
        }
        return cut;
    }
    
    // Dijkstra to find shortest (min cost) path from s to all vertices
    void path(int s) {
        fill(seen.begin(), seen.end(), 0);
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        
        // GNU policy-based data structure: priority queue with modify operation
        __gnu_pbds::priority_queue<pair<T, int>> q;
        vector<typename decltype(q)::point_iterator> its(N);
        q.push({0, s});
        
        while (!q.empty()) {
            s = q.top().second;
            q.pop();
            seen[s] = 1;
            T di = dist[s] + pi[s];  // actual distance with potential
            
            for (Edge& e : ed[s]) {
                if (!seen[e.to] && e.residual() > 0) {
                    // Reduced cost: original cost adjusted by potentials
                    // This makes all edges non-negative (Johnson's trick)
                    T val = di - pi[e.to] + e.cost;
                    
                    // If path is shorter
                    if (val < dist[e.to]) {
                        dist[e.to] = val;
                        par[e.to] = &e;  // remember parent edge
                        
                        // Insert or update in priority queue
                        if (its[e.to] == q.end()) {
                            its[e.to] = q.push({-val, e.to});
                        } else {
                            q.modify(its[e.to], {-val, e.to});
                        }
                    }
                }
            }
        }
        
        // Update potentials for next iteration
        for (int i = 0; i < N; i++) {
            pi[i] = min(pi[i] + dist[i], INF);
        }
    }
    
    // Returns {max_flow, min_cost}
    // flowLimit caps how much flow to push (INF -> maximum flow possible across)
    pair<T, T> maxflow(int s, int t, T flowLimit = INF) {
        T totflow = 0, totcost = 0;

        // Keep finding min-cost augmenting paths
        while (totflow < flowLimit) {
            // runs path(s), then checks if t was reached
            path(s);
            if (!seen[t]) break;

            // Find bottleneck capacity along the path
            T fl = flowLimit - totflow;
            for (Edge* x = par[t]; x; x = par[x->from]) {
                fl = min(fl, x->residual());
            }
            
            totflow += fl;
            
            // Augment flow along the path
            for (Edge* x = par[t]; x; x = par[x->from]) {
                totcost += fl * x->cost;
                x->flow += fl;                    // increase forward flow
                ed[x->to][x->rev].flow -= fl;     // decrease backward flow
            }
        }

        return {totflow, totcost};
    }
    
    // Initialize potentials using Bellman-Ford
    // Call this before maxflow() if there are negative cost edges
    void setpi(int s) {
        fill(pi.begin(), pi.end(), INF);
        pi[s] = 0;
        
        int it = N, ch = 1;
        
        // Bellman-Ford: relax all edges up to N times
        while (ch-- && it--) {
            for (int i = 0; i < N; i++) {
                if (pi[i] != INF) {
                    for (Edge& e : ed[i]) {
                        if (e.cap) {  // edge has capacity
                            T v = pi[i] + e.cost;
                            if (v < pi[e.to]) {
                                pi[e.to] = v;
                                ch = 1;  // changed, need another iteration
                            }
                        }
                    }
                }
            }
        }
        
        assert(it >= 0);  // if it < 0, negative cost cycle exists
    }
};

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    int p,r,l; cin >> p >> r >> l;

    int src=0, snk=1;
    MCMF<ll> flow(2+r);
    int e1,e2;
    FOR(i,0,l) {
        cin >> e1 >> e2;
        e1+=2; e2+=2;
        flow.addEdge(e1,e2,1,1);
        flow.addEdge(e2,e1,1,1);
    }

    int hi=0;
    if (auto [mxflw, mincst] = flow.maxflow(src,snk, p); mxflw == p) {
        cout << mincst << '\n';
    } else {
        cout << (p-mxflw) << " people left behind\n";
    }
}