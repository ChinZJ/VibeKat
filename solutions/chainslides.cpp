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
     * TODO
     * 
     * 8 buttons arranged in a circle and M slide types, defined by {start, end, speed}
     * Pick K slides such that
     *      Form chain slides (one ends at the button the next starts, looping back to first starting point)
     *      All 8 buttons must be covered
     *      Speed range is minimized
     * 
     * Intuitively, we can maintain a sliding window to check if a subset of those slides works, 
     * and easily obtain the minimized range with a simple query (on the sorted order by speed)
     *      If the window has a feasible answer 
     *          1. Record said feasible answer
     *          2. Shrink from the left (to see if we can have a tighter bound on the answer)
     *      Else we increase on the right
     * 
     * Feasibility of a subset is the difficult part of this question
     *      Think of the 8 buttons as nodes in a directed graph.
     *      Each slide from button u to button v is a directed edge u -> v
     *      Selecting slides that forms cycles means we need the flow to be conserved at every node
     *      (what flows in must flow out) -> circulation in network flow
     *      
     *      Feasibility is thus: finding a circulation on 8 nodes where
     *          1. Edge u -> v carries at most count[u][v] flow (number of available slides from u to v)
     *          2. Total flow >= K
     *          3. Every button has flow >= 1 passing through it
     * 
     * MCMF formulation
     *      Goal: maximize (1) buttons covered, then (2) slides covered
     *          This can be merged into a single cost using LARGE = M + 1
     *          totalObjective = buttonsCovered * LARGE + slidesUsed
     *          Observe that MCMF minimizes cost, thus we simply negate everything and minimize it
     * 
     *      Vertex split: each button becomes u_in and u_out to put capacity / cost constraints on passing through a button
     *          1. u_out -> v_in        Capacity count[u][v]        Cost -1         Using a slide u -> v
     *             "There are count[u][v] available slides from u -> v, each using 1 slide"
     * 
     *          2. u_in -> u_out        Capacity sum(count[u][v])   Cost 0          Free pass through
     *             "Plain pass through, capacity capped at total outgoing slides from u, since its not possible to push more flow out of a button than there are slides leaving it"
     *             (Note: the capacity does not really matter here, it can never be abused, but to be accurate it should be sum(...) - 1 because of edge type 3.)
     * 
     *          3. u_in -> u_out        Capacity 1                  Cost -LARGE     Reward for covering u
     *             By making edge 3s cost -LARGE, MCMF always prioritizes covering buttons over using extra slides
     * 
     *      
     *      Technique: Pre saturation of negative cost edges
     *          Note: the removal of negative cost edges is just an added benefit, the main problem being the augmentation (pre saturation)
     * 
     *          The problem comes with augmenting such a circulation to have a source and a sink
     *          MCMF works correctly when you can start with "zero" flow and incrementally push flow along shortest paths
     *          However graph has negative cost edges (edge 1. and 3.)
     *          Thus, start from a state where ALL negative cost edges are already fully used, and let the algorithm undo the ones that do not belong
     * 
     *          1. u_out -> v_in    (Suppose capacity 3, cost -1)
     *              Pretend 3 units flowed along it already, thus v_in receives 3 extra units, and u_out loses 3 units
     *              Add an "undo edge" v_in -> u_out (capacity 3, cost 1) (reverse direction with negated cost)
     * 
     *          After pre saturation, every node has some excess or deficit
     *          (Both edges have cost 0, meant to supply / absorb imbalanced flow)
     *          source -> node with capacity = excess (positive excess)
     *          node -> sink   with capacity = |deficit| (negative deficit)
     *      
     *          Thus when running MCMF from source to sink, it finds the cheapest way to balance all the excessed and deficits
     *          For each pre saturated edge
     *              1. Keep it (do nothing)
     *              2. Undo it (send flow on the undo edge) which incurs cost but is necessary to make flow balance
     *                 Since undoing a coverage edge (buttons) (cost +LARGE) is more expensive than a slide (cost +1)
     *                 it will always sacrifice slides first before coverage
     * 
     *              FULL EXAMPLE
     *              Suppose we have 
     *                  1 slide A -> B     Capacity 1      Cost -3
     *                  1 slide B -> A     Capacity 1      Cost -1
     *                  1 slide A -> C     Capacity 1      Cost -2
     *                  Optimal circulation: push 1 unit around A -> B -> A (A -> C cannot be used)
     *                                       for (-3) + (-1) = -4
     * 
     *              Pre saturate everything: for every negative cost edge, assume its fully used
     *                  A -> B      excess[A] = -1;     excess[B] = +1;     excess[C] = 0;      precost = -3;
     *                  B -> A      excess[A] = 0;      excess[B] = 0;      excess[C] = 0;      precost = -4;
     *                  A -> C      excess[A] = -1;      excess[B] = 0;      excess[C] = 1;      precost = -6;
     * 
     *              Add undo edges
     *                           B -> A     Capacity 1      Cost 3
     *                           A -> B     Capacity 1      Cost 1
     *                           A -> A     Capacity 1      Cost 2
     * 
     *              Look at the excesses
     *                              excess[A] = -1;             add A -> Sink, cap 1, cost 0 (deficit)
     *                              excess[B] = 0               Balanced, do nothing
     *                              excess[C] = 1;              add Src -> C, cap 1, cost 0 (surplus)
     * 
     *              Running MCMF will cause it to push 1 unit from Src -> C -> A -> Snk (cost +2) ie. undo edge 3
     *                          
     * 
     *          totalCost = preCost + mcmfCost
     *              preCost is the cost assuming everything is used (negative)
     *              mcmfCost is the cost of undoing things
     * 
     *          totalCost will be negative, thus
     *          buttonsCovered = (-totalCost) / LARGE
     *          slidesUsed     = (-totalCost) % LARGE
     */

    int M,K; cin >> M >> K;

    vi X(M), Y(M), V(M);
    // Change to 0 index
    FOR(i,0,M) {
        cin >> X[i] >> Y[i] >> V[i];
        X[i]--; Y[i]--;
    }

    // Sort by speed, optimal selection forms a contiguous window in sorted order
    vi order(M);
    iota(ALL(order), 0);
    sort(ALL(order), [&](int a, int b) {return V[a] < V[b];});

    // Large constant to give enormous incentive for covering each button
    // Slides used <= M, set M+1
            // buttons_covered = neg_cost / LARGE
            // slides_used = neg_cost % LARGE
    int LARGE = M+1;

    // Count of slides from u to v
    vector<vi> count(8, vi(8,0));
    

    /**
     * Given a current set of count[u][v], 
     * find the maximum number of slides that can form valid cycles
     * while prioritizing covering all 8 buttons
     * 
     * MCMF Construction
     *      Split each button u into two nodes
     *          u_in: flow arrives at button u
     *          u_out: flow departs from button u
     * 
     *      Circulation edges
     *      Edge A: u_out -> v_in, cap count[u][v], cost -1
     *          Using a slide from u to v costs -1 (want to use slides)
     * 
     *      Edge B: u_in -> u_out, cap sum_v(count[u][v]), cost 0
     *          Pass through inside a button
     * 
     *      Edge C: u_in -> u_out, cap 1, cost -LARGE
     *          Covering button u gives huge reward
     * 
     * 
     *      KEY: because this is a circulation with no source and sink, 
     *          all negative cost edges needs to be "pre saturated"
     *      
     *          For each negative cost edge u -> v with capacity C, cost w (w < 0)
     *          - Pretend we already sent C units
     *          - Creates excess +C at v, deficit -C at u
     *          - Add an "undo" edge v -> u with cap C, cost -w (-w > 0)
     *            (Lets algorithm undo pre saturated flow)
     * 
     *      Then S -> each node with positive excess
     *           each node with negative excess -> T
     * 
     *      Run MCMF S -> T, where MCMF undoes pre saturated edges that should not be used
     * 
     * All edges in reduced graph have non negative cost
     */
    int offset_uin = 0;
    auto uin=[&](int i){return offset_uin + i;};
    int offset_uout = offset_uin + 8;
    auto uout=[&](int i){return offset_uout+i;};
    int src = offset_uout+8;
    int snk=src+1; 

    auto solve =[&]() -> pii {
        MCMF<int> mcmf(snk+1);

        int precost = 0;
        vi excess(snk+1);

        /**
         * Presaturate Edge A: u_out -> v_in, cap count[c][v], cost -1
         * Undo edge v_in -> u_out, cap[u][v], cost +1
         * 
         * Assume all slides are used, undo edge lets algorithm say "do not use slide at cost +1"
         */
        FOR(u,0,8) {
            FOR(v,0,8) {
                if (count[u][v] > 0) {
                    mcmf.addEdge(uin(v), uout(u), count[u][v], 1); // undo edge
                    excess[uin(v)] += count[u][v];
                    excess[uout(u)] -= count[u][v];
                    precost -= count[u][v];
                }
            }
        }

        /**
         * Presaturate Edge C: u_in -> u_out, cap 1, cost -LARGE
         * Undo edge: u_out -> u_in, cap 1, cost +LARGE
         * 
         * Assume all buttons are covered, undo edge lets algorithm say "skip this button at cost +LARGE"
         */
        FOR(u,0,8) {
            mcmf.addEdge(uout(u), uin(u), 1, LARGE);
            excess[uout(u)] += 1;
            excess[uin(u)] -= 1;
            precost -= LARGE;
        }

        /**
         * Edge B: (non negative cost) u_in -> u_out, cap = total ongoing slides from u, cost 0
         * 
         * "Flow passes through button u for free"
         */
        FOR(u,0,8) {
            int cap = 0;
            FOR(v,0,8) {
                cap += count[u][v];
            }
            if (cap > 0) mcmf.addEdge(uin(u), uout(u), cap, 0);
        }

        int totexcess = 0;
        FOR(i,0,src) {
            if (excess[i] > 0) {
                mcmf.addEdge(src, i, excess[i], 0);
                totexcess += excess[i];
            } elif (excess[i] < 0) {
                mcmf.addEdge(i, snk, -excess[i], 0);
            }
        }

        // Every node has been balanced, pre saturated state is a valid circulation
        if (totexcess == 0) {
            int negcost = -precost;
            return {negcost / LARGE, negcost % LARGE};
        }

        // All edge costs >= 0 no need to Bellman ford init
        auto [flow, cost] = mcmf.maxflow(src, snk);

        int totcost = precost + cost;
        int negcost = -totcost;
        int buttonscovered = negcost / LARGE;
        int slidesused = negcost % LARGE;

        return {buttonscovered, slidesused};
    };

    /**
     * TWO POINTER
     * IF [l,r] is feasible, record V[order[r]] - V[order[l]] and shrink from left
     * ELSE expand from right
     */
    int ans=-1;
    int l=0, r=-1;
    while (l < M) {
        auto [bc, su] = solve();

        if (bc == 8 && su >= K) {
            int range = (r >= l) ? V[order[r]] - V[order[l]] : 0;
            if (ans == -1) ans = range;
            else ans = min(ans, range);

            count[X[order[l]]][Y[order[l]]]--;
            ++l;
        } else {
            ++r;
            if (r >= M) break;
            count[X[order[r]]][Y[order[r]]]++;
        }
    }
    cout << ans << '\n';
}   

