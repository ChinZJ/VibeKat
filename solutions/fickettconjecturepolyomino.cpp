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
     * Brute force, given that hint by question is R^3 + C^3 < 10^7
     * 
     * For a convex polyomino, each row occupies cells in a single interval [lo,hi] (only need one interval per row)
     *      By convexity, the interior cells also forms a contiguous interval [ilo, ihi]
     * 
     * Try all 4 rotations and permtuate the overlapping regions
     *      Shapes are convex, overlap in each row is the intersection of two intervals
     *      Compute the numerator and denominator in O(R) by walking row by row if prefix sums of border cells along each row have been computed
     */

    int T; cin >> T; while (T--) {
        int R,C; cin >> R >> C;
        vector<string> grid(R);
        FOR(i,0,R) cin >> grid[i];

        struct Poly {
            int nrows;
            vi lo, hi;   // occupied column interval per row
            vi ilo, ihi; // interior sub interval per row
        };

        /**
         * Compute interior intervals from row intervals
         * Cell (r,c) interior IFF all 8 neighbors are inside the poly
         * 
         *      c-1 and c+1 must be in row r 
         *          - thus c >= lo[r]+1 and c <= hi[r]-1 (left and right cells)
         *      c-1, c, c+1 must all be in row r-1 (top cells)
         *          - thus c >= lo[r-1]+1 and c <= hi[r-1]+1
         *      c-1, c, c+1 must all be in row r+1 (bot cells)  
         *          - thus c >= lo[r+1]+1 and c <=hi[r+1]+1
         *      Take the tightest constraint from everything provided
         * 
         * First and last rows have no interior cells
         */
        auto computeInterior = [&](Poly& p) {
            p.ilo.resize(p.nrows); p.ihi.resize(p.nrows);
            FOR(r,0,p.nrows) {
                if (r==0 || r == p.nrows - 1) {
                    p.ilo[r] = 1; 
                    p.ihi[r] = 0;
                } else {
                    p.ilo[r] = max({p.lo[r]+1, p.lo[r-1] + 1, p.lo[r+1] + 1});
                    p.ihi[r] = min({p.hi[r]-1, p.hi[r-1]-1, p.hi[r+1]-1});
                }
            }
        };

        auto buildpoly = [&](vector<string>& grid, int R, int C) -> Poly {
            Poly p;
            int first=-1, last = -1;
            // Find starting and ending of the rows of the polyomino
            FOR(r,0,R) {
                if (grid[r].find('#') != string::npos)  {
                    if (first == -1) first = r;
                    last = r;
                }
            }
            p.nrows = last - first + 1;
            p.lo.resize(p.nrows); p.hi.resize(p.nrows);

            // Find [l,r] for each row
            int colmin = C;
            REP(r, first, last) {
                int l=C, h=-1;
                FOR(c,0,C) {
                    if (grid[r][c] == '#') {
                        l = min(l,c);
                        h = max(h,c);
                    }
                }
                p.lo[r - first] = l;
                p.hi[r - first] = h;
                colmin = min(colmin, l);
            }

            // Note that when we perform rotate 90, column values becomes row indices
            // Want to prevent unecessary checks on empty rows thus we shift everything to 0 indexed
            FOR(r,0,p.nrows) {
                p.lo[r] -= colmin;
                p.hi[r] -= colmin;
            }

            computeInterior(p);
            return p;
        };

        auto A = buildpoly(grid, R, C);

        /**
         * 90 Clockwise rotation maps (r,c) -> (c, nrows-1-r)
         * Convexity is preserved across rotations
         * 
         * Try every integer translation (dx,dy)
         *      dy shifts B vertically. 
         *          Overlapping rows [max(0, dy), min(ra, dy + rb)]
         *      dx shifts B horizontally. 
         *          Compute range of dx values that produce at least some column overlap in at least one row
         *      
         *      For each (dx,dy), walk overlapping rows
         *          In each row, overlap columns are [max(A.lo[r], B.lo[br]+dx), min(A.hi[r], B.hi[br]+dx)]
         *          Count A border cells and B border cells in that overlap using countBorder
         */
        auto rotate90 = [&](Poly& p) -> Poly {
            int cmax=0;
            FOR(r,0,p.nrows) {
                cmax = max(cmax, p.hi[r]);
            }

            Poly q;
            q.nrows = cmax + 1;
            q.lo.assign(q.nrows, p.nrows);
            q.hi.assign(q.nrows, -1);

            FOR(r,0,p.nrows) {
                REP(c,p.lo[r], p.hi[r]) {
                    int nr=c;
                    int nc=p.nrows - 1 - r;
                    q.lo[nr] = min(q.lo[nr], nc);
                    q.hi[nr] = max(q.hi[nr], nc);
                }
            }
            computeInterior(q);
            return q;
        };

        auto countBorder = [&](Poly& p, int r, int ql, int qr) -> int {
            int cl=max(ql, p.lo[r]); // Clamp query to actual occupied cells
            int cr=min(qr, p.hi[r]);
            if (cl > cr) return 0;   // Query does not hit row at all

            int tot=cr-cl+1;        // Total occupied cells in query range
                                    // Includes both border and interior cells
                                    // Need to subtract interior

            int il = max(cl, p.ilo[r]);
            int ir = min(cr, p.ihi[r]);
            int interior = max(0, ir - il + 1);

            return tot - interior;
        };


        ll bestnum=0, bestden=1;

        auto B = A;
        FOR(rot,0,4) {
            // Try all possilbe placements of B on top of A, then rotate 90 for the next iteration
            
            /**
             * Fix A, shift B
             *      A will thus have rows at position [0,ra)
             *      B will shift by dy and have rows at [dy, dy + rb)
             */
            int ra = A.nrows;
            int rb = B.nrows;

            // iterate all vertical offsets with at least one row of overlap
            FOR(dy, -(rb-1), ra) {
                // Overlapping rows of A and B are [rlo, rhi)
                int rlo = max(0, dy);       // Cannot go above A first row
                int rhi = min(ra, dy + rb); // Cannot go below A last row
                if (rlo >= rhi) continue;

                /**
                 * Range of horizontal offsets to produce overlap
                 * 
                 * For each overlapping row r
                 *      A occupies columns [A.lo[r], A.hi[r]]
                 *      B occupies [B.lo[br]+dx, B.hi[br]+dx]
                 *          br here is the offset caused from dy
                 * 
                 * A.lo[r] <= B.hi[br] + dx
                 * A.hi[r] >= B.lo[br] + dx
                 */
                int dxmin = INT_MAX, dxmax = INT_MIN;
                FOR(r, rlo, rhi) {
                    int br = r-dy;
                    dxmin = min(dxmin, A.lo[r] - B.hi[br]); // Smallest dx where overlap starts
                    dxmax = max(dxmax, A.hi[r] - B.lo[br]); // Largest dx where overlap exists
                }

                REP(dx, dxmin, dxmax) {
                    ll num=0, den=0;

                    FOR(r, rlo, rhi) {
                        int br = r-dy;
                        int ol = max(A.lo[r], B.lo[br]+dx); // Ovelrap left column
                        int oh = min(A.hi[r], B.hi[br]+dx); // Overlap right column
                        if (ol > oh) continue;              // No overlap in this row

                        num += countBorder(A,r,ol,oh);      // A border cell covered by B
                        den += countBorder(B,br,ol-dx, oh-dx); // B border cell covered by A
                                                               // Note B self frame is actually not shifted, thus subtract dx
                    }

                    if (den > 0 && num * bestden > bestnum * den) {
                        bestnum = num; bestden = den;
                    }
                }
            }

            B = rotate90(B);
        }

        ll g = gcd(bestnum, bestden);
        cout << bestnum/g << '/' << bestden/g << '\n';
    }

}