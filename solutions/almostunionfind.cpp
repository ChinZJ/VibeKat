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

struct DSUMove {
    vi parent;      // union_arr: standard DSU
    vi elem;        // move_arr: element → entry point
    vi setSize;
    vector<long long> setSum;
    
    DSUMove(int n) : parent(n), elem(n), setSize(n, 1), setSum(n) {
        iota(parent.begin(), parent.end(), 0);
        iota(elem.begin(), elem.end(), 0);
        iota(setSum.begin(), setSum.end(), 0LL);
    }
    
    // flatten only the node itself because move changes union sets
    // jump from elem to parent so previous trees with old root is maintained
    int find(int x) {  
        int root = elem[x];
        while (root != parent[root]) {
            root = parent[root];
        }
        return elem[x] = root;
    }
    
    bool same(int a, int b) { return find(a) == find(b); }
    int size(int x) { return setSize[find(x)]; }
    long long sum(int x) { return setSum[find(x)]; }
    
    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        // Union by size
        if (setSize[ra] > setSize[rb]) swap(ra, rb); // append a (old root) to b (new root)
        
        parent[ra] = rb;

        setSize[rb] += setSize[ra];
        setSum[rb] += setSum[ra];
        return true;
    }
    
    // move a into set containing b. does nothing if a and b in the same set
    bool move(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        
        // Remove from old set
        --setSize[ra];
        setSum[ra] -= a;
        
        elem[a] = rb;
        
        // Add to new set
        ++setSize[rb];
        setSum[rb] += a;

        return true;
    }
};

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n,m; 
    while (cin >> n >> m) {
        DSUMove dsu(n+1);
        int a,b,c;
        FOR(i,0,m) {
            cin >> a;
            if (a==1) {
                cin >> b >> c;
                dsu.unite(b,c);
            } elif (a==2) {
                cin >> b >> c;
                dsu.move(b,c);
            } else {
                cin >> b;
                cout << dsu.size(b) << ' ' << dsu.sum(b) << '\n';
            }
        }
    }
        
}



