"""
minroman.py
Takes a number and returns the roman numeral for that number
Used for solving Project Euler problem 89:
https://projecteuler.net/problem=89
"""

import sys

def min_roman_numeral(number):
    ronum = ""
    tests = ( ("M", 1000),
              ("CM", 900),
              ("D",  500),
              ("CD", 400),
              ("C",  100),
              ("XC",  90),
              ("L",   50),
              ("XL",  40),
              ("L",   10),
              ("IX",   9),
              ("V",    5),
              ("IV",   4),
              ("I",    1) )

    for tup in tests:
        while number >= tup[1]:
            ronum += tup[0]
            number -= tup[1]
    return ronum

def romnum_to_value(num_string):
    curr_char = 'I'
    running_val = 0
    values = { "I" : 1,
               "V" : 5,
               "X" : 10,
               "L" : 50,
               "C" : 100,
               "D" : 500,
               "M" : 1000 }

    for char in num_string[::-1]:
        if values[char] >= values[curr_char]:
            running_val += values[char]
            curr_char = char
        else:
            running_val -= values[char]
    return running_val

def minimized_romnum(romnum):
    return min_roman_numeral(romnum_to_value(romnum))

file = open('input.txt', 'r')
total_shortened = 0
for line in file:
    line = line.strip()
    total_shortened += len(line) - len(minimized_romnum(line))

file.close()
print total_shortened
