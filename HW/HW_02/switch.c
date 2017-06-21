long switch_prob(long x. long n) {
    long result = x;
    switch (n) {
    case 60:
    case 62:
        result = 0x8 * x;
        break;
    case 63:
        result = x;
        result = result >> 0x3;
        break;
    case 64:
        result = x;
        result = result << 0x4;
        result -= x;
        x = result;
    case 65:
        x = x*x;
    default:
        result = x+0x4b;
    }
    return result;
}
