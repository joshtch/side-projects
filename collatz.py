"""
collatz.py

The collatz conjecture:
    if n is even, halve it;
    if n is odd, multiply by three and add one
    Repeat until a cycle is reached or n becomes 1
    Conjecture: n will reach 1 for all n >= 1

This is a little program to compute the number of steps for a given number to
reach 1
"""

def num_steps(z):
    if z == 1:
        return 1
    if n % 2 == 1:
        return 1 + num_steps(n * 3 + 1)
    else:
        return 1 + num_steps(n / 2)

# These functions are just a slightly optimized method to prove a given number
# follows the collatz conjecture
def clear_trailing_0(z):
        n = int(z)
        while n % 2 == 0:
                n /= 2
        return n

def collatzify(z):
        n = int(z)
        if n % 2 == 1:
                return clear_trailing_0(n * 3 + 1)
        else:
                return clear_trailing_0(n)
