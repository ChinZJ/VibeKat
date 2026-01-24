import math

m, n, t = map(int, input().split())

if (t == 7):
    print("AC" if n <= m else "TLE")
elif (t == 6):
    print("AC" if (n * math.log2(n) <= m) else "TLE") 
elif (t == 5):
    print("AC" if (n ** 2 <= m) else "TLE") 
elif (t == 4):
    print("AC" if (n ** 3 <= m) else "TLE") 
elif (t == 3):
    print("AC" if (n ** 4 <= m) else "TLE") 
elif (t == 2):
    print("AC" if (2 ** n <= m) else "TLE") 
else:
    res = n
    flip = False
    while (n-1):
        n = n -1
        res = res * n
        if (res > m):
            print("TLE")
            flip = True
            break
        
    if (not flip):
        print("AC")