#include <stdio.h>
#include <string.h>
#include "/share/ex_data/ex6/bigInt.h"
#include "/share/ex_data/ex6/virtualHeap.h"
/*####################################################################
*  bigInt.c
*  --------------------------------------------------------------------
* This file include functions represent big large integers using arbitrary precision
* This new data structure is based on a structure type named BigInt_st
#####################################################################*/

/*#######################################################################
* Problem 1.1
* Description: receives a pointer to a string that is supposed to represent
* an integer, and it computes and returns the appropriate value of the exponent.
* Parameters: intStr the pointer to the string
* Return: int that represent the exponent value
#######################################################################*/
int computeExponent(const char* intStr) {
    int exp = -1;
    int length = strlen(intStr);
    int i;
    for (i = 0; i < length; i++) {
        if (intStr[i] < '0' || intStr[i] > '9') {
            return -1;
        }
        if (intStr[i] != '0' || exp != -1) {
            exp++;
        }
    }
    if (exp == -1 && i != 0)
        return 0;
    return exp;
}

/*#######################################################################
* Problem 1.2
* Description: receives a pointer to a string that is supposed to represent an integer,
* and returns the length of the mantissa in a “full precision” representation of the number
* Parameters: intStr the pointer to the string
* Return: int that represent the length of the mantissa 
#######################################################################*/
int fullMantissaLength(const char* intStr) {
    int length = strlen(intStr);
    if (length == 0)
        return -1;
    int zerosAtEnd = 0;
    int zerosAtStart = 0;
    int mantissaLength = 0;
    int i;
    for (i = 0; i < length; i++) {
        if (intStr[i] < '0' || intStr[i] > '9')
            return -1;
        if (intStr[i] == '0' && mantissaLength != 0)
            zerosAtEnd++;
        if (intStr[i] != '0' || mantissaLength != 0) {
            mantissaLength++;
            if (intStr[i] != '0') {
                zerosAtEnd = 0;
            }
        } else {
            zerosAtStart++;
        }
    }
    if (zerosAtEnd + zerosAtStart == length && i != 0)
        return 1;
    return length - (zerosAtStart + zerosAtEnd);

}
/*#######################################################################
* Problem 1.3
* Description: receives a pointer to a string that is supposed to represent an integer,
* a pointer to a character buffer, and the (maximum) number of digits to copy.
* The function copies digit characters from the source string to the  target mantissa buffer.
* Parameters: intStr the pointer to the string
*             mantissaBuff the buffer for copy
*             numDigits maximum number of digits to copy
* Return: int (0  or  1) indicating whether there was loss in precision. 
#######################################################################*/
int copyMantissa(const char* intStr, char* mantissaBuff, int numDigits) {
    int mantissaLength = fullMantissaLength(intStr);
    if (numDigits < 1 || mantissaLength == -1) {
        return -1;
    }
    int currentDigit = 0;
    int i = 0;
    int fixZeros = 0;
    while (intStr[i] != '\0' && currentDigit < numDigits && currentDigit < mantissaLength) {
        if (currentDigit != 0 || intStr[i] != '0') {
            if (intStr[i] != '0') {
                mantissaBuff[currentDigit] = intStr[i];
                if (fixZeros != 0) {
                    while (fixZeros != 0) {
                        mantissaBuff[currentDigit - fixZeros] = '0';
                        fixZeros--;
                    }
                }
            } else
                fixZeros++;
            currentDigit++;
        }
        i++;
    }
    if (currentDigit == 0)
        mantissaBuff[currentDigit++] = '0';
    if (fixZeros == 0)
        mantissaBuff[currentDigit] = '\0';
    else
        mantissaBuff[currentDigit - fixZeros] = '\0';
    if (mantissaLength <= numDigits)
        return 1;
    else
        return 0;
}
/*#######################################################################
* Problem 1.4
* Description: receives a pointer to a string that is supposed to represent an integer
* and the (maximum) number of mantissa digits.
* The function creates a new BigInt object by allocating space for it on the heap, 
* copying digit characters from the source string to the mantissa, and setting the fields appropriately.
* Parameters: intStr the pointer to the string
*             numDigits maximum number of digits to copy
* Return: new BigInt object or NULL if allocation failed
#######################################################################*/
BigInt newBigInt(const char* intStr, int numDigits) {
    char sign;
    int exp;
    if ((!(intStr[0] >= '0' && intStr[0] <= '9')) && (intStr[0] != '+' && intStr[0] != '-')) {
        return NULL;
    }
    if (intStr[0] == '+' || intStr[0] == '-') {
        sign = intStr[0];
        intStr++;
    } else
        sign = '+';
    exp = computeExponent(intStr);
    if (exp == -1 || exp > 255) {
        return NULL;
    }

    BigInt newElement = ourMalloc(sizeof (BigInt_st));
    if (!newElement) { //Allocation failed
        return NULL;
    }
    char copyOfMantissa[strlen(intStr)];
    if (numDigits <= 0)
        copyMantissa(intStr, copyOfMantissa, strlen(intStr));
    else
        copyMantissa(intStr, copyOfMantissa, numDigits);
    newElement->mantissa = ourMalloc(sizeof (char)*(strlen(copyOfMantissa) + 1));
    if (!(newElement->mantissa)) {
        ourFree(newElement);
        return NULL;
    }

    strcpy(newElement->mantissa, copyOfMantissa);
    int mantissaZeroFlag = 0;
    for (int i = 0; i < strlen(newElement->mantissa); i++) {
        if (newElement->mantissa[i] != '0')
            mantissaZeroFlag = 1;
    }
    if (mantissaZeroFlag == 1)
        newElement->sign = sign;
    else
        newElement->sign = '+';
    newElement->exp = exp;
    return newElement;
}

/*#######################################################################
* Problem 1.5
* Description: receives a pointer to a BigInt object and it frees all space allocated
* by the object.
* Parameters: bigInt pointer to the object
* Return: void
#######################################################################*/
void freeBigInt(BigInt bigInt) {
    if (bigInt) {
        if (bigInt->mantissa)
            ourFree(bigInt->mantissa);
        ourFree(bigInt);
    }
}
/*#######################################################################
* Problem 1.6
* Description: receives a pointer to a BigInt object and a number indicating
* the required precision, and it prints the number in the following format:<sign><mantissa>e<exp>
* Parameters: bigInt pointer to the object
*             precision the required precision 
* Return: void
#######################################################################*/
void printBigInt(BigInt bigInt, int precision) {
    if (bigInt) {
        int length = strlen(bigInt->mantissa);
        if (length < precision && precision != 0)
            length = precision;
        if (precision <= 0) {
            precision = length;
        }
        char newMantissa[length];
        if (precision >= strlen(bigInt->mantissa)) {
            copyMantissa(bigInt->mantissa + 1, newMantissa, precision);
            int i;
            for (i = strlen(bigInt->mantissa) - 1; i < length - 1; i++) {
                newMantissa[i] = '0';
            }
            newMantissa[i] = '\0';
        } else {
            copyMantissa(bigInt->mantissa + 1, newMantissa, precision - 1);
        }
        if (precision == 1) {
            printf("%c%ce%d", bigInt->sign, bigInt->mantissa[0], bigInt->exp);
        } else {
            printf("%c%c.%se%d", bigInt->sign, bigInt->mantissa[0], newMantissa, bigInt->exp);
        }
    }
}
/*#######################################################################
* Problem 1.7
* Description: receives pointers to two BigInt objects and returns a number
* (-1, 0, or 1) indicating which one of them is large.
* Parameters: bigInt1 pointer to the first object
*             bigInt2 pointer to the second object 
* Return: int that indicate which one of them is large
#######################################################################*/
int compareBigInt(BigInt bigInt1, BigInt bigInt2) {
    if (bigInt1->sign == '+' && bigInt2->sign == '-')
        return 1;
    if (bigInt1->sign == '-' && bigInt2->sign == '+')
        return -1;
    if ((bigInt1->exp)>(bigInt2->exp)) {
        if (bigInt1->sign == '+')
            return 1;
        else
            return -1;
    }
    if ((bigInt1->exp)<(bigInt2->exp)) {
        if (bigInt1->sign == '+')
            return -1;
        else
            return 1;
    }
    int i = 0;
    while (bigInt1->mantissa[i] != '\0' && bigInt2->mantissa[i] != '\0') {
        if ((bigInt1->mantissa[i])>(bigInt2->mantissa[i])) {
            if (bigInt1->sign == '+')
                return 1;
            else
                return -1;
        }
        if ((bigInt1->mantissa[i])<(bigInt2->mantissa[i])) {
            if (bigInt1->sign == '+')
                return -1;
            else
                return 1;
        }
        i++;
    }
    if (strlen(bigInt1->mantissa) == strlen(bigInt2->mantissa)) {
        return 0;
    } else {
        if (strlen(bigInt1->mantissa) < strlen(bigInt2->mantissa)) {
            if (bigInt1->sign == '+')
                return -1;
            else
                return 1;
        } else {
            if (bigInt1->sign == '+')
                return 1;
            else
                return -1;
        }
    }
}
