#include <stddef.h>

#include "operators.h"

unsigned long long globalmask = DEFAULT_MASK;
int globalmasksize = DEFAULT_MASK_SIZE;

operation operations[16] = {
    {0, 0, NULL},
    {'+', 2, add},
    {'-', 2, subtract},
    {'*', 2, multiply},
    {'/', 2, divide},
    {'&', 2, and},
    {'|', 2, or},
    {'$', 2, nor},
    {'^', 2, xor},
    {'<', 2, sl},
    {'>', 2, sr},
    {'(', 2, rl},
    {')', 2, rr},
    {'%', 2, modulus},
    {'~', 1, not},
    {'\'', 1, twos_complement}
};

operation* getopcode(char c)  {

    for (unsigned long i=0; i < sizeof(operations); i++)
        if (operations[i].character == c)
            return &operations[i];

    return NULL;
}


long long add(long long a, long long b) {

    return a + b;
}

// remember op1 = first popped ( right operand ), op2 = second popped ( left operand )
long long subtract(long long a, long long b) {

    return b - a;
}
long long multiply(long long a, long long b) {

    return a * b;
}

long long divide(long long a, long long b) {

    //TODO not divisible by 0
    if(!a)
        return 0;
    return b / a;
}

long long and(long long a, long long b) {

    return a & b;
}

long long or(long long a, long long b) {

    return a | b;
}

long long nor(long long a, long long b) {

    return ~or(a,b);
}

long long xor(long long a, long long b) {

    return a ^ b;
}
long long sl(long long a, long long b) {

    return b << a;
}

long long sr(long long a, long long b) {

    return (b >> a) & ~((long long) -1 << (64-a));
}

long long rl(long long a, long long b) {

    return b << a | sr(globalmasksize-a, b);
}

long long rr(long long a, long long b) {

    return sr(a, b) | ( b << (globalmasksize- a) );
}

long long modulus(long long a, long long b) {

    //TODO not divisible by 0
    if(!a)
        return 0;

    return b % a;
}

long long not(long long a, long long UNUSED(b)) {

    return ~a;
}

long long twos_complement(long long a, long long UNUSED(b)) {

    return -a;
}
