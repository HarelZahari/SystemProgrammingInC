#ifndef BIG_INT_H
#define BIG_INT_H

/**************************************
*  Header file for the BigInt data 
*  structure for representing large
*  int numbers with arbitray precision
**************************************/

/*************************************/
/**         STRUCTURE  TYPE         **/
/*************************************/
typedef struct {
   char sign;        /** sign character '+' or '-'          **/
   char* mantissa;   /** string holding mantissa characters **/
   char exp;         /** exponent in [0 , 255]              **/
} BigInt_st;

typedef BigInt_st* BigInt;

/*************************************/
/**      FUNCTION  DECLARATION      **/
/*************************************/

/*** Problem 1.1: compute the exponent corresponding to a given int given as a string ***/
int computeExponent(const char* intStr);

/*** Problem 1.2: compute the length of the full mantissa corresponding to a given int given as a string ***/
int fullMantissaLength(const char* intStr);

/*** Problem 1.3: copy mantissa digits from an int (given as string) into a given buffer ***/
int copyMantissa(const char* intStr, char* mantissaBuff, int numDigits);

/*** Problem 1.4: allocate space for new BigInt object on the heap ***/
BigInt newBigInt(const char* intStr, int numDigits);

/*** Problem 1.5: free all space allocated by a given BigInt object ***/
void freeBigInt(BigInt bigInt);

/*** Problem 1.6: print a given BigInt object in the following format: <sign><mantissa>e<exp> ***/
void printBigInt(BigInt bigInt, int precision);

/*** Problem 1.7: compare the values of two BigInt objects ***/
int compareBigInt(BigInt bigInt1, BigInt bigInt2);

#endif
