int
bitcount(STYPE value)
{
    int k = 0;
    UTYPE value1;
    value1 = (UTYPE) value;
    while (value1 != 0) {
        k += value1 & 1;
        value1 >>= 1;
    }
    return k;
}
