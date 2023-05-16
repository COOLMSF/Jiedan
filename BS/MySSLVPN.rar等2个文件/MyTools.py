import math

def eratosthenes(n):
    visit=[False]*(n+1)
    m= int(math.sqrt(n+0.5))
    for i in range(2,m+1):
        if (not visit[i]):
            for j in range(i*i,n+1,i):
                visit[j]=True
    res=list()
    for i in range(2,n+1):
        if not visit[i]:
            res.append(i)
    return res

def gcd(a,b):
    if a<b:
        temp=a
        a=b
        b=temp
    while (b != 0):
        temp = a % b
        a=b
        b=temp
    return a

def fast_pow(x,pow):
    res = 1
    while(pow != 0):
        if ((pow & 1) == 1):
            res = res * x
        pow=pow//2
        x=x*x
    return res

def inverse(x,mod):
    return fast_pow_mod(x,mod-2,mod)

def fast_pow_mod(x,pow,mod):
    x=x%mod
    pow=pow%mod
    res = 1
    while(pow != 0):
        if ((pow & 1) == 1):
            res = (res % mod * (x%mod))% mod
        pow=pow>>1
        x=((x%mod)*(x%mod))%mod
    return res%mod

def simple_inv(x,mod):
    for i in range(1,mod):
        if (x*i)%mod==1:
            return i
    return -1

def is_prime(x):
    if(x<2):
        print("x should be int and bigger than 2")
    if x==2 or x==5:
        return True
    m = int(math.sqrt(x + 0.5))
    if x&1==0 or x&0x111==5:
        return False
    for i in range(3,m,2):
        if x%i==0:
            return False
    return True

def ext_euclid(a, b):
    if b == 0:
        return 1, 0, a
    else:
        x, y, q = ext_euclid(b, a % b)
        # q = gcd(a, b) = gcd(b, a%b)
        x, y = y, (x - (a // b) * y)
        return x, y, q

def ext_euclid_inv(a,b):
    res = ext_euclid(a,b)
    x = res[0]
    return x % b