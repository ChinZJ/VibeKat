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

long double EPS=1e-18;

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int P; cin >> P;
    while (P--) {
        int K; ll M; string x;
        cin >> K >> M >> x;
        __int128 xn=0, xd=1;
        if (auto dot=x.find('.'); dot != string::npos) {
            for (size_t i = dot+1; i<x.size(); ++i) {
                xn=xn*10 + (x[i]-'0');
                xd *= 10;
            }
        }

        auto cmpx=[&](ll a, ll b) -> int {
            __int128 lhs = (__int128)a * xd;
            __int128 rhs = (__int128)xn * b;
            return (lhs < rhs) ? -1 : (lhs > rhs) ? 1 : 0;
        };

        auto closer=[&](ll a, ll b, ll c, ll d) -> int {
            __int128 diff1 = (__int128)xn*b - (__int128)a*xd;
            if (diff1<0) diff1=-diff1;

            __int128 diff2 = (__int128)xn*d - (__int128)c*xd;
            if (diff2<0) diff2=-diff2;

            __int128 lhs=diff1*d;
            __int128 rhs=diff2*b;
            return (lhs < rhs) ? -1 : (lhs > rhs) ? 1 : 0;
        };

        // Stern Brocot with Binary Search Intervals
        ll lon=0, lod=1, hin=1, hid=1, bestn=0, bestd=1;
        bool exact=false;
        while (true) {
            ll medd=lod+hid;
            if (medd>M) break;
            
            ll medn=lon+hin;
            int c = cmpx(medn, medd);

            if (c==0) {
                bestn=medn; bestd=medd; exact=true; break;

            } elif (c<0) {
                ll maxk = (M - lod) / hid;
                ll bk=1, lok=1, hik=maxk;
                while (lok <= hik) {
                    ll midk=lok + (hik - lok) / 2;
                    int cc = cmpx(lon + midk * hin, lod + midk * hid);
                    if (cc<0) {
                        bk = midk; lok=midk+1;
                    } elif (cc==0) {
                        bestn = lon + midk * hin;
                        bestd = lod + midk * hid;
                        exact = true; break;
                    } else {
                        hik = midk - 1;
                    }
                }

                if (exact) break;
                lon += bk * hin;
                lod += bk * hid;
            } else {
                ll maxk= (M-hid) / lod;
                ll bk=1, lok=1, hik=maxk;
                while (lok <= hik) {
                    ll midk= lok + (hik - lok) / 2;
                    int cc = cmpx(hin + midk * lon, hid + midk*lod);
                    if (cc > 0) {
                        bk = midk;
                        lok = midk+1;
                    } elif (cc == 0) {
                        bestn = hin + midk*lon;
                        bestd = hid + midk*lod;
                        exact = true; break;
                    } else {
                        hik = midk - 1;
                    }
                }
                if (exact) break;
                hin += bk*lon;
                hid += bk*lod;

            }
        }

        if (!exact) {
            bool look = lod <= M;
            bool hiok = hid <= M;
            if (look && hiok) {
                int c = closer(lon, lod, hin, hid);
                if (c<=0) {
                    bestn = lon; bestd = lod;
                } else {
                    bestn = hin; bestd = hid;
                }
            } elif (look) {
                bestn = lon; bestd = lod;
            } else {
                bestn = hin; bestd = hid;
            }
        }
        ll g = gcd(bestn, bestd);
        bestn /= g;
        bestd /= g;
        cout << K << ' ' << bestn << '/' << bestd << '\n';
    }
}