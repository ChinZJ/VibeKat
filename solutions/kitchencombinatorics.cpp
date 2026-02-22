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

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int r,s,m,d,n; cin >> r >> s >> m >> d >> n;

    vector<int> brands(r);
    for (int i=0; i<r; ++i) cin >> brands[i];

    vector<vector<int>> starters(s);
    int k, tmp, tmp2;
    for (int i=0; i<s; ++i) {
        cin >> k;
        for (int j=0; j<k; ++j) {
            cin >> tmp; --tmp;
            starters[i].pb(tmp);
        }
    }

    vector<vector<int>> mains(m);
    for (int i=0; i<m; ++i) {
        cin >> k;
        for (int j=0; j<k; ++j) {
            cin >> tmp; --tmp;
            mains[i].pb(tmp);
        }
    }

    vector<vector<int>> dess(d);
    for (int i=0; i<d; ++i) {
        cin >> k;
        for (int j=0; j<k; ++j) {
            cin >> tmp; --tmp;
            dess[i].pb(tmp);
        }
    }

    int tot=s+m+d;
    vector<unordered_set<int>> adj(tot);
    for (int i=0; i<n; ++i) {
        cin >> tmp >> tmp2;
        --tmp; --tmp2;
        adj[tmp].insert(tmp2);
        adj[tmp2].insert(tmp);
    }

    ll ans=0; ll THRESH=1e18;
    for (int st=0; st<s; ++st) {
        for (int ma=0; ma<m; ++ma) {
            for (int de=0; de<d; ++de) {
                if ((adj[st].find(s+ma) != adj[st].end())
                        || (adj[st].find(s+m+de) != adj[st].end())
                        || (adj[s+ma].find(s+m+de) != adj[s+ma].end())
                    ) continue;

                bitset<1000> mask;
                for (auto ing : starters[st]) mask.set(ing);
                for (auto ing : mains[ma]) mask.set(ing);
                for (auto ing : dess[de]) mask.set(ing);

                ll curr=1;
                for (int ing=mask._Find_first(); ing < 1000; ing=mask._Find_next(ing)) {
                    if (curr > (THRESH/brands[ing])) {
                        cout << "too many\n";
                        return 0;
                    }
                    curr *= brands[ing];
                    // cout << "ingredients " << ing << '\n';
                }
                if (curr > THRESH-ans) {
                    cout << "too many\n";
                    return 0;
                }
                ans += curr;
            }
        }
    }
    cout << ans << '\n';
}