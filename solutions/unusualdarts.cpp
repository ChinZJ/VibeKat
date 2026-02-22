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

struct Point {
    double x,y;
};

double polyArea(const vector<Point>& pts) {
    double area=0.0;
    int n = sz(pts);
    for (int i=0; i<n; ++i) {
        int j = (i+1)%n;
        area += pts[i].x * pts[j].y;
        area -= pts[j].x * pts[i].y;
    }
    return abs(area)/2;
}

double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y)
        - (b.y - a.y) * (c.x - a.x);
}

bool onSegment(const Point& a, const Point& b, const Point& c) {
    return std::min(a.x, b.x) <= c.x && c.x <= std::max(a.x, b.x)
        && std::min(a.y, b.y) <= c.y && c.y <= std::max(a.y, b.y);
}

bool segIntersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    double d1 = cross(p3, p4, p1);
    double d2 = cross(p3, p4, p2);
    double d3 = cross(p1, p2, p3);
    double d4 = cross(p1, p2, p4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) 
            && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return true;
    }

    if (d1 == 0.0 && onSegment(p3,p4,p1)) return true;
    if (d2 == 0.0 && onSegment(p3,p4,p2)) return true;
    if (d3==0.0 && onSegment(p1,p2,p3)) return true;
    if (d4==0.0 && onSegment(p1,p2,p4)) return true;

    return false;
}

double EPS=1e-5;

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int N; cin >> N;
    while (N--) {
        double x,y;
        vector<int> perm(7);
        vector<Point> coords(7);
        for (int i=0; i<7; ++i) {
            perm[i]=i+1;
            cin >> x >> y;
            coords[i] = {x,y};
        }

        double p; cin >> p;
        auto buildPoly=[&]() ->vector<Point> {
            vector<Point> poly(7);
            for (int i=0; i<7; ++i) {
                poly[i] = coords[perm[i] - 1];
            }
            return poly;
        };

        do {
            vector<Point> poly=buildPoly();
            // Verify that polygon is simple
                // Every pair of non adjacent edges should not intersect
            bool ok=true;
            for (int i = 0; i < 7; ++i) {
                for (int j = i + 2; j < 7; ++j) {
                    if (i == 0 && j == 7-1) continue;
                    if (segIntersect(poly[i], poly[(i+1)%7],
                            poly[j], poly[(j+1)%7])) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) continue;

            // Shoelace method for calculating area of polygon
            double A = polyArea(poly);
            if (abs(((A/4) * (A/4) * (A/4)) - p) <= EPS) {
                for (int i=0; i<7; ++i) {
                    cout << perm[i] << ' ';
                }
                cout << '\n';
                break;
            }

        } while (next_permutation(perm.begin(), perm.end()));
    }
}