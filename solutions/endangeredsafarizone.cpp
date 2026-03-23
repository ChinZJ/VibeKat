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

const int MAXN=100'005;
const int B = 2160; // N^(2/3)

struct Query {
    int l,r,t,id;
    
    bool operator<(const Query& o) const {
        if (int b1_l=l/B, b2_l=o.l/B; b1_l != b2_l) return b1_l < b2_l;
        if (int b1_r=r/B, b2_r=o.r/B; b1_r != b2_r) return b1_r < b2_r;
        return t < o.t;
    }
};

struct Update {
    int p, oldval, newval;
};

int arr[MAXN];
int freq[MAXN];
int validSpecies = 0;
int KLim;

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     * Mo Algorithm (similar to squareroot decomposition)
     * 
     * Assume number of elements N, queries Q and updates U are all 10^5
     *      Let B be the chosen block size
     *      
     *      Because we sort queries first by L block then R block, 
     *          L pointer move at most B steps to reach new query sstart
     *          R pointer move at most B steps to reach new query end
     *          Across N total queries, total movement for L and R is roughly O(N * B)
     * 
     *      Array is divided into blocks of size B, there are thus N/B blocks for L and R pointer
     *      Thus we create a grid of N/B * N/B = N^2 / B^2 block pairs
     * 
     *      Queries that fall into same L,R pair, sorted by time T
     *          ie T pointer simply sweeps forward from 0 to U (or N)
     *          Worst case, T pointer has to sweep across entire timeline of N updates for every single unique block pair
     *          Thus worst case is O(N^2 / B^2 * N) = O(N^3 / B^2)
     * 
     *      Balance between O(N * B) and O(N^3 / B^2)
     * 
     */

    int N,M; cin >> N >> M >> KLim;

    // Use secondary array to track current state of array
    vi ogarr(N);
    FOR(i,0,N) {
        cin >> arr[i];
        ogarr[i] = arr[i];
    }

    vector<Query> queries; queries.reserve(M);
    vector<Update> updates; updates.reserve(M);

    FOR(i,0,M) {
        int type,a,b;
        cin >> type >> a >> b;
        if (type == 1) {
            int idx=a-1;
            int newval=b;
            int oldval = ogarr[idx];
            ogarr[idx]=newval;
            updates.pb({idx, oldval, newval});
        } else {
            queries.pb({a-1, b-1, sz(updates), sz(queries)});
        }
    }
    
    sort(ALL(queries));
    vi ans(sz(queries));

    auto add = [&](int idx) -> void {
        int s = arr[idx];
        freq[s]++;
        if (freq[s] == 1) validSpecies++;
        if (freq[s] == KLim + 1) validSpecies--;
    };

    auto removeIdx = [&](int idx) -> void {
        int s = arr[idx];
        freq[s]--;
        if (freq[s] == 0) validSpecies--;
        if (freq[s] == KLim) validSpecies++;
    };


    auto applyUpdates = [&](int uIdx, int L, int R, vector<Update>& updates) -> void {
        int p = updates[uIdx].p;
        int nVal = updates[uIdx].newval;

        if (L <= p && p <= R) {
            removeIdx(p);
            arr[p] = nVal;
            add(p);
        } else {
            arr[p] = nVal;
        }

        // Swap old and new value (applyUpdate on the same index will undo the operation)
        swap(updates[uIdx].oldval, updates[uIdx].newval);
    };

    int L=0, R=-1, T=0;
    for (const auto& q : queries) {
        // Adjust time
        while (T < q.t) {
            applyUpdates(T, L, R, updates); T++;
        }
        while (T > q.t) {
            T--; applyUpdates(T, L, R, updates);
        }

        // Adjust range [L,R]
            // Expand to avoid negative ranges
        while (L > q.l) {
            L--; add(L);
        }
        while (R < q.r) {
            R++; add(R);
        }
            // Shrink after expanding
        while (L < q.l) {
            removeIdx(L); L++;
        }
        while (R > q.r) {
            removeIdx(R); R--;
        }

        // Record answer
        ans[q.id] = validSpecies;
    }

    for (int res : ans) {
        cout << res << '\n';
    }
}