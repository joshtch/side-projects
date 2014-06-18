# Prime Sieve of Eratosthenes
import math

def __sieve(maxval):
    if maxval < 0:
        raise Exception("Need non-negative max value")
    l = [False]
    if maxval >= 1:
        l += [False]
        if maxval > 1:
            l += [True]*(maxval - 1)
            root = int(math.sqrt(maxval)) + 1
            for i in xrange(2, root):
                if l[i] == True:
                    for j in xrange(2, (maxval)/i + 1):
                        l[i*j] = False
    return l

def pdict(maxval):
    l = __sieve(maxval)
    result = {}
    for i in xrange(len(l)):
        result[i] = l[i]
    return result

def prime(n):
    if type(n) is not int:
        raise Exception("Bad type")
    elif n < 2:
        return False
    elif n == 2 or n == 3:
        return True
    else:
        for x in xrange(3, sqrt(n)+1, 2):
            if n % x == 0:
                return False
    return True

# Memoized primality function
def xprime(n, hint = 0):
    if "memo" not in xprime.__dict__: xprime.memo = pdict(hint)
    if n not in xprime.memo:
        xprime.memo[n] = prime(n)
    return xprime.memo[n]

