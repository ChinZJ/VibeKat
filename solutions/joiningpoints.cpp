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
     * TODO
     * 
     * Suppose square with corners (X1,Y1) and (X2,Y2) at diagonal borders
     * 
     * Points on the border must have either X or Y coordinate equal to one of the 4 coordinates
     * 
     * We first simplify the problem by trying to pin down either the X or Y coordinates
     *      Given all our coordinates, we can obtain Xmin, Xmax, Ymin, Ymax
     *      Trivially we can always take the longer one (ie Xmax - Xmin > Ymax - Ymin) we fix X, else Y
     * 
     *      If both are equal, then we have to try both 
     * Now assume we have a scenario by which we fix X coordinates to be the min and max value
     * (The argument for fixing Y coordinates is the exact same)
     *      For points whose X coordinate is strictly between xmin and xmax (the coordinates we will be using)
     *      they must have y coordinate equal to Y1 or Y2
     * 
     *      Suppose we find a Y1 for which some of the points agree to, Y2 is fixed because of the nature of the square
     * 
     *      Case 1: More than 2 distinct y values within the interior:  impossible
     *      Case 2: Exactly 2 values:                                   Try Y1,Y2 = {a,b} 
     *      Case 3: Exactly 1 value:                                    Try Y1 = a, and separately Y2 = a
     *      Case 3: No value:                                           Try existing ymin and ymax
     * 
     *      For each permutation of Y1,Y2 that we try, we simply ensure that
     *          1. lengths are equal
     *          2. every point indeed touches one
     */

    int N; cin >> N;
    int xmin=INT_MAX, xmax=INT_MIN, ymin=INT_MAX, ymax=INT_MIN;
    int x1=0,x2=0,y1=0,y2=0;

    int X[N], Y[N];
    FOR(i,0,N) {
        cin >> X[i] >> Y[i];
        xmin=min(xmin, X[i]); xmax=max(xmax, X[i]);
        ymin=min(ymin, Y[i]); ymax=max(ymax, Y[i]);
    }

    auto tryy = [&]() -> bool {
        // Fix y1 and y2
        y1=ymin; y2=ymax;

        // Collate all interior points
        set<int> interiorX;
        FOR(i,0,N) {
            if (Y[i] > ymin && Y[i] < ymax) interiorX.insert(X[i]);
            if (sz(interiorX) > 2) return false;
        }
        
        // Case 2: exactly 2 values
        int szx = sz(interiorX);
        if (szx == 2) {
            auto it=interiorX.begin();
            int v1 = *(it); ++it; int v2=*(it);
            x1 = min(v1,v2); x2=max(v1,v2);
            if (x1 > xmin || x2 < xmax) return false;
            if ((y2-y1) != (x2-x1)) return false;
            else {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) return false;
                }
                return true;
            }
        } elif (szx == 1) {
            bool pass=true;
            x1 = *(interiorX.begin()); x2 = x1+(y2-y1);
            if (x1 <= xmin && x2 >= xmax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }
                
            pass = true;
            x2 = x1 - (y2-y1); swap(x1,x2);
            if (x1 <= xmin && x2 >= xmax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }
            return false;
        } else {
            bool pass=true;
            x1 = xmin; x2 = x1 + (y2-y1);
            if (x1 <= xmin && x2 >= xmax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }

            pass = true;
            x2 = xmax; x1 = x2 - (y2-y1);
            if (x1 <= xmin && x2 >= xmax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }
            return false;
        }
        return false;
    };

    auto tryx = [&]() -> bool {
        // Fix y1 and y2
        x1=xmin; x2=xmax;

        // Collate all interior points
        set<int> interiorY;
        FOR(i,0,N) {
            if (X[i] > xmin && X[i] < xmax) interiorY.insert(Y[i]);
            if (sz(interiorY) > 2) return false;
        }
        
        // Case 2: exactly 2 values
        int szy = sz(interiorY);
        if (szy == 2) {
            auto it=interiorY.begin();
            int v1 = *(it); ++it; int v2=*(it);
            y1 = min(v1,v2); y2=max(v1,v2);

            if (y1 > ymin || y2 < ymax) return false;
            if ((y2-y1) != (x2-x1)) return false;
            else {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) return false;
                }
                return true;
            }
        } elif (szy == 1) {
            bool pass=true;
            y1 = *(interiorY.begin()); y2 = y1+(x2-x1);
            if (y1 <= ymin && y2 >= ymax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }

            pass = true;
            y2 = y1 - (x2-x1); swap(y1,y2);
            if (y1 <= ymin && y2 >= ymax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }
            return false;
        } else {
            bool pass=true;
            y1 = ymin; y2 = y1 + (x2-x1);
            if (y1 <= ymin && y2 >= ymax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }

            pass = true;
            y2 = ymax; y1 = y2 - (x2-x1);
            if (y1 <= ymin && y2 >= ymax) {
                FOR(i,0,N) {
                    if (x1 != X[i] && x2 != X[i] && y1 != Y[i] && y2 != Y[i]) {pass = false; break;}
                }
                if (pass) return true;
            }
            return false;
        }
    };

    bool ok=false;
    if ((ymax-ymin) > (xmax-xmin)) {
        ok = tryy();
    } elif ((xmax-xmin) > (ymax-ymin)) {
        ok = tryx();
    } else {
        ok = tryy();
        if (!ok) ok = tryx();
    }
    if (ok) {
        cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << '\n';
    } else cout << "Impossible\n";
}