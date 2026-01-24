import sys

from collections import defaultdict, deque, Counter
from heapq import heappush, heappop, heapify, heapreplace, nlargest, nsmallest
from bisect import bisect_left, bisect_right
from functools import lru_cache
from itertools import accumulate, permutations, combinations
import itertools # for itertools.count()
from math import gcd, sqrt, ceil, floor, factorial


# Fast I/O - equivalent to cin.tie(0)->sync_with_stdio(0)
# input = sys.stdin.readline

INF = float("inf")

def lcm(a, b):
    return a * b // gcd(a, b)

def comb(n, k):
    if k < 0 or k > n:
        return 0
    return factorial(n) // (factorial(k) * factorial(n - k))

def perm(n, k):
    if k < 0 or k > n:
        return 0
    return factorial(n) // factorial(n - k)

def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    a, b, c = map(int, input().split())
    s = input().strip() # Remove trailing newline
    
    pass

grids = []
currgd = []

def drawVert(cnt, ci, se, pse):
    if se > pse:
        se, pse = pse, se
    global grids
    for i in range(se+1, pse):
        if (grids[cnt][i][ci] == '.'):
            grids[cnt][i][ci] = '|'
        elif (grids[cnt][i][ci] == '-'):
            grids[cnt][i][ci] = '+'

def drawHor(cnt, ri, fi, pfi):
    if fi > pfi:
        fi, pfi = pfi, fi
    global grids
    for i in range(fi+1, pfi):
        if (grids[cnt][ri][i] == '.'):
            grids[cnt][ri][i] = '-'
        elif (grids[cnt][ri][i] == '|'):
            grids[cnt][ri][i] = '+'


def main():
    global grids, currgd

    text = sys.stdin.read()

    for line in text.splitlines():
        if line.strip() == "":
            if currgd:
                grids.append(currgd)
                currgd = []
        else:
            currgd.append(list(line))

    if currgd:
        grids.append(currgd)

    for cnt, grid in enumerate(grids):
        hm = {}
        mn = -1
        ma = ""
        mA = ""
        for ri in range(len(grid)):
            for ci in range(len(grid[ri])):
                val = grid[ri][ci]
                if val == ".":
                    continue
                else:
                    hm[val] = (ri, ci)
                    if (val.isdigit()):
                        mn = max(mn, int(val))
                    elif val.islower():
                        ma = max(ma, val)
                    else:
                        mA = max(mA, val)

        if mn != -1:
            for i in range(mn):
                fi, se = hm[str(i)]
                pfi, pse = hm[str(i+1)]
                if (fi == pfi):
                    drawHor(cnt, fi, se, pse)
                else:
                    drawVert(cnt, se, fi, pfi)

        if (mn == 9 and ma != ""):
            fi, se = hm['9']
            pfi, pse = hm['a']
            if (fi == pfi):
                drawHor(cnt, fi, se, pse)
            else:
                drawVert(cnt, se, fi, pfi)

        if ma != "":
            for i in range(ord('a'), ord(ma)):
                fi, se = hm[chr(i)]
                pfi, pse = hm[chr(i+1)]
                if (fi == pfi):
                    drawHor(cnt, fi, se, pse)
                else:
                    drawVert(cnt, se, fi, pfi)

        if (ma == 'z' and mA != ""):
            fi, se = hm['z']
            pfi, pse = hm['A']
            if (fi == pfi):
                drawHor(cnt, fi, se, pse)
            else:
                drawVert(cnt, se, fi, pfi)

        if mA != "":
            for i in range(ord('A'), ord(mA)):
                fi, se = hm[chr(i)]
                pfi, pse = hm[chr(i+1)]
                if (fi == pfi):
                    drawHor(cnt, fi, se, pse)
                else:
                    drawVert(cnt, se, fi, pfi)

        for row in grid:
            print(''.join(row))
        if (cnt < len(grids) - 1):
            print()
    

if __name__ == "__main__":
    main()