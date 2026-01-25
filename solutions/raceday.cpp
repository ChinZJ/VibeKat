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

    int n;

    string s1,s2,s3,fulls; int tmp;
    while (cin >> n) {
        if (n==0) break;

        map<string,int> name;
        unordered_map<int,string> revname;
        unordered_map<int,string> bib;
        vector<pair<string,int>> sp1, sp2, fin;
        unordered_map<int,pair<string,int>> rk1,rk2,rkfin;
        revname.reserve(n), bib.reserve(n);
        sp1.reserve(n), sp2.reserve(n), fin.reserve(n);
        rk1.reserve(n),rk2.reserve(n),fin.reserve(n);
        

        FOR(i,0,n) {
            cin >> s1 >> s2 >> s3;
            tmp=stoi(s3);
            fulls= s2 + ", " + s1;
            name[fulls]=tmp; revname[tmp]=fulls; bib[tmp]=s3;
        }

        FOR(i,0,3*n) {
            cin >> s3 >> s1 >> s2;
            tmp=stoi(s3);
            if (s1=="S1") {
                sp1.pb({move(s2),tmp});
            } elif (s1=="S2") {
                sp2.pb({move(s2),tmp});
            } else {
                fin.pb({move(s2),tmp});
            }
        }

        sort(ALL(sp1)); sort(ALL(sp2)); sort(ALL(fin));

        auto rnk = [&](vector<pair<string,int>>& arr, unordered_map<int,pair<string,int>>& putin) {
            int currRank=1;
            int consec=0;
            int idx=0;
            int arrsz=sz(arr);
            while (idx < arrsz) {
                consec=0;
                while(idx+1 < arrsz && arr[idx+1].fi == arr[idx].fi) {
                    consec++;
                    idx++;
                }
                for (int j=idx;j>=idx-consec;j--) {
                    putin[arr[j].se]={move(arr[j].fi),currRank};
                }
                currRank+=consec+1;
                idx++;
            }
        };

        rnk(sp1,rk1); rnk(sp2,rk2); rnk(fin,rkfin);

        cout << left << setw(20) << "Name"
            << right << setw(10) << "Bib"
            << right << setw(10) << "Split1"
            << right << setw(10) << "Rank"
            << right << setw(10) << "Split2"
            << right << setw(10) << "Rank"
            << right << setw(10) << "Finish"
            << right << setw(10) << "Rank" << "\n";

        for (auto& [fname,bibint] : name) {
            cout << left << setw(20) << fname
                << right << setw(10) << bib[bibint]
                << right << setw(10) << rk1[bibint].fi
                << right << setw(10) << rk1[bibint].se
                << right << setw(10) << rk2[bibint].fi
                << right << setw(10) << rk2[bibint].se
                << right << setw(10) << rkfin[bibint].fi
                << right << setw(10) << rkfin[bibint].se << "\n";
        }
        cout << '\n';
    }
}