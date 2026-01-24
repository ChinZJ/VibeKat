#include <bits/stdc++.h>
using namespace std;

struct Win {
    long long x, y, w, h;
    int id; // original insertion order
};

long long xmax, ymax;
vector<Win> windows;

// Check if two rectangles overlap (exclusive boundaries)
bool rectsOverlap(long long x1, long long y1, long long w1, long long h1,
                  long long x2, long long y2, long long w2, long long h2) {
    // No overlap if one is completely left/right/above/below the other
    if (x1 + w1 <= x2 || x2 + w2 <= x1) return false;
    if (y1 + h1 <= y2 || y2 + h2 <= y1) return false;
    return true;
}

// Check if window fits on screen
bool fitsOnScreen(long long x, long long y, long long w, long long h) {
    return x >= 0 && y >= 0 && x + w <= xmax && y + h <= ymax;
}

// Check if a window would overlap any existing window (excluding one by index)
bool hasOverlap(long long x, long long y, long long w, long long h, int excludeIdx = -1) {
    for (int i = 0; i < (int)windows.size(); i++) {
        if (i == excludeIdx) continue;
        if (rectsOverlap(x, y, w, h, windows[i].x, windows[i].y, windows[i].w, windows[i].h)) {
            return true;
        }
    }
    return false;
}

// Find index of window containing pixel (x, y)
// Window covers [x, x+w) and [y, y+h)
int findWindow(long long px, long long py) {
    for (int i = 0; i < (int)windows.size(); i++) {
        Win& win = windows[i];
        if (px >= win.x && px < win.x + win.w &&
            py >= win.y && py < win.y + win.h) {
            return i;
        }
    }
    return -1;
}

// Check if two windows overlap vertically (their y-ranges intersect)
bool overlapVertically(const Win& a, const Win& b) {
    return !(a.y + a.h <= b.y || b.y + b.h <= a.y);
}

// Check if two windows overlap horizontally (their x-ranges intersect)
bool overlapHorizontally(const Win& a, const Win& b) {
    return !(a.x + a.w <= b.x || b.x + b.w <= a.x);
}

// Move window at idx by (dx, dy) with cascading
// Returns actual distance moved (absolute value)
long long moveWindow(int idx, long long dx, long long dy) {
    Win& start = windows[idx];
    
    if (dx > 0) {
        // Moving right
        // Find all windows that overlap vertically with start
        vector<pair<long long, int>> band; // (x position, index)
        for (int i = 0; i < (int)windows.size(); i++) {
            if (overlapVertically(windows[i], start)) {
                band.push_back({windows[i].x, i});
            }
        }
        sort(band.begin(), band.end());
        
        // Find position of start window in sorted band
        int startPos = -1;
        for (int i = 0; i < (int)band.size(); i++) {
            if (band[i].second == idx) {
                startPos = i;
                break;
            }
        }
        
        // Build chain and calculate cumulative gaps
        // chain[i] = (window index, cumulative gap before this window)
        vector<pair<int, long long>> chain;
        chain.push_back({idx, 0});
        long long chainRight = start.x + start.w;
        long long cumGap = 0;
        
        for (int i = startPos + 1; i < (int)band.size(); i++) {
            int nextIdx = band[i].second;
            Win& next = windows[nextIdx];
            
            // Only consider if it overlaps vertically (should already be true)
            if (!overlapVertically(next, start)) continue;
            
            long long gap = next.x - chainRight;
            
            // If the requested movement doesn't reach this window, stop
            if (cumGap + gap >= dx) break;
            
            cumGap += gap;
            chain.push_back({nextIdx, cumGap});
            chainRight = next.x + next.w;
        }
        
        // Calculate maximum possible movement
        // The rightmost window in chain limits movement
        // Final right edge of last window: chainRight + (actualMove - cumGap)
        // Must satisfy: chainRight + (actualMove - cumGap) <= xmax
        // So: actualMove <= xmax - chainRight + cumGap
        long long maxMove = xmax - chainRight + cumGap;
        long long actualMove = min(dx, maxMove);
        
        // Apply movement to each window in chain
        for (auto& [winIdx, gapBefore] : chain) {
            windows[winIdx].x += (actualMove - gapBefore);
        }
        
        return actualMove;
    }
    else if (dx < 0) {
        // Moving left
        long long requested = -dx;
        
        vector<pair<long long, int>> band;
        for (int i = 0; i < (int)windows.size(); i++) {
            if (overlapVertically(windows[i], start)) {
                band.push_back({windows[i].x, i});
            }
        }
        // Sort descending (rightmost first, so we process leftward)
        sort(band.begin(), band.end(), greater<pair<long long, int>>());
        
        int startPos = -1;
        for (int i = 0; i < (int)band.size(); i++) {
            if (band[i].second == idx) {
                startPos = i;
                break;
            }
        }
        
        vector<pair<int, long long>> chain;
        chain.push_back({idx, 0});
        long long chainLeft = start.x;
        long long cumGap = 0;
        
        for (int i = startPos + 1; i < (int)band.size(); i++) {
            int nextIdx = band[i].second;
            Win& next = windows[nextIdx];
            
            if (!overlapVertically(next, start)) continue;
            
            long long gap = chainLeft - (next.x + next.w);
            
            if (cumGap + gap >= requested) break;
            
            cumGap += gap;
            chain.push_back({nextIdx, cumGap});
            chainLeft = next.x;
        }
        
        // chainLeft - (actualMove - cumGap) >= 0
        // actualMove <= chainLeft + cumGap
        long long maxMove = chainLeft + cumGap;
        long long actualMove = min(requested, maxMove);
        
        for (auto& [winIdx, gapBefore] : chain) {
            windows[winIdx].x -= (actualMove - gapBefore);
        }
        
        return actualMove;
    }
    else if (dy > 0) {
        // Moving down
        vector<pair<long long, int>> band;
        for (int i = 0; i < (int)windows.size(); i++) {
            if (overlapHorizontally(windows[i], start)) {
                band.push_back({windows[i].y, i});
            }
        }
        sort(band.begin(), band.end());
        
        int startPos = -1;
        for (int i = 0; i < (int)band.size(); i++) {
            if (band[i].second == idx) {
                startPos = i;
                break;
            }
        }
        
        vector<pair<int, long long>> chain;
        chain.push_back({idx, 0});
        long long chainBottom = start.y + start.h;
        long long cumGap = 0;
        
        for (int i = startPos + 1; i < (int)band.size(); i++) {
            int nextIdx = band[i].second;
            Win& next = windows[nextIdx];
            
            if (!overlapHorizontally(next, start)) continue;
            
            long long gap = next.y - chainBottom;
            
            if (cumGap + gap >= dy) break;
            
            cumGap += gap;
            chain.push_back({nextIdx, cumGap});
            chainBottom = next.y + next.h;
        }
        
        long long maxMove = ymax - chainBottom + cumGap;
        long long actualMove = min(dy, maxMove);
        
        for (auto& [winIdx, gapBefore] : chain) {
            windows[winIdx].y += (actualMove - gapBefore);
        }
        
        return actualMove;
    }
    else if (dy < 0) {
        // Moving up
        long long requested = -dy;
        
        vector<pair<long long, int>> band;
        for (int i = 0; i < (int)windows.size(); i++) {
            if (overlapHorizontally(windows[i], start)) {
                band.push_back({windows[i].y, i});
            }
        }
        sort(band.begin(), band.end(), greater<pair<long long, int>>());
        
        int startPos = -1;
        for (int i = 0; i < (int)band.size(); i++) {
            if (band[i].second == idx) {
                startPos = i;
                break;
            }
        }
        
        vector<pair<int, long long>> chain;
        chain.push_back({idx, 0});
        long long chainTop = start.y;
        long long cumGap = 0;
        
        for (int i = startPos + 1; i < (int)band.size(); i++) {
            int nextIdx = band[i].second;
            Win& next = windows[nextIdx];
            
            if (!overlapHorizontally(next, start)) continue;
            
            long long gap = chainTop - (next.y + next.h);
            
            if (cumGap + gap >= requested) break;
            
            cumGap += gap;
            chain.push_back({nextIdx, cumGap});
            chainTop = next.y;
        }
        
        long long maxMove = chainTop + cumGap;
        long long actualMove = min(requested, maxMove);
        
        for (auto& [winIdx, gapBefore] : chain) {
            windows[winIdx].y -= (actualMove - gapBefore);
        }
        
        return actualMove;
    }
    
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> xmax >> ymax;
    
    string cmd;
    int cmdNo = 1;
    int nextId = 1;
    
    while (cin >> cmd) {
        if (cmd == "OPEN") {
            long long x, y, w, h;
            cin >> x >> y >> w >> h;
            
            if (!fitsOnScreen(x, y, w, h) || hasOverlap(x, y, w, h)) {
                cout << "Command " << cmdNo << ": OPEN - window does not fit\n";
            } else {
                windows.push_back({x, y, w, h, nextId++});
            }
        }
        else if (cmd == "CLOSE") {
            long long x, y;
            cin >> x >> y;
            
            int idx = findWindow(x, y);
            if (idx == -1) {
                cout << "Command " << cmdNo << ": CLOSE - no window at given position\n";
            } else {
                windows.erase(windows.begin() + idx);
            }
        }
        else if (cmd == "RESIZE") {
            long long x, y, w, h;
            cin >> x >> y >> w >> h;
            
            int idx = findWindow(x, y);
            if (idx == -1) {
                cout << "Command " << cmdNo << ": RESIZE - no window at given position\n";
            } else {
                Win& win = windows[idx];
                // Check if new size fits (at same position)
                if (!fitsOnScreen(win.x, win.y, w, h) || hasOverlap(win.x, win.y, w, h, idx)) {
                    cout << "Command " << cmdNo << ": RESIZE - window does not fit\n";
                } else {
                    win.w = w;
                    win.h = h;
                }
            }
        }
        else if (cmd == "MOVE") {
            long long x, y, dx, dy;
            cin >> x >> y >> dx >> dy;
            
            int idx = findWindow(x, y);
            if (idx == -1) {
                cout << "Command " << cmdNo << ": MOVE - no window at given position\n";
            } else {
                long long requested = abs(dx) + abs(dy); // at most one is non-zero
                long long actual = moveWindow(idx, dx, dy);
                
                if (actual < requested) {
                    cout << "Command " << cmdNo << ": MOVE - moved " << actual << " instead of " << requested << "\n";
                }
            }
        }
        cmdNo++;
    }
    
    // Output final state
    // Sort by original insertion order (id)
    vector<Win> sorted = windows;
    sort(sorted.begin(), sorted.end(), [](const Win& a, const Win& b) {
        return a.id < b.id;
    });
    
    cout << sorted.size() << "\n";
    for (const Win& w : sorted) {
        cout << w.x << " " << w.y << " " << w.w << " " << w.h << "\n";
    }
    
    return 0;
}
