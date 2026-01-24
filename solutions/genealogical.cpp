#include <bits/stdc++.h>
using namespace std;

unordered_map<string, string> birth;
unordered_map<string, string> death;
unordered_map<string, vector<string>> parents; 
unordered_map<string, vector<string>> child;

void printPerson(const string& name, int indent) {
    cout << string(indent, ' ') << name;
    if (birth.find(name) != birth.end() && !birth[name].empty()) {
        cout << " " << birth[name] << " -";
        if (death.find(name) != death.end() && !death[name].empty()) {
            cout << " " << death[name];
        }
    }
    cout << '\n';
}

void printAncestors(const string& name, int indent) {
    if (parents.find(name) == parents.end()) return;
    
    vector<string> pars = parents[name];
    sort(pars.begin(), pars.end());
    
    for (const string& p : pars) {
        printPerson(p, indent);
        printAncestors(p, indent + 2);
    }
}

void printDescendants(const string& name, int indent) {
    if (child.find(name) == child.end()) return;
    
    vector<string> kids = child[name];
    sort(kids.begin(), kids.end());
    
    for (const string& c : kids) {
        printPerson(c, indent);
        printDescendants(c, indent + 2); 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    birth.reserve(1000); 
    death.reserve(1000); 
    parents.reserve(1000); 
    child.reserve(1000);
    
    string line;
    bool first = true;
    
    while (getline(cin, line)) {
        if (line[0] == 'Q') break;
        
        if (line[0] == 'B') {  // BIRTH child : date : mother : father
            vector<string> args(4);
            int st = 6, i=6, arg=0;
            while (arg < 3) {
                if (line[i] == ':') {
                    args[arg] = line.substr(st, i - st - 1);
                    arg++;
                    st = i + 2;
                }
                i++;
            }
            args[3] = line.substr(st);
            
            birth[args[0]] = args[1];
            parents[args[0]].push_back(args[2]);
            parents[args[0]].push_back(args[3]);
            child[args[2]].push_back(args[0]);
            child[args[3]].push_back(args[0]);
        }
        else if (line[0] == 'D' && line[2] == 'A') {  // DEATH person : date
            size_t p1 = line.find(':');
            string person = line.substr(6, p1 - 6 - 1);
            string date = line.substr(p1 + 2);
            death[person] = date;
        }
        else if (line[0] == 'A') {  // ANCESTORS person
            string person = line.substr(10);
            if (!first) cout << '\n';
            first = false;
            cout << "ANCESTORS of " << person << '\n';
            printAncestors(person, 2);
        }
        else if (line[0] == 'D') {  // DESCENDANTS person
            string person = line.substr(12);
            if (!first) cout << '\n';
            first = false;
            cout << "DESCENDANTS of " << person << '\n';
            printDescendants(person, 2);
        }
    }
    
    return 0;
}