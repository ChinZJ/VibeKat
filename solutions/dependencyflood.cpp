#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
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
     * 
     */

    int N,M,K; cin >> N >> M >> K;

    vector<vi> fwdadj(N+1); // successors of u
    vector<vi> revadj(N+1); // predecessors of v

    vi dpin(N+1, 1);  // longest path ending at v
    vi dpout(N+1, 1); // longest path starting at v

    FOR(i,0,M) {
        int a,b; cin >> a >> b;
        fwdadj[a].pb(b);
        revadj[b].pb(a);
    }

    // Compute initial dpin in topological order
    // Edges fo from u -> v with u < v
    REP(v,1,N) {
        for (int u : revadj[v]) {
            dpin[v] = max(dpin[v], dpin[u] + 1);
        }
    }

    // Compute initial dpout (decreasing order)
    REF(v,N,1) {
        for (int w : fwdadj[v]) {
            dpout[v] = max(dpout[v], dpout[w] + 1);
        }
    }

    int Q; cin >> Q; while (Q--) {
        int C,D; cin >> C >> D;

        if (dpin[C] + dpout[D] > K) {
            cout << "reject\n"; continue;
        }

        cout << "accept\n";

        fwdadj[C].pb(D);
        revadj[D].pb(C);

        // Propagate dpin forward 
        if (dpin[C] + 1 > dpin[D]) {
            queue<int> q;
            dpin[D] = dpin[C] + 1;
            q.push(D);

            while (!q.empty()) {
                int v=q.front(); q.pop();
                for (int w : fwdadj[v]) {
                    if (dpin[v] + 1 > dpin[w]) {
                        dpin[w] = dpin[v] + 1;
                        q.push(w);
                    }
                }
            }
        }

        if (dpout[D] + 1 > dpout[C]) {
            queue<int> q;
            dpout[C] = dpout[D] + 1;
            q.push(C);

            while (!q.empty()) {
                int v=q.front(); q.pop();
                for (int u : revadj[v]) {
                    if (dpout[v] + 1 > dpout[u]) {
                        dpout[u] = dpout[v] + 1;
                        q.push(u);
                    }
                }
            }
        }
    }
}