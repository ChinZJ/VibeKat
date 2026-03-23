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

using i128 = __int128;
ll LIMIT = 1'000'000'000'000'000'000LL;
vll valid;

bool isSorted(i128 val) {
    int prev = 9;
    while (val > 0) {
        int d = (int)(val %10);
        if (d > prev) return false;
        prev = d;
        val /= 10;
    }
    return true;
}

void generate(ll curr, int lastdig) {
    if (curr > LIMIT) return;

    if (curr > 0) {
        i128 sq = (i128)(curr) * curr;
        if (isSorted(sq)) {
            valid.pb(curr);
        }
    }

    for (int d = max(lastdig, 0); d <= 9; ++d) {
        ll next = curr*10 + d;
        if (next > LIMIT) break;
        generate(next,d);
    }
}

const int BITS = 32;
ll memo[BITS+1][2][2][3][3][3][3];

signed main() {
    cin.tie(0) -> sync_with_stdio(0);

    /**
     * TODO
     * 
     * Digit DP, process bits from LSB to MSB
     * 
     * Observe that the question is asking for (A+B) | (A-B) = (A+B)
     *      ie A-B bits is a subset of A+B and does not contribute anything
     * 
     * Build A and B one bit at a time, from bit 0 (LSB) to 31 (MSB)
     * 
     * States:
     *      bit:    bit position
     *      carry:  carry into this bit from A+B
     *      borrow: borrow into this bit from A-B
     *      cmpAL:  comparison of A vs L
     *      cmpAR:  comparison of A vs R
     *      cmpBL:  comparison of B vs L
     *      cmpBA:  comparison of B vs A
     * 
     * At each bit :try all 4 choices of (a_bit, b_bit)
     *      Compute sum_bit and diff_bit (using carry / borrow)
     *      Reject if diff_bit = 1 and sum_bit = 0
     *      Update carry, borrow and 4 comparisons
     *          0 = less
     *          1 = equal
     *          2 = greater
     * 
     *      Accept at bit == 32 only if
     *          borrow = 0
     *          L <= A <= R
     *          L <= B <= A
     */

    memset(memo, -1, sizeof(memo));

    ll L,R; cin >> L >> R;

    auto dp = [&](auto& self, int bit, int carry, int borrow,
            int cmpAL, int cmpAR, int cmpBL, int cmpBA) -> ll {

        if (bit == BITS) {
            bool valid = (borrow == 0)                  // A-B >= 0
                    && (cmpAL >= 1) && (cmpAR <= 1)     // L <= A <= R
                    && (cmpBL >= 1) && (cmpBA <= 1);    // L <= B <= A
            return valid ? 1 : 0;
        }

        auto& ans = memo[bit][carry][borrow][cmpAL][cmpAR][cmpBL][cmpBA];
        if (ans != -1) return ans;

        int LBit = (L >> bit) & 1;
        int RBit = (R >> bit) & 1;
        ans = 0;

        REP(a,0,1) {
            REP(b,0,1) {
                // A + B
                int sm = a + b + carry;
                int sumBit = sm & 1;
                int newCarry = sm >> 1;

                // A - B
                int diff = a - b - borrow;
                int diffBit = (diff >= 0) ? diff : diff + 2;
                int newBrw = (diff >= 0) ? 0 : 1;

                // Submask check - if (A-B) has a 1 but (A+B) has 0 subset rule is violated
                if (diffBit == 1 && sumBit == 0) continue;

                // Update comparisons (higher bit overrides lower bits)
                auto cmp = [](int oldCmp, int myBit, int refBit) {
                    if (myBit > refBit) return 2;
                    if (myBit < refBit) return 0;
                    return oldCmp; // tie so rely on older bits
                };

                ans += self(self, bit+1, newCarry, newBrw, 
                        cmp(cmpAL, a, LBit),
                        cmp(cmpAR, a, RBit),
                        cmp(cmpBL, b, LBit),
                        cmp(cmpBA, b, a));
            }
        }
        return ans;
    };

    std::cout << dp(dp, 0, 0, 0, 1, 1, 1, 1) << "\n";
}