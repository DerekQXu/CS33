/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	/*
 	* Accomplishes bang in the following way:
 	*  Subtracting 1 from the absolute value of x returns negative ONLY FOR 0
 	*  Use this fact to detect if the number is 0 or not
 	*/
	int neg = x >> 31;
	return ((((neg^x) + (neg&1))+ ~0)>>31)&1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	/*
 	* Accomplishes bitCount in the following way:
 	*  Create 5 different masks in the following pattern: 
 	*    0101..., 00110011..., 00001111...
 	*  Use these masks to perform the following operations:
 	*    first shift all the bits one time to the LSB
 	*    do this by adding all even bits with odd bits
 	*    continue doing this but shifting the bits 2 and then 4 times
 	*  This is similar to addition, as we're adding the number of bits
 	*    that are in each (2^n) bit chunk.
 	*  By performing the masking and the shifting until x is shifted 32/2
 	*    = 16 times to the left, the final 2 values added is a regular
 	*    addition of the number of bits in the 2 16-bit chunks of the 
 	*    number, giving the final number of 1s in the entire bit vector, x.
 	*/
	int mask0 = 0x55;
	int mask1 = 0x33;
	int mask2 = 0x0f;
	int mask3 = 0xff;
	int mask4 = ~0;
	int cmp0, cmp1, cmp2, cmp3;

	mask0 = (mask0<<8)|mask0;
	mask0 = (mask0<<16)|mask0;

	mask1 = (mask1<<8)|mask1;
	mask1 = (mask1<<16)|mask1;

	mask2 = (mask2<<8)|mask2;
	mask2 = (mask2<<16)|mask2;

	mask3 = (mask3<<16)|mask3;

	mask4 = ~(mask4<<16);

	cmp0 = (x & mask0) + ((x>>1) & mask0);
	cmp1 = (cmp0 & mask1) + ((cmp0>>2) & mask1);
	cmp2 = (cmp1 & mask2) + ((cmp1>>4) & mask2);
	cmp3 = (cmp2 & mask3) + ((cmp2>>8) & mask3);
	
	return (cmp3 & mask4) + ((cmp3>>16) & mask4);
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
	/*
 	* Accomplishes bitOr in the following way:
 	*  DeMorgan's law states that a OR b is the same as  
 	*  NOT NOT a and NOT b
 	*/
	return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
	/*
 	* Accomplishes bitRepeat in the following way:
 	*  We exponentially append x to the number with the following: 
 	*    set x to the first n bits
 	*    Shift x to the right by the size/bit# of x and append x
 	*    Repeat from the shift command
 	*  This allows us to double n-bit x vectors we can shift each shift.
 	*  Note: We want to stop shifting when the value of x is >= than 32
 	*    b/c a right shift of 32 is dangerous.
 	*    We accomplish this by checking if the x vector is larger than 32
 	*    for each time we shift the vectors.
 	*  Note: The first shift was optimized to do a 8-bit mask, so that an
 	*    input of n = 32, does not shift the bit vector 32 times. We utilize
 	*    the fact that the SPEC assumes INPUT N to be in the range [1, 32] so
 	*    that we can disregard leading bits in assuring that the vector shift
 	*    is of value <32 
 	*/
	x = x &~ ((~1)<<(n+0xff)); 
	
	x = (x << (n&0x3F)) | x; 

	n = n << 1;
	x = (x << (n &~ ((32 + ~n)>>31))) | x; 

	n = n << 1;
	x = (x << (n &~ ((32 + ~n)>>31))) | x; 

	n = n << 1;
	x = (x << (n &~ ((32 + ~n)>>31))) | x; 

	n = n << 1;
	return (x << (n &~ ((32 + ~n)>>31))) | x; 
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	/*
 	* Accomplishes fitsBits in the following way:
 	*  shave out the last (n-1) bits and look at the remaining bits 
 	*  if the remaining bits are consistant (all 1s or all 0s) that means
 	*    the number x fit in the n bits, as the MSB of the n bit number is
 	*    consistent with the MSBits of the 32-bit integer
 	*/
	int leadingbits = (x >> (n+~0)) ^ (x >> 31);
	return !leadingbits;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/*
 	* Accomplishes getBytes in the following way:
 	*  Shift the number to the LSBit, and then mask it with the LSByte 
 	*/
	return (x>>(n<<3)) & 0xFF;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	/*
 	* Accomplishes isLessOrEqual in the following way:
 	*  Check if the two numbers are the same sign
 	*  If the sign is equal compute x - y, if the sum is negative y < x
 	*    One can use the inverse of y < x to determine if x >= y  
 	*  If the signs aren't equal, check if x is negative to see if its smaller
 	*/
	int compute = (x^y)>>31;
	int sum = (x + ~y) + 1;
	return ((compute&x) | (~compute&(sum|( ~sum & ( sum + ~0 )))))>>31&1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	/*
 	* Accomplishes isPositive in the following way:
 	*  checks if the leading bit is 0 or 1 determining sign 
 	*  0x00000000 has a positive leading bit, but 0 is not >0, thus make an
 	*    exception if x == 0
 	*/
	return (~(x|( ~x & ( x + ~0 )))>>31)&1;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	/*
 	* Accomplishes logicalShift in the following way:
 	*  Use XOR to make leading bit always 0, to force logical right shift 
 	*  Use a mask to unXOR the input 'x' but NOT unXOR the leading 0s
 	*  Note: mask is computed in 2 lines because the first shift cannot be 32
 	*    as it leads to undefined behavior.
 	*/
	int neg = x >> 31;
	int mask = ~0;
	x = neg^x;
	x = x >> n;
	mask = mask << (31+~(n + ~0));
	mask = mask << 1;
	return (x & mask) | ((x ^neg)&~mask);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/*
 	* Accomplishes bang in the following way:
 	*  the smallest 2s complement integer is 0x80000000  
 	*/
	return (1 << 31);
}
