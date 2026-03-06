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

struct EdgeRef {
    int from; // source vertex of forward edge
    int idx;  // index into adj[from]
};

enum EdgeClass{ 
    IN_ALL,  // only bridge between S and T
    IN_SOME, // can appear in min cut, but alternatives exist
    IN_NONE, // never needed (residual e.c > 0)
};

#include <bits/extc++.h>  // for __gnu_pbds::priority_queue

template<typename T>
struct MCMF {
    static constexpr T INF = numeric_limits<T>::max() / 4;

    struct Edge {
        int to;
        int rev;

        T c;     // current residual capacity
        T oc;    // original capacity
        T cost;  // cost per unit flow

        [[nodiscard]] T flow() const { return max(oc - c, T(0)); }
    };

    struct FlowEdge {
        int from;
        int to;

        T flow;
        T capacity;
        T cost;
    };

    int N;
    vector<vector<Edge>> adj;
    vector<int> seen;
    vector<T> dist, pi;
    vector<int> parV, parI;   // parent vertex + edge index (replaces Edge* par)

    explicit MCMF(int N) : N(N), adj(N), seen(N), dist(N), pi(N), parV(N), parI(N) {}

    // Add edge from -> to with capacity cap, cost cost
    // Returns EdgeRef for queries / updates
    EdgeRef addEdge(int from, int to, T cap, T cost) {
        if (from == to) return {-1, -1};
        int const idx = static_cast<int>(adj[from].size());
        adj[from].push_back({to, static_cast<int>(adj[to].size()), cap, cap, cost});
        adj[to].push_back({from, idx, 0, 0, -cost});
        return {from, idx};
    }

    // Modify capacity of an existing edge
        // Adjusts capacity while preserving current flow where possible
        // Returns true if resetFlow() needs to be called prior to maxFlow()
    [[nodiscard]] bool updateEdge(EdgeRef ref, T newCap) {
        if (ref.from < 0) return false;
        Edge& e = adj[ref.from][ref.idx];
        T const currentFlow = e.oc - e.c;
        e.oc = newCap;
        e.c = newCap - currentFlow;
        return newCap < currentFlow;
    }

    // Query flow on a specific edge
    [[nodiscard]] T getFlow(EdgeRef ref) const {
        if (ref.from < 0) return 0;
        return adj[ref.from][ref.idx].flow();
    }

    // Qeury cost of a specific edge
    [[nodiscard]] T getCost(EdgeRef ref) const {
        if (ref.from < 0) return 0;
        return adj[ref.from][ref.idx].cost;
    }

    void resetFlow() {
        for (auto& edges : adj)
            for (auto& e : edges) e.c = e.oc;
        fill(pi.begin(), pi.end(), T(0));
    }

    // 5-arg callback: (from, to, flow, capacity, cost)
    template<typename Func>
    void forEachFlow(Func&& func) const {
        for (int u = 0; u < N; ++u)
            for (auto const& e : adj[u])
                if (T const f = e.flow(); f > 0 && e.oc > 0)
                    func(u, e.to, f, e.oc, e.cost);
    }

    // Dijkstra with Johnson's potentials
    void path(int s) {
        fill(seen.begin(), seen.end(), 0);
        fill(dist.begin(), dist.end(), INF);
        fill(parV.begin(), parV.end(), -1);
        dist[s] = 0;

        __gnu_pbds::priority_queue<pair<T, int>> q;
        vector<typename decltype(q)::point_iterator> its(N);
        q.push({0, s});

        while (!q.empty()) {
            int u = q.top().second; q.pop();
            seen[u] = 1;
            T di = dist[u] + pi[u];

            for (int i = 0; i < static_cast<int>(adj[u].size()); ++i) {
                Edge& e = adj[u][i];
                if (!seen[e.to] && e.c > 0) {
                    T val = di - pi[e.to] + e.cost;
                    if (val < dist[e.to]) {
                        dist[e.to] = val;
                        parV[e.to] = u;
                        parI[e.to] = i;
                        if (its[e.to] == q.end())
                            its[e.to] = q.push({-val, e.to});
                        else
                            q.modify(its[e.to], {-val, e.to});
                    }
                }
            }
        }
        for (int i = 0; i < N; i++)
            pi[i] = min(pi[i] + dist[i], INF);
    }

    // Returns {total_flow, total_cost}
    pair<T, T> maxflow(int s, int t, T flowLimit = INF) {
        T totflow = 0, totcost = 0;
        while (totflow < flowLimit) {
            path(s);
            if (!seen[t]) break;

            // Find bottleneck
            T fl = flowLimit - totflow;
            for (int v = t; v != s; v = parV[v])
                fl = min(fl, adj[parV[v]][parI[v]].c);

            // Augment
            totflow += fl;
            for (int v = t; v != s; v = parV[v]) {
                Edge& e = adj[parV[v]][parI[v]];
                totcost += fl * e.cost;
                e.c -= fl;
                adj[e.to][e.rev].c += fl;
            }
        }
        return {totflow, totcost};
    }

    // Bellman-Ford potential init — call BEFORE maxflow() if negative costs
    void setpi(int s) {
        fill(pi.begin(), pi.end(), INF);
        pi[s] = 0;
        int it = N, ch = 1;
        while (ch-- && it--) {
            for (int i = 0; i < N; i++) {
                if (pi[i] != INF) {
                    for (Edge& e : adj[i]) {
                        if (e.oc) {  // edge exists (original cap > 0)
                            T v = pi[i] + e.cost;
                            if (v < pi[e.to]) { pi[e.to] = v; ch = 1; }
                        }
                    }
                }
            }
        }
        assert(it >= 0); // negative cost cycle if fails
    }

    [[nodiscard]] bool leftOfMinCut(int a) const { return seen[a]; }

    [[nodiscard]] vector<FlowEdge> minCutEdges() const {
        vector<FlowEdge> cut;
        for (int u = 0; u < N; ++u) {
            if (!leftOfMinCut(u)) continue;
            for (auto const& e : adj[u])
                if (!leftOfMinCut(e.to) && e.oc > 0)
                    cut.push_back({u, e.to, e.flow(), e.oc, e.cost});
        }
        return cut;
    }

/**
================================================================================
                    CUT ANALYSIS AND BOTTLENECK DETECTION
================================================================================
 */
    vector<bool> reachS, reachT;

    void buildReachability(int s, int t) {
        reachS.assign(N, false);
        reachT.assign(N, false);
        vector<int> q(N);

        int qi = 0, qe = 1;
        q[0] = s; reachS[s] = true;
        while (qi < qe) {
            int u = q[qi++];
            for (auto const& e : adj[u])
                if (!reachS[e.to] && e.c > 0) {
                    reachS[e.to] = true;
                    q[qe++] = e.to;
                }
        }

        qi = 0; qe = 1;
        q[0] = t; reachT[t] = true;
        while (qi < qe) {
            int u = q[qi++];
            for (auto const& e : adj[u])
                if (!reachT[e.to] && adj[e.to][e.rev].c > 0) {
                    reachT[e.to] = true;
                    q[qe++] = e.to;
                }
        }
    }

    [[nodiscard]] bool isBottlneck(EdgeRef ref) const {
        if (ref.from < 0) return false;
        auto const& e = adj[ref.from][ref.idx];
        if (e.c > 0) return false;
        return reachS[ref.from] && reachT[e.to];
    }

    [[nodiscard]] EdgeClass classifyingEdge(EdgeRef ref) const {
        if (ref.from < 0) return IN_NONE;
        auto const& e = adj[ref.from][ref.idx];
        if (e.c > 0) return IN_NONE;
        if (reachS[ref.from] && reachT[e.to]) return IN_ALL;
        if (reachS[ref.from] || reachT[e.to]) return IN_SOME;
        return IN_NONE;
    }
};

// auto IN=[&](int t, int i, int j) { return 2*(t*n*n + i*n + j);};
// auto OUT=[&](int t, int i, int j) { return 2*(t*n*n + i*n + j) + 1;};

const ll MOD1 = 998244353;
const ll MOD2 = 1000000007;

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    /**
     * Conventional MCMF 
     */

    int n,m,s,t; cin >> n >> m >> s >> t;
    int u,v; ll c,w;
    MCMF<ll> flow(n);
    FOR(i,0,m) {
        cin >> u >> v >> c >> w;
        flow.addEdge(u,v,c,w);
    }
    // No negative costs
    auto [tf,tc] = flow.maxflow(s,t);
    cout << tf << ' ' << tc << '\n';
}