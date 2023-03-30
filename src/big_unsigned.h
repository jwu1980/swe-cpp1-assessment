#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class BigUnsigned  {
// Put your implementation here
public:
    BigUnsigned(){
        clear();
    }
    
    BigUnsigned(int in) {
        num.clear();
        while (in > 0) {
            num.push_back(in % 10); // Store the least significant digits in the vector
            in /= 10; // Shift right
        }
        if (num.empty()) {
            num.push_back(0); // If number is zero, store one digit
        }
    }
    
    void set_num(const string& str) {
        for(int i = str.length() - 1; i  >= 0 ; i--){
            num.push_back(int(str[i])-int('0'));
        }
    }
    
    BigUnsigned(const string& str) {
        set_num(str);
    }
    
    
    
    int size() const{
        return num.size();
    }
    
    int empty() const{
        return num.empty();
    }
    
    void clear(){
        num.clear();
    }
    
    void resize(int n){
        num.resize(n);
    }
    
    void push_back(int a){
        num.push_back(a);
    }
    
    
    void pop_back(){
        num.pop_back();
    }
    
    int back(){
        return num.back();
    }
    
    
    void show() const{
        // cout<<"size:"<<num.size()<<endl;
        for(int i = num.size() - 1; i  >= 0 ; i--){
            cout<<num[i];
        }
        cout<<endl;
    }
    
    int operator[](int idx) const{
        return num[idx];
    }
    
    BigUnsigned operator+(const BigUnsigned& in) {
        BigUnsigned res;
        int carry = 0;
        int sum = 0;
        for(int i = 0; i < in.size() || i < size() || carry != 0; i++){
            sum = carry;
            if(i < in.size())
                sum += in[i];
            if(i < size())
                sum += num[i];
            res.push_back(sum % 10);
            carry = sum / 10;
        }
        return res;
    }
    
    BigUnsigned operator-(const BigUnsigned& in) {
        BigUnsigned res;
        int carry = 0;
        int diff = 0;
        for(int i = 0;  i < size(); i++){
            diff = num[i] - carry;
            if(i < in.size())
                diff -= in[i];
            if(diff < 0){
                diff += 10;
                carry = 1;
            }
            else{
                carry = 0;
            }
            res.push_back(diff);
        }
        while (!res.empty() && res.back() == 0) {
            res.pop_back();
        }
        if (res.empty()) {
            res.push_back(0);
        }

        return res;
    }
    
    BigUnsigned operator*(const BigUnsigned& in) const{
        BigUnsigned res;
        vector<long long> prod;
        prod.resize(in.size() + size());
        long long carry = 0;
        
        int i, j;
        for(i = 0;  i < in.size(); i++){
            for(j = 0;  j < size(); j++){
                prod[i + j] += in[i] * num[j];
            }
        }
        long long sum;
        for(i = 0;  i < prod.size(); i++){
            sum = prod[i] + carry;
            carry = sum / 10; 
            res.push_back(sum % 10);
        }
        while(res.back() == 0)
            res.pop_back();
        return res;
    }
    
    bool operator<(const BigUnsigned& other) const {
        if (num.size() != other.size()) {
            return num.size() < other.size();
        }
        for (int i = num.size()-1; i >= 0; i--) {
            if (num[i] != other[i]) {
                return num[i] < other[i];
            }
        }
        return false;
    }
    
    // Comparison operators
    bool operator==(const BigUnsigned& other) const {
        if (num.size() != other.size()) {
            return false;
        }
        for (int i = 0; i < num.size(); i++) {
            if (num[i] != other[i]) {
                return false;
            }
        }
        return true;
    }
        
    bool operator<=(const BigUnsigned& other) const {
        return (*this < other) || (*this == other);
    }

    bool operator>(const BigUnsigned& other) const {
        return !(*this <= other);
    }

    bool operator>=(const BigUnsigned& other) const {
        return !(*this < other);
    }
    
    pair<BigUnsigned,BigUnsigned> operator/(const BigUnsigned& divisor) const{
        BigUnsigned quotient("0");
        BigUnsigned remainder("0");
        
        for (int i = size() - 1; i >= 0; i--) {
            remainder = remainder * BigUnsigned("10") + BigUnsigned(num[i]);
            int count = 0;
            while (remainder >= divisor) {
                count++;
                remainder = remainder - divisor;
            }
            quotient.push_back(count);
        }

        reverse(quotient.num.begin(), quotient.num.end());
        // Remove leading zeros
        while (quotient.size() > 1 && quotient.back() == 0) {
            quotient.pop_back();
        }
        return make_pair(quotient, remainder);
    }
    
    
    BigUnsigned operator%(const BigUnsigned& in) const{
        BigUnsigned res;
        //First: quotient, Second: remainder
        pair<BigUnsigned, BigUnsigned> quot_rem = *this/in;
        
        return quot_rem.second;
    }
    
private:
    vector<int> num;
};

#endif