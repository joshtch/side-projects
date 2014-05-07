"""
Distinct primes factors
Problem 47
http://projecteuler.net/problem=47

The first two consecutive numbers to have two distinct prime factors are:

14 = 2 * 7
15 = 3 * 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2^2 * 7 * 23
645 = 3 * 5 * 43
646 = 2 * 17 * 19.

Find the first four consecutive integers to have four distinct prime factors.
What is the first of these numbers?
"""

def uniques(l):
    current = 1
    uniques = []
    for n in l:
        if n > current:
            current = n
            uniques += [n]
        else:
            uniques[-1] *= n
    return uniques

def prime_factors(n):
    curr_factor = 2
    factors = []
    while n > 1:
        if n % curr_factor == 0:
            n /= curr_factor
            factors += [curr_factor]
        else:
            curr_factor += 1
    return uniques(factors)

def solve_p47(n):
    consecutive_nums = []
    counter = 2
    while len(consecutive_nums) < n:
        if len(prime_factors(counter)) == n:
            consecutive_nums += [counter]
        else:
            consecutive_nums = []
        counter += 1
    return consecutive_nums

print solve_p47(4)
