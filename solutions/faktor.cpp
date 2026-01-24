#include <bits/stdc++.h>
using namespace std;

int main() {
    int i, j;
    scanf("%d %d", &i, &j);
    if (i == 1) {
        printf("%d\n", j);
    } else {
        printf("%d\n", i * (j - 1) + 1);
    }
}