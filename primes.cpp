/* Comparison of prime generator functions
 * modulus:    count up and check each number for divisibility
 * char sieve: Erastothenes sieve using char vector
 * bit sieve:  Erastothenes' sieve using bit vector (better locality)
 *
 * Conclusion so far: modulus > char > bit in terms of time required
 * With -O3 flag, the latter two are two orders of magnitude faster (with
 * sufficiently large MAX_VAL) and bit is slightly under an order of magnitude
 * faster than char. No surprises anywhere, except maybe that bitsieve is only
 * slightly faster than charsieve.
 *
 * TODO: Sieve of Atkin? Segmented sieve?
 */

#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

const int MAX_VAL = 30000000;

void modulus();
void char_sieve();
void bit_sieve();
#define METHOD modulus()

int main()
{
    time_t t = clock();
    METHOD;
    std::cout << clock() - t << std::endl;
    return EXIT_SUCCESS;
}

void modulus()
{
    std::vector<int> primes;
    primes.push_back(2);
    int i, j, maxval, psize;
    bool is_prime;
    std::vector<int>::iterator it;

    for (i = 3; i < MAX_VAL; i += 2) {
        maxval = sqrt(i) + 1;
        psize = primes.size();
        is_prime = true;
        for (it = primes.begin(); is_prime && it < primes.cend() && *it < maxval; ++it)
            if (i % *it == 0)
                is_prime = false;

        if (is_prime) primes.push_back(i);
    }
}

void char_sieve()
{
    std::vector<char> primes (MAX_VAL, true);
    std::vector<char>::iterator it, lead_iter;
    int i;

    primes[0] = primes[1] = false;

    for (i = 0, it = primes.begin(); i <= MAX_VAL && it < primes.cend(); ++it, ++i)
        if (*it)
            for (lead_iter = it + i; lead_iter < primes.cend(); lead_iter += i)
                *lead_iter = false;
}

void bit_sieve()
{
    std::vector<bool> primes (MAX_VAL, true);
    std::vector<bool>::iterator it, lead_iter;
    int i;

    primes[0] = primes[1] = false;

    for (i = 0, it = primes.begin(); i <= MAX_VAL && it < primes.cend(); ++it, ++i)
        if (*it)
            for (lead_iter = it + i; lead_iter < primes.cend(); lead_iter += i)
                *lead_iter = false;
}

