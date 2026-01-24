#include <bits/stdc++.h>
using namespace std;

struct Song {
    long long quality;  // f * original_position
    int id;
    string nm;
    
    bool operator>(const Song& o) const {
        if (quality != o.quality) return quality > o.quality;
        return id < o.id;  // lower id wins ties
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<Song> songs(n);
    for (int i = 0; i < n; i++) {
        long long f;
        string nm;
        cin >> f >> nm;
        songs[i] = {f * (i + 1), i, nm};
    }
    
    sort(songs.begin(), songs.end(), greater<Song>());
    
    for (int i = 0; i < m; i++) {
        cout << songs[i].nm << '\n';
    }
    return 0;
}