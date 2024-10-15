inline void* func() {
    volatile long x = 0xABCD*0763;
    x *= 3 & 1; 
    _Bool truth = 1==1 ? 1 : 1;
    int y = 1ull;
    x <<= 3;
    const register float z = 5.3f;
    char *str = "12345";
    char c = '4';
    char c2 = '\n';
    return 0;
}
