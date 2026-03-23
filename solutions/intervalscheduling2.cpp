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

#define umap unordered_map 

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
     * 
     * 
     */

    int N; cin >> N;

    vector<pii> og(N);
    vector<pii> cop(N);
    int hh,mm; char c;
    FOR(i,0,N) {  
        cin >> hh >> c >> mm;
        int sst = (hh*60) + mm;
        cin >> c >> hh >> c >> mm;
        int een = (hh*60) + mm;
        og[i] = cop[i] = {sst,een};
    }
    int st=og[0].fi, en = og[N-1].se;

    int lo=0, hi=479;
    int curst=0, curen=0, preven=0, nextst=0;
    while (lo < hi) {
        int mid = lo + (hi-lo+1)/2;

        bool ok=true;
        FOR(i,0,N) {
            if (i==0) {
                preven = st;
            } else preven = cop[i-1].se;

            if (i==N-1) {
                nextst = en;
            } else nextst = og[i+1].fi;

            curst = og[i].fi; curen = og[i].se;
            if (curen - preven >= mid) {cop[i] = {preven, curen}; continue;}
            else if (nextst - preven >= mid) {
                int minreq = mid+preven;
                cop[i] = {preven, minreq};
            } else {
                ok = false;
            }

            if (!ok) break;
        }

        if (ok) lo=mid;
        else hi = mid-1;
    }

    FOR(i,0,N) {
        if (i==0) {
            preven = st;
        } else preven = cop[i-1].se;

        if (i==N-1) {
            nextst = en;
        } else nextst = og[i+1].fi;

        curst = og[i].fi; curen = og[i].se;
        if (curen - preven >= lo) {cop[i] = {preven, curen}; continue;}
        else if (nextst - preven >= lo) {
            int minreq = lo+preven;
            cop[i] = {preven, minreq};
        }
    }

    for (auto& [sst, een] : cop) {
        int ssth = sst/60;
        int sstm = sst%60;
        int eenh = een/60;
        int eenm = een%60;

        cout << ssth << ':';
        if (sstm < 10) cout << "0";
        cout << sstm << " - " << eenh << ':';
        if (eenm < 10) cout << "0";
        cout << eenm << '\n';
    }
}