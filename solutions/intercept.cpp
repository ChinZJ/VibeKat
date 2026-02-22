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

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int N,M; cin >> N >> M;
    int u,v; ll w;
    vector<vector<pair<int,ll>>> adj(N);
    vector<vector<pair<int,ll>>> radj(N);
    for (int i=0; i<M; ++i) {
        cin >> u >> v >> w;
        adj[u].pb({v,w});
        radj[v].pb({u,w});
    }
    int s,t; cin >> s >> t;
    vll dists(N, LLONG_MAX), cnts1(N, 0), cnts2(N, 0), distt(N, LLONG_MAX), cntt1(N, 0), cntt2(N, 0);

    priority_queue<pair<ll,int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0,s});
    dists[s] = 0; cnts1[s] = 1; cnts2[s] = 1; 
    distt[t] = 0; cntt1[t] = 1; cntt2[t] = 1;
    while (!pq.empty()) {
        auto [cost, stn] = pq.top(); pq.pop();
        if (cost > dists[stn]) continue;

        for (auto [v, add] : adj[stn]) {
            ll newcost = cost + add;
            if (newcost < dists[v]) {
                dists[v] = newcost;
                cnts1[v] = cnts1[stn];
                cnts2[v] = cnts2[stn];
                pq.push({newcost, v});
            } elif (newcost == dists[v]) {
                cnts1[v] = (cnts1[v]+cnts1[stn])%MOD1;
                cnts2[v] = (cnts2[v]+cnts2[stn])%MOD2;
            }
        }
    }

    pq.push({0,t});
    while (!pq.empty()) {
        auto [cost, stn] = pq.top(); pq.pop();
        if (cost > distt[stn]) continue;

        for (auto [v, add] : radj[stn]) {
            ll newcost = cost + add;
            if (newcost < distt[v]) {
                distt[v] = newcost;
                cntt1[v] = cntt1[stn];
                cntt2[v] = cntt2[stn];
                pq.push({newcost, v});
            } elif (newcost == distt[v]) {
                cntt1[v] = (cntt1[v]+cntt1[stn])%MOD1;
                cntt2[v] = (cntt2[v]+cntt2[stn])%MOD2;
            }
        }
    }

    for (int i=0; i<N; ++i) {
        if (i == s 
                || i == t 
                || (dists[i] + distt[i] == dists[t] 
                        && (cnts1[i] * cntt1[i])%MOD1 == cnts1[t]
                        && (cnts2[i] * cntt2[i])%MOD2 == cnts2[t])
            ) {
            cout << i << ' ';
        }
    }
    cout << '\n';
}