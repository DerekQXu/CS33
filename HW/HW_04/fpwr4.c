static float u2f(unsigned u)
{
    //unions yay!
    union u2f_type{
        float f;
        unsigned z;
    } temp;
    temp.z = u;
    return temp.f;
}

float fpwr4(int x)
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < -74) {	                        //-149 <- (2-2^(8-1))-23 && 2^-148 -> 4^-74 <smallest possible exponent>
        /* Too small. Return 0.0 */
        exp = 0x0;	                        //standard notation for 0
        frac = 0x0;	                        //standard notation for 0
    } else if (x < -63) {	                //-127 <- (2-2*(8-1))-1 && 2^-126 -> 4^-63 <largest possible denormalized number>
        /* Denormalized result */
        exp = 0x0;	                        //standard notation for dNormalized
        frac = 0x1 << (23+((x<<1)+126));	//>>(x*2) . . . bits directly mean fpwr4
    } else if (x < 64) {	                //129 <- 2^8-(2^(8-1)-1)&& 2^128 = 4^64 <largest possible normalized number>
        /* Normalized result */
        exp = (x<<1) + 127;	                //bias = 2^(8-1)-1 = 127, exp = x*2 + bias
        frac = 0x0;	                        //always a multiple of 2 t.f. only need 1 1-bit
    } else {
        /* Too big. Return +oo */
        exp = 0xff;	                        //standard notation for +oo
        frac = 0x0;	                        //standard notation for +oo
    }

    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}
