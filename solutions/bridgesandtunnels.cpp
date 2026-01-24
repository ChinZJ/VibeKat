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

struct DSUExtended {
    vi p, rank_;
    vi setSize;
    int numSets;
    vector<long long> setSum;  // example: track sum of elements
    
    DSUExtended(int n) : p(n), rank_(n, 0), setSize(n, 1), numSets(n), setSum(n) {
        iota(p.begin(), p.end(), 0);       // p[i] = i
        iota(setSum.begin(), setSum.end(), 0LL);  // setSum[i] = i initially
                                                  // if compressed, can use their real values here, no repercussions
    }
    
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    
    bool same(int a, int b) { return find(a) == find(b); }
    int size(int x) { return setSize[find(x)]; }
    int count() { return numSets; }
    long long sum(int x) { return setSum[find(x)]; }
    
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (rank_[a] > rank_[b]) swap(a, b);  // unite by rank. Let a be the shorter set added to b
        p[a] = b;
        if (rank_[a] == rank_[b]) ++rank_[b]; // rank only increases by 1 if rank a equals rank b (same height)
        setSize[b] += setSize[a]; // only need to maintain root ie. b
        setSum[b] += setSum[a];   // only need to maintain root ie. b
        --numSets;
        return true;
    }
};


signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n; cin >> n;

    unordered_map<string,int> hm;
    int st=0;
    string s1,s2;
    int a,b;
    DSUExtended dsu(n*2);
    FOR(i,0,n) {
        cin >> s1 >> s2;
        if (hm.count(s1)==0) {
            hm[s1]=st;
            st++;
        }
        if (hm.count(s2)==0) {
            hm[s2]=st;
            st++;
        }
        a=hm[s1]; b=hm[s2];
        dsu.unite(a,b);
        cout << dsu.size(a) << '\n';
    }
}