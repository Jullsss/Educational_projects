STYPE bit_reverse(STYPE value) {
    UTYPE x = 0, byte = 0;
    UTYPE l = -1;
    while (l != 1) {
        byte = value & 1;
        x |= byte;
        x <<= 1;
        value >>= 1;
        l >>= 1;
    }
    byte = value & 1;
    x |= byte;
    return x;
}
