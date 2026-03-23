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

/*
  TEMPLATE PARAMETERS:
    S       - Monoid element type (what you query)
    Op      - Binary operation:  S op(S, S)       — must be associative (takes 2 elements of type S and merges them into a single element (the parent))
    E       - Identity element:  S e()            — op(x, e()) == op(e(), x) == x

  CONSTRUCTION:
    SegTree<S, Op, E> seg(n);            // n elements, all initialized to e()
    SegTree<S, Op, E> seg(vector<S> v);  // from vector

  OPERATIONS (0-indexed, half-open [l, r)):
    seg.set(p, x)        — a[p] = x                             O(log n)
    seg.get(p)           — returns a[p]                          O(1)
    seg.query(l, r)      — op(a[l], ..., a[r-1])                O(log n)
    seg.query_all()      — op(a[0], ..., a[n-1])                O(1)
    seg.max_right(l, f)  — max r s.t. f(op(a[l..r-1])) = true  O(log n)
    seg.min_left(r, f)   — min l s.t. f(op(a[l..r-1])) = true  O(log n)

  REQUIREMENTS:
    - f(e()) must be true for max_right / min_left
    - f must be monotonic (once false, stays false)
================================================================================
*/

template <class S, auto Op, auto E>
concept Monoid = requires(S a, S b) {
    { Op(a, b) } -> std::convertible_to<S>; // Op: (S,S) -> S
    { E() } -> std::convertible_to<S>;      // E: () -> S
};

template <class S, auto Op, auto E>
requires Monoid<S, Op, E>
struct SegTree{ 
public:
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(std::vector<S>(n, E())) {}
    explicit SegTree(const std::vector<S>& v) : n_(static_cast<int>(v.size())) {
        sz_ = std::bit_ceil(static_cast<unsigned>(n_));
        log_ = std::countr_zero(static_cast<unsigned>(sz_));

        d_.assign(2 * sz_, E());
        for (int i=0; i<n_; ++i) {
            d_[sz_ + i] = v[i];
        }
        for (int i = sz_ - 1; i>=1; --i) {
            pull(i);
        }
    }

    // Point updates a[p] = x
    void set(int p, S x) {
        assert(0 <= p && p < n_);
        p += sz_;
        d_[p] = x;
        for (int i=1; i<=log_; ++i) { pull(p >> i); }
    }

    // Point query a[p]
    [[nodiscard]] S get(int p) const {
        assert(0 <= p && p < n_);
        return d_[p + sz_];
    }

    // Range query op(a[l], ..., a[r-1]), 0 <= l <= r <= n
    [[nodiscard]] S query(int l, int r) const {
        assert(0 <= 1 && l <= r && r <=n_);
        S res_l = E(), res_r = E();
        for (l += sz_, r += sz_; l < r; l >>= 1, r >>= 1) {
            if (l&1) { res_l = Op(res_l, d_[l++]); }
            if (r&1) { res_r = Op(d_[--r], res_r); }
        }
        return Op(res_l, res_r);
    }

    // Full range query
    [[nodiscard]] S query_all() const { return d_[1]; }

    // Returns max r in [l, n] such that f(op(a[l..r-1])) == true
    // Requires f(e()) == true, where f is monotonic
    template <class F>
    [[nodiscard]] int max_right(int l, F f) const {
        assert(0 <= l && l <= n_); assert(f(E()));
        if (l == n_) { return n_; }
        l += sz_;
        S sm = E();
        do { // BSTA
            while (l%2 == 0) { l >>= 1; }
            if (!f(Op(sm, d_[l]))) {
                while (l < sz_) {
                    l = 2*l;
                    if (f(Op(sm, d_[l]))) {
                        sm = Op(sm, d_[l]); ++l;
                    }
                }
                return l - sz_;
            }
            sm = Op(sm, d_[l]); ++l;
        } while ((l & -l) != l);
        return n_;
    }

    // Returns min l in [0,r] such that f(op(a[l..r-1])) == true
    // Requires f(e()) == true, where f is monotonic
    template <class F>
    [[nodiscard]] int min_left(int r, F f) const {
        assert(0 <= r && r <= n_); assert(f(E()));
        if (r == 0) { return 0; }
        r += sz_;
        S sm = E();
        do { // BSTA
            --r;
            while (r > 1 && (r&1)) { r >>= 1; }
            if (!f(Op(d_[r], sm))) {
                while (r < sz_) {
                    r = 2 * r + 1;
                    if (f(Op(d_[r], sm))) {
                        sm = Op(d_[r], sm);
                        --r;
                    }
                }
                return r + 1 - sz_;
            }
            sm = Op(d_[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int n_{}, sz_{}, log_{};
    std::vector<S> d_;

    void pull (int k) { d_[k] = Op(d_[2*k], d_[2*k + 1]); }
};

/**
 * ================================================================================
 * PRESET MONOIDS
 * ================================================================================
 */

namespace RMin {
    using S = long long;
    constexpr S op(S a, S b) { return std::min(a,b); }
    constexpr S e() { return std::numeric_limits<S>::max(); }
}

namespace RMax {
    using S = long long;
    constexpr S op(S a, S b) { return std::max(a,b); }
    constexpr S e() { return std::numeric_limits<S>::min(); }
}

namespace RSum {
    using S = long long;
    constexpr S op(S a, S b) { return a + b; }
    constexpr S e() { return 0; }
}

namespace RGcd {
    using S = long long;
    constexpr S op(S a, S b) { return std::gcd(a, b); }
    constexpr S e() { return 0; }
}

namespace RXor {
    using S = long long;
    constexpr S op(S a, S b) { return a ^ b; }
    constexpr S e() { return 0; }
}

namespace RMinIdx {
    using S = std::pair<long long, int>;
    constexpr S op(S a, S b) { return std::min(a, b); }
    inline S e() { return {std::numeric_limits<long long>::max(), -1}; }
}

namespace RMaxCnt {
    struct S { long long val; int cnt; };
    constexpr S op(S a, S b) {
        if (a.val > b.val) { return a; }
        if (b.val > a.val) { return b; }
        return {a.val, a.cnt + b.cnt};
    }
    constexpr S e() { return {std::numeric_limits<long long>::min(), 0}; }
}

const ll MOD1 = 998244353;
const ll MOD2 = 1000000007;
const ll EPS=1e-8;

namespace RDens {
    struct S{
        long long totlen;   // total length of the segment
        long long sumsq;    // total density of segment
        char prefchar;      // the character touching left boundary
        long long preflen;  // how many of that character are at the left boundary
        char suffchar;      // character touching right boundary 
        long long sufflen;  // how many of that character are at the right boundary
    };

    // Merge logic
    constexpr S op(S a, S b) {
        // if either child is identity, return the other
        if (a.totlen == 0) return b;
        if (b.totlen == 0) return a;

        // Base addition: parent assumes boundary characters do not match
        // Densities are simply added up
        S res{};
        res.totlen = a.totlen + b.totlen;
        res.sumsq = a.sumsq + b.sumsq;

        // Check for boundaries

        // Merge boundary if characters touch and match
        if (a.suffchar == b.prefchar) {
            // subtract old separated squares
            res.sumsq -= (a.sufflen * a.sufflen) + (b.preflen * b.preflen);
            long long comblen = a.sufflen + b.preflen;
            res.sumsq += (comblen * comblen);
        }

        // Prefix handling
            // When left child is made entirely of one character and matcches right child
        res.prefchar = a.prefchar;
        if (a.preflen == a.totlen && a.prefchar == b.prefchar) {
            res.preflen = a.totlen + b.preflen;
        } else {
            res.preflen = a.preflen;
        }

        // Suffix handling
            // vice versa
        res.suffchar = b.suffchar;
        if (b.sufflen == b.totlen && b.suffchar == a.suffchar) {
            res.sufflen = b.totlen + a.sufflen;
        } else {
            res.sufflen = b.sufflen;
        }

        return res;
    }

    constexpr S e() {
        // Identity element represents empty string segment
        return {0,0,'#',0,'#',0};
    }
}

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     * Custom counting monoid
     */

    int N,Q; cin >> N >> Q;
    string s; cin >> s;

    vector<RDens::S> initleaves(N);
    FOR(i,0,N) {
        initleaves[i] = {1,1,s[i],1,s[i],1};
    }

    SegTree<RDens::S, RDens::op, RDens::e> seg(initleaves);

    FOR(i,0,Q) {
        int type; cin >> type;
        if (type == 1) {
            int pos; char c; cin >> pos >> c;
            pos--;

            seg.set(pos, {1,1,c,1,c,1});
        } elif (type == 2) {
            int l,r; cin >> l >> r;
            --l; // Convert to 0 indexed

            RDens::S res = seg.query(l,r);
            cout << res.sumsq << '\n';
        }
    }
}