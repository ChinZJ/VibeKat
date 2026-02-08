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

    string s; cin >> s;
    int p1=s.find('+'), p2=s.find('=');
    string w1=s.substr(0,p1), w2=s.substr(p1+1,p2-p1-1), w3=s.substr(p2+1);
    int sw1=sz(w1), sw2=sz(w2), sw3=sz(w3);

    if (sw3 < max(sw1,sw2)) { cout << "impossible\n"; return 0; };

    set<char> charset;
    for (char c : s) if (isalpha(c)) charset.insert(c);
    vector<char> chars(charset.begin(), charset.end());

    if (sz(chars) > 10) { cout << "impossible\n"; return 0; }

    int nonzero=0; setBit(nonzero,w1[0]-'A'); setBit(nonzero,w2[0]-'A'); setBit(nonzero,w3[0]-'A');
    int dig[26]; memset(dig, -1, sizeof(dig));
    int used=0;

    int maxlen=max({sw1,sw2,sw3});
    vector<vi> cols(maxlen, vi(3)); // pos on string
    vector<vi> colChar(maxlen,vi(3)); // store letter index
    FOR(i,0,maxlen) {
        cols[i][0]=(i < sw1) ? (sw1-i-1) : -1;
        cols[i][1]=(i < sw2) ? (sw2-i-1) : -1;
        cols[i][2]=(i < sw3) ? (sw3-i-1) : -1;

        colChar[i][0]=(cols[i][0] == -1) ? -1 : w1[cols[i][0]] - 'A';
        colChar[i][1]=(cols[i][1] == -1) ? -1 : w2[cols[i][1]] - 'A';
        colChar[i][2]=(cols[i][2] == -1) ? -1 : w3[cols[i][2]] - 'A';
    }


    auto colRdy = [&](int c) -> bool {
        FOR(j,0,3) {
            if (cols[c][j] != -1) {
                char ch=(j==0 ? w1 : j==1 ? w2 : w3)[cols[c][j]];
                if (dig[ch-'A']==-1) return false;
            }
        }
        return true;
    };

    auto checkCols = [&]() -> bool {
        int carry=0;
        bool allChk=false;
        FOR(i,0,maxlen) {
            if (!colRdy(i)) break;

            int d1=(cols[i][0]==-1) ? 0 : dig[colChar[i][0]];
            int d2=(cols[i][1]==-1) ? 0 : dig[colChar[i][1]];
            int d3=(cols[i][2]==-1) ? 0 : dig[colChar[i][2]];

            int sum=d1+d2+carry;
            if (sum%10!=d3) return false;
            carry=sum/10;
            if (i==maxlen-1) allChk=true;
        }
        if (allChk) return carry==0;
        return true; 
    };

    auto solve = [&](auto&& self, int idx) -> bool {
        if (idx==sz(chars)) {
            for (char c : s) {
                if (isalpha(c)) cout << dig[c-'A'];
                else cout << c;
            }
            cout << '\n';
            return true;
        }

        char c = chars[idx];

        int st = (isOn(nonzero,c-'A') ? 1 : 0);

        FOR(d,st,10) {
            if (isOn(used,d)) continue;
            dig[c-'A']=d;
            setBit(used,d);

            if (checkCols() && self(self, idx+1)) return true;

            dig[c-'A']=-1;
            clearBit(used,d);
        }
        return false;
    };

    if (sw3 > max(sw1,sw2)) {
        dig[w3[0]-'A']=1;
        setBit(used,1);
        chars.erase(find(chars.begin(), chars.end(), w3[0]));
    }

    if (!solve(solve,0)) cout << "impossible\n";
}
