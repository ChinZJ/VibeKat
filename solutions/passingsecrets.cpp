#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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

ll binpow(ll a, ll b, ll mod=1) {
    ll res = 1;
    a%=mod;
    while (b > 0) {
        if (b & 1) {
            res = (res * a)%mod;
        }
        a = (a * a) % mod;
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


ll binomial(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k==0 || k==n) return 1;

    if (k > n-k) k=n-k;

    ll res=1;
    for (int i=0;i<k;i++) {
        res=res*(n-i)/(i+1);
    }
    return res;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    string a,b,s;
    int n;
    while (cin >> a >> b) {
        
        unordered_map<string,int> map;
        unordered_map<int, string> revmap;
        int uid=0;
        map[a]=uid; revmap[uid++]=a;
        map[b]=uid; revmap[uid++]=b;
        
        cin >> n;
        cin.ignore();
        vector<unordered_map<int,int>> adj(5002);
        FOR(i,0,n) {
            getline(cin,s);
            stringstream ss(s);
            vi group; group.reserve(5002);
            while (ss >> a) {
                if (map.find(a)==map.end()) {
                    map[a]=uid; revmap[uid++]=a;
                }
                group.pb(map[a]);
            }

            int nn=sz(group);
            FOR(i,0,nn) {
                FOR(j,i+1,nn) {
                    if (adj[group[i]].find(group[j])==adj[group[i]].end()) {
                        adj[group[i]][group[j]]=nn-2;
                    }
                    else adj[group[i]][group[j]]=min(adj[group[i]][group[j]], nn-2);
                    if (adj[group[j]].find(group[i])==adj[group[j]].end()) {
                        adj[group[j]][group[i]]=nn-2;
                    }
                    else adj[group[j]][group[i]]=min(adj[group[j]][group[i]], nn-2);
                }
            }
        }

        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0,0}); // risk, id
        vi par(uid, -1); par[0]=0;
        vi dist(uid,INF); dist[0]=0;
        bool ok=false;
        while (!pq.empty()) {
            auto [xx,yy]=pq.top(); pq.pop();
            if (xx>dist[yy]) continue;

            if (yy==1) {
                cout << xx-1;
                ok=true;
                break;
            }

            for (auto [key,val] : adj[yy]) {
                if (val+xx+1 < dist[key]) {
                    // cout << "going from " << yy << ' ' << key << " with val " << val+xx << '\n';
                    dist[key]=val+xx+1;
                    pq.push({val+xx+1, key});
                    par[key]=yy;
                }
            }
        }

        if (ok) {
            vi ans; ans.reserve(uid);
            for (int i=1; i!=par[i]; i=par[i]) {
                ans.pb(i);
            }
            cout << ' ' << revmap[0];
            REF(i,sz(ans)-1,0) {
                cout << ' ' << revmap[ans[i]];
            }
            cout << '\n';
        } else {
            cout << "impossible\n";
        }
    }
}