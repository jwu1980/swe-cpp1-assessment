#ifndef BIG_PRIME_FIELD_H
#define BIG_PRIME_FIELD_H
#include "big_unsigned.h"

class BigPrimeField {
public:
    
    static void set_prime(BigUnsigned &p){
        prime = p;
    }
    
    BigPrimeField() {
        big_int.clear();
    }
    
    
    
    BigPrimeField(int num) {
        big_int.set_num(num);
    }
    
    BigPrimeField(const string& str) {
        for(int i = str.length() - 1; i  >= 0 ; i--){
            big_int.push_back(int(str[i])-int('0'));
        }
    }
    
    // Comparison operators
    bool operator!=(const int other) const {
        BigPrimeField pf(other);
        return big_int != pf.big_int;
    }
    
    // Comparison operators
    bool operator==(const BigPrimeField& other) const {
        return big_int == other.big_int;
    }
    
    BigPrimeField operator+(const BigPrimeField& other) {
        BigPrimeField res;
        res.big_int = (big_int + other.big_int) % prime;
        return res;
    }
    
    BigPrimeField operator+=(const BigPrimeField& other) {
        return *this + other;
    }
    
    BigPrimeField operator-(const BigPrimeField& other) {
        BigPrimeField res;
        BigUnsigned tmp = other.big_int;
        //e.g. (11 - 7) % 10 = 4, (7 - 11) % 10 = 6
        if(big_int > other.big_int){
            res.big_int = (big_int - other.big_int) % prime;
        }
        else{
            //Since we didn't implement negative subtraction (7 - 11), 
            //so we do (11 - 7) = 4 than do 10 - (4 mod 10).
            res.big_int = prime - (tmp - (const BigUnsigned)big_int) % prime;
        }
        
        return res;
    }
    
    BigPrimeField operator-=(const BigPrimeField& other) {
        return *this - other;
    }
    
    BigPrimeField operator-() const{
        return *this;
    }
    
    BigPrimeField operator*(const BigPrimeField& other) const{
        BigPrimeField res;
        res.big_int = (big_int * other.big_int) % prime;
        return res;
    }
    
    BigUnsigned power(BigUnsigned in, BigUnsigned n) const{
        BigUnsigned res("1");
        pair<BigUnsigned, BigUnsigned> quot_rem;
        while(n > BigUnsigned("0")) {
            if((n % BigUnsigned("2")) == BigUnsigned("1")) {
                res = (res * in) % prime;
            }
            in = (in * in) % prime;
            quot_rem = n / BigUnsigned("2");
            n = quot_rem.first;
        }
        return res;
    }
    
    BigPrimeField inverse(const BigPrimeField &in) const{
        BigPrimeField res;
        res.big_int = power(in.big_int, prime - BigUnsigned("2"));
        return res;
    }
    
    BigPrimeField operator/(const BigPrimeField& other) const{
        return *this * inverse(other);
    }
    
    BigUnsigned big_int;
private:
    static BigUnsigned prime;
    
    
};

#endif