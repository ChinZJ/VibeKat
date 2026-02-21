#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define fi first
#define se second

#define FOR(i, a, b) for (int i = int(a); i < int(b); i++)
#define REP(i, a, b) for (int i = int(a); i <= int(b); i++)
#define REF(i, a, b) for (int i = int(a); i >= int(b); i--)

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


// cout << fixed << setprecision(8) << ... for decimal precision

#include <bits/extc++.h>                         // pbds
using namespace __gnu_pbds;

typedef tree<pair<ll,int>, // key type (storing)
    null_type, // mapped type (set) -> no duplicates
    less<pair<ll,int>>, // less comparator (ascending)        // the alternative is greater<int>
    rb_tree_tag, // red black tree implementation
    tree_order_statistics_node_update> ordered_set; // order statistics operations


signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n,q; cin >> n >> q;
    unordered_map<string, int> name; int uid=0;
    unordered_map<int, ll> idsc;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        idsc[uid] = 0; name[s] = uid++; 

    }

    char cmd;  
    int no; ll sc;

    ordered_set scores;
    for (int i = 0; i < uid; ++i) {
        scores.insert({0,i});
    }

    for (int i = 0; i < q; ++i) {
        cin >> cmd;
        if (cmd == '!') {
            cin >> no;
            for (int j = 0; j < no; ++j) {
                cin >> s >> sc;
                uid = name[s];
                auto it = scores.find({idsc[uid], uid});
                auto [oSc, uid] = *it;
                scores.erase(it);
                idsc[uid] += sc;
                scores.insert({oSc + sc, uid});
            }
        } else {
            cin >> s;
            uid = name[s];
            cout << scores.order_of_key({idsc[uid], 0}) + 1 << ' ' << idsc[uid] << '\n';
        }
    }
}