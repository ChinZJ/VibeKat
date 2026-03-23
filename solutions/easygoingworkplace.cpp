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
     * N employees [1,N] where 1 is the CEO and every other employee has exactly one direct boss B_i
     *      Rooted tree at 1 is formed
     * 
     * Each employee has tolerance value A_i
     *      When N employees arrive one at a time (permutation we want to find), 
     *      look and count how many of own subordinates (below them in the tree) are in office doing work
     *          If count <= A_i (work)
     *          Else slack
     * 
     *      - Arrive early (before subtree): see 0 working subordinates -> always work
     *      - Arrive late (after subtree): see all working subordinates -> slack if count > A_i
     * 
     * Step 1: find the minimum possible workers per subtreee (bottom up)
     *      Observe that leaves will always work (no subordinates below them)
     *      For each node, if the number of workers is minimized per subtree, how many workers will the node get
     * 
     * Step 2: Check feasibility
     *      Anything from minworkers to N is feasible
     */

    int n,k; cin >> n >> k;

    vi a(n+1);
    FOR(i,1,n+1) cin >> a[i];

    vector<vi> child(n+1);
    FOR(i,2,n+1) {
        int b; cin >> b;
        child[b].pb(i);
    }

    // Post order to compute sizes[] and minworkers[]
    vi sizes(n+1, 1), minworkers(n+1, 0);
    vi postorder;
    {
        stack<pii> st; // {node, visited}
        st.push({1,0});
        while (!st.empty()) {
            auto [v,vis] = st.top(); st.pop();
            if (vis) {postorder.pb(v); continue;}
            st.push({v,1});
            for (int c : child[v]) st.push({c,0});
        }
    }
    for (int v : postorder) {
        int childsum=0;
        for (int c : child[v]) {
            sizes[v] += sizes[c];
            childsum += minworkers[c];
        }
        // For leaf, childsum = 0, thus minworkers = 1
        minworkers[v] = (childsum > a[v]) ? childsum : childsum + 1;
    }

    if (k < minworkers[1] || k > n) {
        cout << -1 << '\n'; return 0;
    }

    // Top down BFS to assign budget and work / slack
    vector<bool> works(n+1, false);
    vi budget(n+1, 0); budget[1] = k;
    {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            int b = budget[v];

            // v slacks iff we can put all b workers in children
            // requires     b > a[v]     (so v sees sufficiently many to slack) 
            //              b < sizes[v] (room in children, sizees[v] is the entire subtree including v itself)
            //                           (if b == sizes[v], then every person in the subtree must work, no room for v to slack)
            bool vslack = (b > a[v]) && (b < sizes[v]);
            works[v] = !vslack;

            int childbudget = vslack ? b : b-1;

            // distribute (give each child minworkers first then greedily fill)
            int rem=childbudget;
            for (int c : child[v]) {
                budget[c] = minworkers[c];
                rem -= minworkers[c];
            }
            for (int c : child[v]) {
                int extra = min(rem, sizes[c] - minworkers[c]);
                budget[c] += extra;
                rem -= extra;
                if (!rem) break;
            }

            for (int c : child[v]) q.push(c);
        }
    }

    // Build permutaiton via DFS
        // works -> pre order (arrive before subordinates, see 0 workers <= A_i)
        // slacks -> post order (arrive after subordinates, see b workers > A_i)
    vi perm; perm.reserve(n);
    {
        stack<pii> st;  st.push({1,0});
        while (!st.empty()) {
            auto [v,vis] = st.top(); st.pop();
            if (vis) {
                if (!works[v]) perm.pb(v); continue;
            }
            if (works[v]) perm.pb(v);
            st.push({v,1});
            for (int i = sz(child[v]) - 1; i>=0; --i) {
                st.push({child[v][i], 0});
            }
        }
    }

    FOR(i,0,n) {
        cout << perm[i] << ' ';
    }
    cout << '\n';

}