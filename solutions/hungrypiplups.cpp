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

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     * Observe value of A_i is relatively small (500), counting sort is feasible
     * Sort and run a simple O(500) siulation per query which is definitely manageable
     * 
     * Problem stems from counting sort on the interval
     */

    int n,m; cin >> n >> m;
    int MAX_VAL = 501;
    
    // Squareroot decomposition instead of segment tree
        // Scan partial blocks in O(B) and full blocks in O((N/B)*500)
    int B = max(1, (int)sqrt((double)n * MAX_VAL));

    vi a(n+1);
    int numblocks = (n+B-1) / B; // ceiling

    // Hpw many times value v appears in block b
    vector<vi> blockfreq(numblocks, vi(MAX_VAL, 0));

    // Which block does 1 indexed position in block b
    auto blk=[&](int i) {return (i-1) / B;};
    // First 1 indexed position in block b
    auto blkst = [&](int b) {return b*B + 1;};
    // Last 1 indexed position in block b
    auto blkend = [&](int b) {return min((b+1)*B, n);};

    REP(i,1,n) {
        cin >> a[i];
        blockfreq[blk(i)][a[i]]++;
    }

    while (m--) {
        int type; cin >> type;

        // Performing updates
        if (type==0) {
            int p,x; cin >> p >> x;
            blockfreq[blk(p)][a[p]]--;
            a[p] = x;
            blockfreq[blk(p)][a[p]]++;
        } else {
            int l,r,x; cin >> l >> r >> x;

            // Build freq[v] (count of value in A[l..r])
            vi freq(MAX_VAL);

            /**
             * Case 0: Subset of a block: scan element by element
             * Case 1: Left partial block: scan element by element
             * Case 2: Full middle block: add precomputad blockfreq arrays
             * Case 3: Right partial block: scan element by element
             */
            int lb=blk(l), rb=blk(r);
            
            if (lb == rb) {
                // Same block, scan directly
                REP(i,l,r) {
                    freq[a[i]]++;
                } 
            } else {
                // Left partial
                REP(i,l,blkend(lb)) {
                    freq[a[i]]++;
                }

                // Middle
                FOR(b,lb+1,rb) {
                    FOR(v,0,MAX_VAL) {
                        freq[v] += blockfreq[b][v];
                    }
                }

                // Right partial
                REP(i,blkst(rb), r) {
                    freq[a[i]]++;
                }
            }


            /**
             * Use freq to simulate the migration operation using the frequency table
             * Process v = 1,2,..,500 in order
             *      freq[v] piplus all target iceberg v
             *      Land staritng at max(v, nextfree) and occupy freq[v] consecutive icebergs
             *      
             *      Track the resulting occupied segments as (start,end)  pairs
             *      At most 500 segments
             * 
             * segments[i] = {start, end} of the ith occupied interval
             */
            int segst[MAX_VAL], segend[MAX_VAL];
            int segcnt=0, nextfree=1;

            FOR(v,1,MAX_VAL) {
                if (freq[v] == 0) continue;

                int s = max(v, nextfree); // first iceberge reached
                int e = s + freq[v] - 1; // last iceberg they fill

                // Merge with previous if overlap
                    // Overlaps are handled via nextfree
                if (segcnt > 0 && segend[segcnt - 1] >= s-1) {
                    segend[segcnt - 1] = e;
                } else {
                    segst[segcnt] = s;
                    segend[segcnt] = e;
                    segcnt++;
                }
                nextfree = e+1;
            }

            /**
             * Find the xth empty iceberge (1 indexed)
             * Walk through all segments, gaps contain empty icebergs
             */
            int ans=-1, cnt=0,pos=1;
            for (int i=0; i < segcnt && cnt < x; ++i) {
                // Gap before segment
                int gapsz = segst[i] - pos;

                if (cnt + gapsz >= x) {
                    ans = pos + (x - cnt - 1);
                    cnt = x;
                } else {
                    cnt += gapsz;
                    pos = segend[i] + 1;
                }
            }
            if (cnt < x) {
                ans = pos + (x - cnt - 1);
            }
            cout << ans << '\n';
        }
    }

}