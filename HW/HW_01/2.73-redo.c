#include <limits.h>
//behaves robustly: allows hardware to leverage following:
//	ints can be any word size multiple of 8
//	will not compute the addition if overflow (in case of undefined behavior)

int saturating_add(int x, int y)
{
	//compute if there is positive or negative overflow 
	int min_overflow = (x & y) >> ((sizeof(int)<<3)-1);
	int max_overflow = (~x & ~y) >> ((sizeof(int)<<3)-1);
	
	//compute if there is overflow
	int sum;
	int is_overflow = (__builtin_add_overflow(x,y,&sum) << ((sizeof(int)<<3)-1)) 
		>> ((sizeof(int)<<3)-1); 

	//return the result
	return( (is_overflow & ((max_overflow & INT_MAX) | (min_overflow & INT_MIN)))|
		(~is_overflow & sum) );
}
