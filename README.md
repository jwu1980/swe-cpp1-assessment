# swe-cpp1-assessment

## Problem
Implement a big integer prime field library in C++.

### Step 1

As you may have heard, cryptography uses a lot of large prime numbers.  We first need a way to represent arbitrarily large integers in C++ and perform arithmetic operations on them. Implement a `BigUnsigned` in `big_unsigned.h` that implements addition, subtraction, multiplication and division.  Note that division is a function that returns a quotient and a remainder.  Example usage:

```
BigUnsigned a("5678912345678");
BigUnsigned b("1234567");

b += a * a
```

### Step 2

 We also employ what are called prime fields, a fancy math term for operations that happen modulo some prime number.  For example, if we assume our prime is 13, then 7 + 11 = 5.  The prime number is static for a given application, but should be changeable at runtime for supporting different applications.  Implement a `BigPrimeField` class in `big_prime_field.h` that implements addition, subtraction, multiplication and division. Note that division is only defined by calculating a [multiplicative inverse](https://en.wikipedia.org/wiki/Finite_field_arithmetic#Multiplicative_inverse).  You might need signed integer arithmetic beyond your BigUnsigned implemented above.  Example usage:

```
BigUnsigned p("123456768987654321");
BigPrimeField::set_prime(p);
BigPrimeField big("99998888333");

// A bunch of computations on big and other numbers.
big += big * big;
...
```

## Scoring
The assessment will be judged on:
1. Correctness - If it passes all the given tests (plus some extra ones)
2. Speed - scored relative to a hidden baseline implementation.

This will happen by running the `score.sh` script, which reports on both of these.