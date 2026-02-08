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

/** 
bitset<1000000010> isprime;
vi primes;
bitset<1000000010> wins;
*/
unordered_set<int> lose = {0,3,8,11,32,35,56,59,64,67,118,121,208,211,216,219,622,625,712,715,720,723,744,747,896,899,986,989,2560,2563,2778,2781,3806,3809,3890,3893,4198,4201,4584,4587,5338,5341,5458,5461,5962,5965,8642,8645,12084,12087,12772,12775,13602,13605,14012,14015,17336,17339,18016,18019,19310,19313,20940,20943,26374,26377,29320,29323,38154,38157,42662,42665,43502,43505,45930,45933,49686,49689,60066,60069,64476,64479,72448,72451,83956,83959,91046,91049,93740,93743,96310,96313,118766,118769,123806,123809,143434,143437,147712,147715,154866,154869,170090,170093,187820,187823,209752,209755,244800,244803,273474,273477,347428,347431,382530,382533,402720,402723,467274,467277,543812,543815,561334,561337,580884,580887,607694,607697,665034,665037,686696,686699,693306,693309,816300,816303,960620,960623,960964,960967,1024258,1024261,1157516,1157519,1340720,1340723,1377504,1377507,1412330,1412333,1454878,1454881,1488314,1488317,1608896,1608899,1907342,1907345,1915204,1915207,1953088,1953091,2011552,2011555,2053088,2053091,2218520,2218523,2439860,2439863,2506800,2506803,2792760,2792763,2818000,2818003,3058974,3058977,3692938,3692941,3810186,3810189,3850764,3850767,4240946,4240949,5380204,5380207,5484644,5484647,5632196,5632199,6136490,6136493,6929080,6929083,7019280,7019283,7163844,7163847,7339412,7339415,8299624,8299627,9702450,9702453,10000910,10000913,11404634,11404637,13368688,13368691,13509604,13509607,13750138,13750141,15095790,15095793,16166924,16166927,16409144,16409147,17105420,17105423,17412348,17412351,17820008,17820011,20007958,20007961,20693774,20693777,22045460,22045463,23380094,23380097,24789334,24789337,25126678,25126681,26647980,26647983,27683252,27683255,27781826,27781829,28640628,28640631,33645474,33645477,36104218,36104221,36190982,36190985,36607498,36607501,36830424,36830427,38880354,38880357,40010700,40010703,42600652,42600655,46883338,46883341,47261042,47261045,50441582,50441585,50806108,50806111,51326550,51326553,63270628,63270631,73376298,73376301,79246954,79246957,85507614,85507617,86494788,86494791,87659372,87659375,93188572,93188575,102490320,102490323,111387292,111387295,117666362,117666365,125481924,125481927,125946452,125946455,129257606,129257609,131533502,131533505,148061544,148061547,154708884,154708887,156257698,156257701,164235208,164235211,174422902,174422905,177543326,177543329,200688798,200688801,203517204,203517207,227993998,227994001,235532762,235532765,239063820,239063823,241476986,241476989,251732672,251732675,279478702,279478705,281430472,281430475,294129388,294129391,300664758,300664761,309796952,309796955,315713182,315713185,343273582,343273585,364007276,364007279,367324042,367324045,373016576,373016579,385477086,385477089,405738568,405738571,442967366,442967369,480451560,480451563,519983304,519983307,536597756,536597759,629403140,629403143,713858034,713858037,739002982,739002985,809065744,809065747,813583138,813583141,822228058,822228061,830259270,830259273,834828324,834828327,916215504,916215507,978364206,978364209};

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    /**
     * Cheat Preprocessing
     * To reach a losing position L, want to remove i - L stones (to get L stones)
     * To remove i-L stones, i-L+1 must be prime according to the rules of the game
     * If none of the losing positions are reachable, then i is a new losing position
     */

    // Sieve https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
    
    /** 
    ll NMAX=(ll)1e9;
    // Primes are 1
    isprime.set(); isprime[0]=isprime[1]=0;
    for (ll i=2; i*i <= NMAX+1; i++) {
        if (isprime[i]) {
            for (ll j=i*i; j<=NMAX+1; j+=i) {
                isprime[j]=0;
            }
        }
    }

    primes.reserve(60000000);
    for (ll i=2;i<=NMAX;i++) {
        if (isprime[i]) primes.pb(i);
    }

    printf("{");
    for (ll i=0; i<= NMAX; i++) {
        if (!wins[i]) {
            printf("%lld,", i);
            for (int& p : primes) {
                if (i + p - 1 > NMAX) break;
                wins[i+p-1] = 1;
            }
        }
    }
    printf("}");
    */


    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        if (lose.find(n) != lose.end()) cout << "Bob\n";
        else cout << "Alice\n";
    }
}
