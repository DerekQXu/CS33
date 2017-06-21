int any_odd_one(unsigned x)
{
	//use 0xaaaaaaaa on a 32-bit integer to only operate on odd-bits
	return 1 && (x & 0xaaaaaaaa);
}
