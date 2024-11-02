#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/signal.h>
#include <util/delay.h>
#include <stdlib.h>

#ifndef HELPER_H
#define HELPER_H

//Functionality - finds the greatest common divisor of two values
//Parameter: Two long int's to find their GCD
//Returns: GCD else 0
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a % b;
		if( c == 0 ) { return b; }
		a = b;
		b = c;
	}
	return 0;
}

// computes gcd of entire array
unsigned int findGCD_Array(const unsigned int *arr, unsigned int size) {
	unsigned int curr_gcd = arr[0];
	for (unsigned int i = 1; i < size; i++) {
		curr_gcd = findGCD(curr_gcd, arr[i]);
	}
	return curr_gcd;
}

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
              //   Set bit to 1           Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

 
int nums[16] = {0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011, 0b1110111, 0b0011111, 0b1001110, 0b0111101, 0b1001111, 0b1000111 }; 
// a  b  c  d  e  f  g

void outNum(int num){
	PORTD = nums[num] << 1;
  	PORTB = SetBit(PORTB, 1 ,nums[num]&0x01);
}


//aFirst/Second: First range of values
//bFirst/Second: Range of values to map to
//inVal: value being mapped
unsigned int map_value(unsigned int aFirst, unsigned int aSecond, unsigned int bFirst, unsigned int bSecond, unsigned int inVal)
{
	return bFirst + (long((inVal - aFirst))*long((bSecond-bFirst)))/(aSecond - aFirst);
}


// Function to find the maximum of two numbers
short max(short a, short b) {
    return (a > b) ? a : b;
}

// Function to find the minimum of two numbers
short min(short a, short b) {
    return (a < b) ? a : b;
}

// absolute value of floats
float fabs(float a) {
	if (a < 0) return -a;
	return a;
}

// absolute value of short ints
short abs(short a) {
	if (a < 0) return -a;
	return a;
}

float rand_incl(float min, float max) {
	return min + ((float)rand() / RAND_MAX) * (max - min);
}
#endif /* HEPLER_H */