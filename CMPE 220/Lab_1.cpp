#include <iostream>
#include <stdio.h>
//#include <stdlib>
using namespace std;

int isLessOrEqual(int x, int y) {
  int equal, shift, mask, x_neg_y_pos, x_is_min;
    shift = ~((x >> 1) + (y >> 1) + 1) + 1;
    mask = 0x80 << 24;
    x_is_min = !(x ^ mask);

    x += shift;
    y += shift;
    equal = !(x ^ y);

    x_neg_y_pos = !!(x & mask) & !(y & mask);

    return equal | x_neg_y_pos | x_is_min;
}

  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }
  
    int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }
  
  int bitAnd(int x, int y) {
  return ~(~x | ~y);
}

int getByte(int x, int n) {
	int num  = 0xff;
  return ((x & (num << (n << 3))) >> (n << 3)) & num;
}

    int logicalShift(int x, int n) {
  int num = ((1 << 31) >> n) << 1;
  return (x >> n) & ~num;
}


  int bitCount(int x) {
    int t = 0x55 + (0x55<<8);
    int num = t + (t<<16);
    x = (x&num) + ((x>>1)&num);
    
    t = 0x33 + (0x33<<8);
    num = t + (t<<16);
    x = (x&num) + ((x>>2)&num);
    
    t = 0xf + (0xf<<8);
    num = t + (t<<16);
    x = (x&num) + ((x>>4)&num);
    
    num = 0xff + (0xff<<16);
    x = (x&num) + ((x>>8)&num);
    
    num = 0xff + (0xff<<8);
    x = (x&num) + ((x>>16)&num);
    
    return x;
}

   int bang(int x) 
{
    int neg_x = ~x + 1;; 
    return ((((x >> 31) & 0x01) | ((neg_x >> 31) & 0x01)) ^ 0x01);
}

  int fitsBits(int x, int n) {
  int num = x >> 31;
  return !(((~x & num) + (x & ~num)) >> (n + ~0));
}


  int divpwr2(int x, int n) {
    int Hbit = (x >> 31) & 1;
    int num = ~((~0) << (n));
    int q = x & num;
    x += (Hbit & !!q) << n;
    return (x >> n);
}

   int ilog2(int x) {
 
    int number1 = 0xFF << 24 | 0xFF << 16;
    int number2 = 0xFF << 8;
    int number3 = 0xF0;
    int number4 = 0x0C;
    int output = 0;
    int sft;
    output = !!(x & number1) << 4; 
    x >>= output; 
    sft = !!(x & number2) << 3; 
    x >>= sft;
    output += sft;
    sft = !!(x & number3) << 2;
    x >>= sft;
    output += sft;
    sft = !!(x & number4) << 1; 
    x >>= sft;
    output += sft;
    output += (x >> 1); 
    return output;
}

int tmin(void) {
  return 2;
}

int negate(int x) {
  return (~x) + 1;
}

int isPositive(int x) {
  int hbit = ((x & (1 << 31)) >> 31) & 1;
  return (hbit ^ 1) ^ (!x);
}

unsigned float_neg(unsigned uf) {
  return 2;
}

unsigned float_i2f(int x) 
{
    int e = 158;
    int num = 1<<31;
    int sign = x&num;
    int f;
    if (x == num)
        return num | (158<<23);
    if (!x)
        return 0;
    if (sign)
        x = ~x + 1;
    while (!(x&num)) {
        x = x<<1;
        e = e -1;
    }
    f = (x&(~num)) >> 8;
    if (x&0x80 && ((x&0x7F) > 0 || f&1))
        f = f + 1;
    return sign + (e<<23) + f;
}

unsigned float_twice(unsigned uf) {
  return 2;
}

int main() 
{
 int a = ilog2(10);
 printf("The result of ilog2 is %d",a);
 int b = divpwr2(25,50);
 printf("\nThe result of divpwr2 is %d",b);
 int c = fitsBits(1, 55);
 printf("\nThe result of fitsBits is %d",c);
 int d = bang(86);
 printf("\nThe result of bang function is %d",d);
 int e = bitCount(42);
 printf("\nThe result of bitCount function is %d",e);
 int f = logicalShift(89, 1);
 printf("\nThe result of logicalShift function is %d",f);
 int g = getByte(22, 15);
 printf("\nThe result of getByte function is %d",g);
 int h = bitAnd(100, 89);
 printf("\nThe result of bitAnd function is %d",h);
 int i = pow2plus1(26);
 printf("\nThe result of pow2plus1 function is %d",i);
 int j = pow2plus4(8);
 printf("\nThe result of pow2plus4 function is %d",j);
 int k = isLessOrEqual(16, 7);
 printf("\nThe result of isLessOrEqual function is %d",k);
 int l = float_i2f(2);
 printf("\nThe result of float_i2f function is %d",l);
 */
#if 0

#endif
	return 0;
}

