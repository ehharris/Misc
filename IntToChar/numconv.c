/**
 * Name: Elijah Harris
 * CS270
 * P2
 * ehharris@rams.colostate.edu
 */
#include <stdio.h>
#include <math.h>
/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */


char int2char (int radix, int value) {
    char e;
    if (value > radix - 1 || value < 0 || radix < 2 || radix > 36){
    return '?';
    }
    if (value < 10){
        e = value + 48;
    }
    else{
        e = value + 55;
    }
    return e;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char2int (int radix, char digit) {
    if (digit < 48 || digit > 57){
        if (digit < 65 || digit > 90){
            if(digit < 97 || digit > 122){
                return -1;
            }
        }
    }
    if (digit > 96 && digit < 123){
        // +10
        if (radix >= 2 && (digit - 87) < radix && radix <= 36){
        //if (radix < 2 || (digit - 87) < (radix - 1) || radix > 37){
           int a = digit;
            return a - 87 ;
        }
    }
    if (digit > 64 && digit < 91){
        // +10
         if (radix >= 2 && (digit - 55) < radix && radix <= 36){
        int a = digit;
            return a - 55 ;
        }
    }
    if (digit > 47 && digit < 58){
        if (radix >= 2 && (digit - 48) < radix && radix <= 36){
        int a = digit;
            return a - 48 ;
        }
    }
    return -1;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void divRem (int numerator, int divisor, int* quotient, int* remainder) {
    *remainder = numerator % divisor;
    *quotient = numerator / divisor;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii2int (int radix, int valueOfPrefix) {
    char a = getchar();
    if (a == 10){
        return valueOfPrefix;
    }
    int i = char2int(radix, a);
    valueOfPrefix =  (radix * valueOfPrefix) + i;
    return ascii2int(radix, valueOfPrefix);
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int2ascii (int radix, int value) {
    int quo;
    int rem;
    if (value == 0){
            return;
    }
    divRem(value, radix, &quo, &rem);
    int2ascii(radix, quo);
    printf("%1c", int2char(radix, rem));
    return;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double radbrah;
double frac2double (int radix) {
    char a = getchar();
    float j = 0;
    if(radix < 17){
        radbrah = radix;
    }
    if (a == 10){
        return 0;
    }
    int i = 0;
    if (a > 96 && a < 123){
        // +10
        i = a - 87 ;
        }
    if (a > 64 && a < 91){
        // +10
        i = a - 55 ;
        }
    if (a > 47 && a < 58){
        i = a - 48 ;
        }
    double radi = radix;
    float rad = (1/radi);
    radix = radix * radbrah;
    j = rad * i;
    printf("j = %d\n", radix);
    double e = frac2double(radix);
    return j + e;
}
