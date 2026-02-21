#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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

ll binpow(ll a, ll b, ll mod=1) {
    ll res = 1;
    a%=mod;
    while (b > 0) {
        if (b & 1) {
            res = (res * a)%mod;
        }
        a = (a * a) % mod;
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


ll binomial(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k==0 || k==n) return 1;

    if (k > n-k) k=n-k;

    ll res=1;
    for (int i=0;i<k;i++) {
        res=res*(n-i)/(i+1);
    }
    return res;
}

template<typename T>
struct Dinic {
    struct Edge {
        int to, rev; // destination vertex
                     // index of reverse edge
        T c, oc;     // current residual capacity
                     // original capacity
        T flow() { return max(oc - c, T(0)); }
    };
    
    vector<int> lvl, ptr, q;
    vector<vector<Edge>> adj;
    
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    
    // Adds edge a - b with capacity c and b - a with capacity rcap
    void addEdge(int a, int b, T c, T rcap = 0) {
        adj[a].push_back({b, (int)adj[b].size(), c, c});
        adj[b].push_back({a, (int)adj[a].size() - 1, rcap, rcap});
    }
    

    T dfs(int v, int t, T f) {
        if (v == t || !f) return f; // Either reach sink
                                    // Or no flow
        for (int& i = ptr[v]; i < (int)adj[v].size(); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1) { // Only follow level graph
                T p = dfs(e.to, t, min(f, e.c));
                if (p) {
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
                while (T p = dfs(s, t, numeric_limits<T>::max())) {
                    flow += p;
                }
            } while (lvl[t]); // lvl[t] is non zero if reachable from source
        }
        return flow;
    }
    
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,k,h; cin >> n >> k >> h;
    vector<vi> height(n,vi(n));
    FOR(i,0,n) {
        FOR(j,0,n) {
            cin >> height[i][j];
        }
    }

    auto IN=[&](int t, int i, int j) { return 2*(t*n*n + i*n + j);};
    auto OUT=[&](int t, int i, int j) { return 2*(t*n*n + i*n + j) + 1;};

    int totN=2*n*n*(h+1);
    int src=totN, snk=totN+1;
    Dinic<ll> flow(totN+2);

    int r,c;
    FOR(i,0,k) {
        cin >> r >> c;
        flow.addEdge(src,IN(0,r,c), 1);
        flow.addEdge(IN(0,r,c), OUT(0,r,c), 1);
    }

    int fh;
    vector<pii> mv={{0,0},{0,1},{1,0},{-1,0},{0,-1}};

    int nx,ny;
    REP(hh,1,h) {
        cin >> fh;
        FOR(i,0,n) {
            FOR(j,0,n) {
                for (auto [xx,yy]:mv) {
                    nx=i+xx; ny=j+yy;
                    if (nx>=0 && nx<n && ny>=0 && ny<n) {
                        flow.addEdge(OUT(hh-1,nx,ny), IN(hh,i,j),1);
                    }
                }

                if (height[i][j]<=fh) continue;

                flow.addEdge(IN(hh,i,j), OUT(hh,i,j), 1);

                if (hh==h) flow.addEdge(OUT(hh,i,j), snk, 1);
            }
        }
    }

    cout << flow.calc(src,snk) << '\n';

}