
#include "src/big_unsigned.h"
#include "src/big_prime_field.h"
#include "gtest/gtest.h"

namespace {

TEST(BigUnsigned, Add) {
  BigUnsigned n = BigUnsigned("1267650600228229401496703205376"); // 2^100
  BigUnsigned two(2); 

  EXPECT_EQ(n + n, two * n);
}

// 1849764852316
TEST(BigPrimeField, Add) {
  BigUnsigned p("1849764852316");
  BigPrimeField::set_prime(p);
  BigPrimeField n("1267650600228229401496703205376"); // 2^100
  BigPrimeField res("1037610352464");
  
  EXPECT_EQ(n + n, res);
}


TEST(BigPrimeField, SubtractPositive) {
  BigUnsigned p("1849764852316");
  BigPrimeField::set_prime(p);
  BigPrimeField n("1267650600228229401496703205376"); // 2^100
  BigPrimeField n2("123456789123456789");
  BigPrimeField res("1114309858401");

  EXPECT_EQ(n2 - n, res);
}


TEST(BigPrimeField, SubtractNegative) {
  BigUnsigned p("1849764852316");
  BigPrimeField::set_prime(p);
  BigPrimeField n("1267650600228229401496703205376"); // 2^100
  BigPrimeField n2("123456789123456789");
  BigPrimeField res("735454993915");

  EXPECT_EQ(n - n2, res);
}

TEST(BigPrimeField, Multiply) {
  BigUnsigned p("1849764852316");
  BigPrimeField::set_prime(p);
  BigPrimeField n("1267650600228229401496703205376"); // 2^100
  BigPrimeField res("464726607316");

  EXPECT_EQ(n * n, res);
}


TEST(BigPrimeField, Divide) {
  BigUnsigned p("184976485289");
  BigPrimeField::set_prime(p);
  BigPrimeField n("1267650600228229401496703205376"); // 2^100
  BigPrimeField d("123456789");
  BigPrimeField res("157546369834");

  BigPrimeField got = n / d;
    got.big_int.show();
  EXPECT_EQ(got, res);
}

TEST(BigPrimeField, DivideSimple) {
  BigUnsigned p("37");
  BigPrimeField::set_prime(p);
  BigPrimeField n("1");
  BigPrimeField d("2");
  BigPrimeField res("19");

  BigPrimeField got = n / d;
  got.big_int.show();
  EXPECT_EQ(got, res);
}


} // namespace