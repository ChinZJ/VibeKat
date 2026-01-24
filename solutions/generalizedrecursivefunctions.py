n = int(input())

def solve(memo, pairs, x, y, c, d):
    if (x, y) in memo:
        return memo[(x, y)]
    elif (x <=0 or y <= 0):
        memo[(x, y)] = d
        return d
        
    tot = c
    for a, b in pairs:
        tot += solve(memo, pairs, x - a, y - b, c, d)
    memo[(x, y)] = tot
    return tot
        

for _ in range(n):
    desc = list(map(int, input().split()))
    queries = list(map(int, input().split()))
    
    c = desc[-2]
    d = desc[-1]
    
    pairs = []
    for i in range(0, len(desc) - 2, 2):
        pairs.append((desc[i], desc[i+1]))
    
    xy_pairs = []
    for i in range(0, len(queries), 2):
        xy_pairs.append((queries[i], queries[i+1]))
        
    memo = {}
    
    for x, y in xy_pairs:
        print(solve(memo, pairs, x, y, c, d))
    
    print()
    
    