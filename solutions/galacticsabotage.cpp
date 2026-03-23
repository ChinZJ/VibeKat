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

/*

  TEMPLATE PARAMETERS:
    S            - Data type (what you query)
    Op           - Combine data:      S op(S, S)           — associative
                   op(S a, S b) where a is the left child and b is the right child
    E            - Data identity:     S e()                — op(x, e()) == x
                   "blank slate" value that does not change the result of op
    F            - Lazy tag type (the update operation) "pending updates"
    Mapping      - Apply tag to data: S mapping(F, S)
                   Tells the tree how to apply the lazy instruction f to the actual data x
    Composition  - Combine tags:      F composition(F, F)  — f ∘ g (f after g)
                   "Merge operation" combining a lazy update g with a new update f
                   (which one comes first in the operation?)
                   f(g(x)) implies apply g first then f (eg. f + g, where g is +3 and f is +5)
    Id           - Tag identity:      F id()               — mapping(id(), x) == x
                   mapping(id(), x) must equal x
                   composition(f, id()) must equal f

  CONSTRUCTION:
    LazySegTree<S, Op, E, F, Mapping, Composition, Id> seg(n);
    LazySegTree<S, Op, E, F, Mapping, Composition, Id> seg(vector<S> v);

  OPERATIONS (0-indexed, half-open [l, r)):
    seg.set(p, x)          — a[p] = x                              O(log n)
    seg.get(p)             — returns a[p]                           O(log n)
    seg.query(l, r)        — op(a[l], ..., a[r-1])                 O(log n)
    seg.query_all()        — op(a[0], ..., a[n-1])                 O(1)
    seg.apply(p, f)        — a[p] = mapping(f, a[p])               O(log n)
    seg.apply(l, r, f)     — apply f to entire range [l, r)        O(log n)
    seg.max_right(l, g)    — binary search from left                O(log n)
    seg.min_left(r, g)     — binary search from right               O(log n)

  REQUIREMENTS:
    - composition(f, id()) == composition(id(), f) == f
    - mapping(id(), x) == x
    - mapping(composition(f, g), x) == mapping(f, mapping(g, x))
    - mapping(f, op(a, b)) == op(mapping(f, a), mapping(f, b))
      (only needed if using range apply)
================================================================================
*/

template <class S, auto Op, auto E,
          class F, auto Mapping, auto Composition, auto Id>
    requires requires(S a, S b, F f, F g) {
        { Op(a, b) } -> std::convertible_to<S>;
        { E() } -> std::convertible_to<S>;
        { Mapping(f, a) } -> std::convertible_to<S>;
        { Composition(f, g) } -> std::convertible_to<F>;
        { Id() } -> std::convertible_to<F>;
    }
struct LazySegTree {
public:
    LazySegTree() : LazySegTree(0) {}

    explicit LazySegTree(int n) : LazySegTree(std::vector<S>(n, E())) {}

    explicit LazySegTree(const std::vector<S>& v) : n_(static_cast<int>(v.size())) {
        sz_ = std::bit_ceil(static_cast<unsigned>(n_));
        log_ = std::countr_zero(static_cast<unsigned>(sz_));

        d_.assign(2 * sz_, E());
        lz_.assign(sz_, Id());
        for (int i = 0; i < n_; ++i) {
            d_[sz_ + i] = v[i];
        }
        for (int i = sz_ - 1; i >= 1; --i) {
            pull(i);
        }
    }

    // Point update: a[p] = x  (pushes lazily first)
    void set(int p, S x) {
        assert(0 <= p && p < n_);
        p += sz_;
        for (int i = log_; i >= 1; --i) { push(p >> i); }
        d_[p] = x;
        for (int i = 1; i <= log_; ++i) { pull(p >> i); }
    }

    // Point query: returns a[p]  (pushes lazily first)
    [[nodiscard]] S get(int p) {
        assert(0 <= p && p < n_);
        p += sz_;
        for (int i = log_; i >= 1; --i) { push(p >> i); }
        return d_[p];
    }

    // Range query: op(a[l], ..., a[r-1])
    [[nodiscard]] S query(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) { return E(); }

        l += sz_;
        r += sz_;
        for (int i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) { push(l >> i); }
            if (((r >> i) << i) != r) { push((r - 1) >> i); }
        }

        S res_l = E(), res_r = E();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { res_l = Op(res_l, d_[l++]); }
            if (r & 1) { res_r = Op(d_[--r], res_r); }
        }
        return Op(res_l, res_r);
    }

    // Full-range query
    [[nodiscard]] S query_all() const { return d_[1]; }

    // Point apply: a[p] = mapping(f, a[p])
    void apply(int p, F f) {
        assert(0 <= p && p < n_);
        p += sz_;
        for (int i = log_; i >= 1; --i) { push(p >> i); }
        d_[p] = Mapping(f, d_[p]);
        for (int i = 1; i <= log_; ++i) { pull(p >> i); }
    }

    // Range apply: apply f to [l, r)
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) { return; }

        l += sz_;
        r += sz_;
        for (int i = log_; i >= 1; --i) {
            if (((l >> i) << i) != l) { push(l >> i); }
            if (((r >> i) << i) != r) { push((r - 1) >> i); }
        }

        {
            int l2 = l, r2 = r;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1) { apply_at(l++, f); }
                if (r & 1) { apply_at(--r, f); }
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log_; ++i) {
            if (((l >> i) << i) != l) { pull(l >> i); }
            if (((r >> i) << i) != r) { pull((r - 1) >> i); }
        }
    }

    //   Returns max r in [l, n] such that g(op(a[l..r-1])) == true.
    template <class G>
    [[nodiscard]] int max_right(int l, G g) {
        assert(0 <= l && l <= n_);
        assert(g(E()));
        if (l == n_) { return n_; }
        l += sz_;
        for (int i = log_; i >= 1; --i) { push(l >> i); }
        S sm = E();
        do { // BSTA from left
            while (l % 2 == 0) { l >>= 1; }
            if (!g(Op(sm, d_[l]))) {
                while (l < sz_) {
                    push(l);
                    l = 2 * l;
                    if (g(Op(sm, d_[l]))) {
                        sm = Op(sm, d_[l]);
                        ++l;
                    }
                }
                return l - sz_;
            }
            sm = Op(sm, d_[l]);
            ++l;
        } while ((l & -l) != l);
        return n_;
    }

    //   Returns min l in [0, r] such that g(op(a[l..r-1])) == true.
    template <class G>
    [[nodiscard]] int min_left(int r, G g) {
        assert(0 <= r && r <= n_);
        assert(g(E()));
        if (r == 0) { return 0; }
        r += sz_;
        for (int i = log_; i >= 1; --i) { push((r - 1) >> i); }
        S sm = E();
        do { // BSTA from right
            --r;
            while (r > 1 && (r % 2)) { r >>= 1; }
            if (!g(Op(d_[r], sm))) {
                while (r < sz_) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(Op(d_[r], sm))) {
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
    std::vector<F> lz_;

    void pull(int k) { d_[k] = Op(d_[2 * k], d_[2 * k + 1]); }

    void apply_at(int k, F f) {
        d_[k] = Mapping(f, d_[k]);
        if (k < sz_) { lz_[k] = Composition(f, lz_[k]); }
    }

    void push(int k) {
        apply_at(2 * k,     lz_[k]);
        apply_at(2 * k + 1, lz_[k]);
        lz_[k] = Id();
    }
};

// ============================================================================
//                       COMMON LAZY SEGTREE PRESETS
// ============================================================================
// Usage example:
//   auto v = AddSum::build({1,2,3,4,5});
//   LazySegTree<AddSum::S, AddSum::op, AddSum::e,
//               AddSum::F, AddSum::mapping, AddSum::composition, AddSum::id>
//       seg(v);

// --- Pattern 1: Range Add + Range Sum ---------------------------------------
namespace AddSum {
    struct S { long long sum; int len; };
    using F = long long;

    constexpr S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
    constexpr S e() { return {0, 0}; }
    constexpr S mapping(F f, S x) { return {x.sum + f * x.len, x.len}; }
    constexpr F composition(F f, F g) { return f + g; }
    constexpr F id() { return 0; }

    inline std::vector<S> build(const std::vector<long long>& a) {
        std::vector<S> v(a.size());
        for (int i = 0; i < static_cast<int>(a.size()); ++i) { v[i] = {a[i], 1}; }
        return v;
    }
}

// --- Pattern 2: Range Set + Range Sum ---------------------------------------
namespace SetSum {
    struct S { long long sum; int len; };
    using F = long long;
    static constexpr long long UNSET = std::numeric_limits<long long>::min();

    constexpr S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
    constexpr S e() { return {0, 0}; }
    constexpr S mapping(F f, S x) { return (f == UNSET) ? x : S{f * x.len, x.len}; }
    constexpr F composition(F f, F g) { return (f == UNSET) ? g : f; }
    constexpr F id() { return UNSET; }

    inline std::vector<S> build(const std::vector<long long>& a) {
        std::vector<S> v(a.size());
        for (int i = 0; i < static_cast<int>(a.size()); ++i) { v[i] = {a[i], 1}; }
        return v;
    }
}

// Range change minimum (changes minimum only when set)
namespace ChminMin {
    using S = long long;
    using F = long long;
    static constexpr long long INF  = std::numeric_limits<long long>::max();
    static constexpr long long UNSET = INF;  // sentinel = identity element

    constexpr S op(S a, S b) { return std::min(a, b); }
    constexpr S e() { return INF; }
    
    // CHANGE 1: Take the minimum of the new update (f) and the old value (x)
    constexpr S mapping(F f, S x) { return std::min(f, x); }
    
    // CHANGE 2: Combine lazy tags by keeping the smallest one
    constexpr F composition(F f, F g) { return std::min(f, g); }
    
    constexpr F id() { return UNSET; }
}

// --- Pattern 3: Range Add + Range Min ---------------------------------------
namespace AddMin {
    using S = long long;
    using F = long long;
    static constexpr long long INF = std::numeric_limits<long long>::max();

    constexpr S op(S a, S b) { return std::min(a, b); }
    constexpr S e() { return INF; }
    constexpr S mapping(F f, S x) { return (x == INF) ? INF : x + f; }
    constexpr F composition(F f, F g) { return f + g; }
    constexpr F id() { return 0; }
}

// --- Pattern 4: Range Add + Range Max ---------------------------------------
namespace AddMax {
    using S = long long;
    using F = long long;
    static constexpr long long NEG_INF = std::numeric_limits<long long>::min();

    constexpr S op(S a, S b) { return std::max(a, b); }
    constexpr S e() { return NEG_INF; }
    constexpr S mapping(F f, S x) { return (x == NEG_INF) ? NEG_INF : x + f; }
    constexpr F composition(F f, F g) { return f + g; }
    constexpr F id() { return 0; }
}

// --- Pattern 5: Range Set + Range Min ---------------------------------------
namespace SetMin {
    using S = long long;
    using F = long long;
    static constexpr long long INF  = std::numeric_limits<long long>::max();
    static constexpr long long UNSET = INF;  // sentinel = identity element

    constexpr S op(S a, S b) { return std::min(a, b); }
    constexpr S e() { return INF; }
    constexpr S mapping(F f, S x) { return (f == UNSET) ? x : f; }
    constexpr F composition(F f, F g) { return (f == UNSET) ? g : f; }
    constexpr F id() { return UNSET; }
}

// --- Pattern 6: Range Affine (ax + b) + Range Sum (MOD) ---------------------
namespace AffineSum {
    static constexpr long long MOD = 998244353;

    struct S { long long sum; int len; };
    struct F { long long a, b; };  // x → a*x + b

    constexpr S op(S x, S y) { return {(x.sum + y.sum) % MOD, x.len + y.len}; }
    constexpr S e() { return {0, 0}; }
    constexpr S mapping(F f, S x) {
        return {(f.a * x.sum % MOD + f.b * x.len % MOD) % MOD, x.len};
    }
    // f(g(x)) = f.a*(g.a*x + g.b) + f.b = (f.a*g.a)*x + (f.a*g.b + f.b)
    constexpr F composition(F f, F g) {
        return {f.a * g.a % MOD, (f.a * g.b % MOD + f.b) % MOD};
    }
    constexpr F id() { return {1, 0}; }

    inline std::vector<S> build(const std::vector<long long>& a) {
        std::vector<S> v(a.size());
        for (int i = 0; i < static_cast<int>(a.size()); ++i) { v[i] = {a[i] % MOD, 1}; }
        return v;
    }
}

const ll MOD1 = 998244353;
const ll MOD2 = 1000000007;
const ll EPS=1e-8;

namespace RAddZero {
    struct S { long long minval; long long count; };
    using F = long long;

    // Merging
    constexpr S op(S a, S b) { 
        if (a.minval < b.minval) return a;
        if (b.minval < a.minval) return b;
        return {a.minval, a.count + b.count}; // equal mins, sum their count
    }

    // Identity (should not affect operations)
    constexpr S e() { return {INT_MAX, 0}; }

    // Applies lazy addition
    constexpr S mapping(F f, S x) { return {x.minval + f, x.count}; }

    // Combine 2 pending lazy
    constexpr F composition(F f, F g) { return f + g; }

    // Do nothing
    constexpr F id() { return 0; }

    inline std::vector<S> build(const std::vector<long long>& a) {
        std::vector<S> v(a.size());
        for (int i = 0; i < static_cast<int>(a.size()); ++i) { v[i] = {a[i], 1}; }
        return v;
    }
}


signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     * Custom Lazy Seg
     */

    int N,M; cin >> N >> M;
    vi arr(N+1); 

    vll init(N+1, 0LL);
    auto build = RAddZero::build(init);
    LazySegTree<RAddZero::S, RAddZero::op, RAddZero::e,
           RAddZero::F, RAddZero::mapping, RAddZero::composition, RAddZero::id> seg(build);
    
    REP(i,1,N) {
        cin >> arr[i];
        if (arr[i] > i) seg.apply(i, arr[i], 1);
    }

    auto res = seg.query(1, N+1);
    cout << (res.minval == 0 ? res.count : 0) << '\n';

    FOR(i,0,M) {
        int u,v; cin >> u >> v; if (u > v) swap(u,v);
        int oldval = arr[u], newval = arr[v];
        swap(arr[u], arr[v]);

        int en = min(oldval, v);
        if (u < en) {
            seg.apply(u, en, -1);
        }

        en = min(newval, v);
        if (u < en) {
            seg.apply(u, en, 1);
        }

        auto res = seg.query(1, N+1);
        cout << (res.minval == 0 ? res.count : 0) << '\n';
    }
}