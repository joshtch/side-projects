"""
Prime digit replacements
Problem 51

By replacing the 1st digit of the 2-digit number *3, it turns out that six of
the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit
number is the first example having seven primes among the ten generated numbers,
yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993.
Consequently 56003, being the first member of this family, is the smallest prime
with this property.

Find the smallest prime which, by replacing part of the number (not necessarily
adjacent digits) with the same digit, is part of an eight prime value family.
"""
import primes

FAMILY_SIZE = 8

def members(prototype):
    [prototype.replace("x", str(n)) for n in xrange(10)]

found = False
i = 2
while not found:
    if xprime(i):
        for family in iterfamilies(i):
            if family == 8:
                found = True
                print i

def subseq(l):
    if not l:
        yield []
    else:
        for r in perm(l[1:]):
            yield r
            yield [l[0]] + r

def check(s,ps):
    n = int(s[ps[0]])
    num_prime = 0
    for i in xrange(n,10):
        pass

def family_search(prime_str, counts):
    for c in "012":
        if counts[c] > 1:
            ps = pos(prime_str,c)

