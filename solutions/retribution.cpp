#include <bits/stdc++.h>
using namespace std;

struct Data{
  int idj, idd;
  double dist;
  
  Data(int j, int d, double di) : idj(j), idd(d), dist(di) {}
  
  bool operator>(const Data& o) const {
      if (dist != o.dist) return dist > o.dist;
      if (idj != o.idj) return idj > o.idj;
      return idd > o.idd;
  }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,m,p, x, y;
    cin >> n >> m >> p;
    double ans=0.0;
    
    vector<int> xs(n+1), ys(n+1), jj(n+1), mj(m+1), sj(p+1);
    
    priority_queue<Data, vector<Data>, greater<Data>> pqm;
    
    for (int i=1;i<=n;i++) {
        cin >> xs[i] >> ys[i];
    }
    
    for (int i=1;i<=m;i++) {
        cin >> x >> y;
        for (int j=1;j<=n;j++) {
            pqm.push({j, 
                i, 
                sqrt(pow((x - xs[j]), 2) + pow((y - ys[j]), 2))
                });
        }
    }
    
    int cnt=0;
    while (cnt<n) {
        Data d = pqm.top();
        pqm.pop();
        if (!jj[d.idj] && !mj[d.idd]) {
            jj[d.idj] = 1;
            mj[d.idd] = 1;
            cnt++;
            ans += d.dist;
        }
    }
    
    while (!pqm.empty()) {
        pqm.pop();
    }
    
    for (int i=1;i<=p;i++) {
        cin >> x >> y;
        for (int j=1;j<=n;j++) {
            pqm.push({j, 
                i, 
                sqrt(pow((x - xs[j]), 2) + pow((y - ys[j]), 2))
                });
        }
    }
    
    cnt=0;
    while (cnt<n) {
        Data d = pqm.top();
        pqm.pop();
        if (jj[d.idj] && !sj[d.idd]) {
            jj[d.idj] = 0;
            sj[d.idd] = 1;
            cnt++;
            ans += d.dist;
        }
    }
    
    cout << fixed << setprecision(6) << ans << '\n';
}