"""
Josh Howe
Riemann Sums Challenge Project
Math 36-02, Fall 2013
Sept. 4, 2013, Riemann sums

Prompt: Write a program, in the language of your choice, to compute a Riemann
sum. That is, given a polynomial function in x and a number of partitions, the
program should compute the corresponding Riemann sum.
"""
import math

# ------ Calculating Riemann Sums ------ #

def riemann(f, a, b, n):
    if a == b: print "All Riemann sums equal zero because a = b."; return

    Dx = (b-a)/n
    # Left Riemann = [f(a) + f(a+Dx) + f(a+2Dx) + ... + f(b-Dx)]*Dx
    print "Left Riemann:   %.2f" % (sigma(a,Dx,b-Dx,f)*Dx)

    # Right Riemann = [f(a+Dx) + f(a+2Dx) + f(a+3Dx) + ... + f(b)]*Dx
    print "Right Riemann:  %.2f" % (sigma(a+Dx,Dx,b,f)*Dx)

    # Middle Riemann = [f(a+Dx/2) + f(a+Dx/2+Dx) + ... + f(b-Dx/2)]*Dx
    print "Middle Riemann: %.2f" % (sigma(a+Dx/2,Dx,b-Dx/2,f)*Dx)

# Calculates the total sums of function(x) for x = start, x = start + delta,
# x = start + 2*delta, x = start + 3*delta etc. until x reaches the end
# This function is a bit more flexible than the mathematical Sigma function;
# instead of stepping by one over a contiguous set of integers, this works for
# all real numbers, and steps by whatever "delta" is set to. If the iteration
# never equals 'end' exactly, the sum will just stop short.
def sigma(start, delta, end, function):
    sum = 0.0; x = start
    while x <= end: sum += function(x); x += delta
    return sum


# ------ Getting Input ------ #

import re # Python's regular expressions module

print "Please input your desired function. Whitespace will be ignored."
f_str = raw_input("f(x) = ")

f_str = f_str.lower()                      # Make all chars lowercase
f_str = f_str.expandtabs().replace(" ","") # Clear all tabs and spaces

# This should catch most bad input
if re.search("^[^\dx(\-]", f_str):
    print "Error: Input starts with invalid character."
    exit()
if re.search("[^\dx+\-*/()^]+", f_str):
    print "Error: Input contains invalid character."
    exit()
if re.search("[^\dx)]$", f_str):
    print "Error: Input ends with invalid character."
    exit()
if re.search("[*/+-][*/+]", f_str):
    print "Error: Function operator is repeated."
    exit()

# Convert f_str into python-readable format
f_str = f_str.replace("^", "**")       # Replace ^ with **
def repl(m): return m.group(1)+"*x"    # A not-so-anonymous lambda for doing:
f_str = re.sub(r"([\dx])x",repl,f_str) # Add * before x if needed, continued

# Convert f_str into the actual function f(x)
def f(x): return eval(f_str.replace("x","(%f)"%x))

# Finish checking for invalid input via edge cases
try:
    f(-1.5), f(-1), f(0), f(0.5), f(1.0/2), f(1), f(f(2))
except SyntaxError:
    print "Error: Invalid function."
    exit()

# For floating point numbers Python already has an established idiom for
# checking bad input
try:
    a = float(raw_input("a = "))
    b = float(raw_input("b = "))
    n = float(raw_input("n = "))
except SyntaxError:
    print "Error: Not a number."
    exit()

if n <= 0 and a != b:
    print "Error: n must be greater than 0."
    exit()


# ----- Execution ----- #

#Executes the Riemann sum function
riemann(f, a, b, n)
