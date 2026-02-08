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
    cin.tie(0)->sync_with_stdio(0);

    int N; cin >> N;
    unordered_map<int,vector<string>> dic;
    unordered_map<int, vector<unordered_map<char,int>>> diccnt;
    string s;
    FOR(i,0,N) {
        cin >> s;
        dic[sz(s)].pb(s);
        unordered_map<char,int> tmp;
        for (char c : s) {
            tmp[c]++;
        }
        diccnt[sz(s)].pb(move(tmp));
    }

    // merge sort
    auto countInv=[&](string& from, string& to) -> int {
        int n=from.length();

        vector<queue<int>> pos(256);
        FOR(i,0,n) pos[(unsigned char)to[i]].push(i);

        vi perm(n);
        FOR(i,0,n) {
            perm[i]=pos[(unsigned char)from[i]].front();
            pos[(unsigned char)from[i]].pop();
        }
        
        
        function<int(int,int)> mergeSort=[&](int l, int r) -> int {
            if (l >= r) return 0;
            int m=l+(r-l)/2;
            int inv =0;
            inv += mergeSort(l,m);
            inv += mergeSort(m+1,r);

            vi left(perm.begin()+l, perm.begin()+m+1);
            vi right(perm.begin()+m+1, perm.begin()+r+1);
            int i=0,j=0,k=l;
            while (i <sz(left) && j < sz(right)) {
                if (left[i]<=right[j]) {
                    perm[k++]=left[i++];
                } else {
                    perm[k++]=right[j++];
                    inv+=(sz(left)-i);
                }
            }
            while (i<sz(left)) perm[k++]=left[i++];
            while(j<sz(right)) perm[k++]=right[j++];
            return inv;
        };
        return mergeSort(0,n-1);
    };

    while (cin >> s) {
        int len=sz(s);
        int dig=0; vi digpos; digpos.reserve(len);
        unordered_map<char,int> tmp;
        FOR(i,0,len) {
            if (isdigit(s[i])) {
                dig++; digpos.pb(i);
            } else {
                tmp[s[i]]++;
            }
        }
        if (dig>3) {cout << s << '\n'; continue;}
        
        bool imposs,solve=false;
        FOR(i,0,sz(diccnt[len])) {
            imposs=false;
            unordered_map<char,int> diffs=diccnt[len][i];
            for (auto& [c,cnt]:tmp) {
                if (diffs[c] < cnt) { imposs=true;break;}
                diffs[c]-=cnt;
            }
            if (imposs) continue;

            vector<char> rem;
            for (auto& [c,cnt]:diffs) {
                FOR(j,0,cnt) rem.pb(c);
            }
            if (sz(rem)!=dig) continue;
            sort(ALL(rem));

            do {
                string filled=s;
                FOR(j,0,dig) filled[digpos[j]]=rem[j];

                if (dig+countInv(filled,dic[len][i]) <= 3) {
                    solve=true; break;
                }
            } while (next_permutation(ALL(rem)));
        }

        if (!solve) cout << s << '\n';
    }
}
