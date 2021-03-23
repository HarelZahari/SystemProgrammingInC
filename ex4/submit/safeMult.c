#include <stdio.h>

/*************************************************
*  safeMult.c
*  ----------
*  A program containing functions for safely
*  computing the product of two integer numbers
*************************************************/

/************************************************/
/* IMPORTANT NOTE:                              */
/* !! MODIFY CODE ONLY IN THE MARKED PLACES !!  */
/************************************************/

/********************************/
/**    FUNCTION DECLARATIONS   **/
/********************************/

/*********************************
* Problem 1.2
* computes the product of two int
* parameters as double
*********************************/
double multToDouble(int, int);

/*********************************
* Problem 1.3
* computes the product of two int
* parameters as int
*********************************/
int multToInt(int, int);

/*********************************
* Problem 1.4
* computes the product of two int
* parameters modulo n
*********************************/
int multModulo(int a, int b, int n);


/********************************/
/**    FUNCTION DEFINITIONS    **/
/********************************/

/*********************************
* Problem 1.2
* computes the product of two int
* parameters as double
* params:
* a (int)
* b (int)
* returns axb as double type
*********************************/
double multToDouble(int a, int b) {
   /***                  Problem 1.2:                   ***/
   return (double)a*b;;    /*** <-- ONLY MODIFY EXPRESSION COMPUTED FOR RETURN STATEMENT ***/  
}

/*********************************
* Problem 1.3
* computes the product of two int
* parameters as int
* params:
* a (int)
* b (int)
* returns axb as int type if it can be
* expressed as int. Otherwise, returns 0
*********************************/
int multToInt(int a, int b) {
   double x = multToDouble(a,b);
   /***                  Problem 1.3:                   ***/
   /***             vvvv MODIFY HERE vvvv               ***/
    if (x < 2147483647 && x > -(2147483647))
        return (int) x;
   /***             ^^^^ MODIFY HERE ^^^^               ***/
   return 0;
}


/*********************************
* Problem 1.4
* computes the product of two int
* parameters modulo n
* a (int)
* b (int)
* n (int)
* returns (axb) (mod n) as int.
* makes sure not to overflow in every step
*********************************/
int multModulo(int a, int b, int n) {
   double x = multToDouble(a%n,b%n);
   /***                  Problem 1.4:                   ***/
   return ((long)x)%n;    /*** <-- ONLY MODIFY EXPRESSION COMPUTED FOR RETURN STATEMENT ***/
}







int main() {
   
   printf("Tests for Problem 1.2:\n");
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("multToDouble(%7d,%7d) = %15.1lf\n", 2, -3, multToDouble(2,-3));
   printf("multToDouble(%7d,%7d) = %15.1lf\n", 0, 400, multToDouble(0,400));
   printf("multToDouble(%7d,%7d) = %15.1lf\n", 12345, 67890, multToDouble(12345,67890));
   printf("multToDouble(%7d,%7d) = %15.1lf\n", -100000, 100000, multToDouble(-100000,100000));
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
   
   printf("\nTests for Problem 1.3:\n");
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("multToInt(%7d,%7d) = %10d\n", 2, -3, multToInt(2,-3));
   printf("multToInt(%7d,%7d) = %10d\n", 0, 400, multToInt(0,400));
   printf("multToInt(%7d,%7d) = %10d\n", 12345, 67890, multToInt(12345,67890));
   printf("multToInt(%7d,%7d) = %10d\n", -100000, 100000, multToInt(-100000,100000));
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
   
   printf("\nTests for Problem 1.4:\n");
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("multModulo(%7d,%7d,%7d) = %10d\n", 2, -3, 5, multModulo(2,-3, 5));
   printf("multModulo(%7d,%7d,%7d) = %10d\n", 0, 400, 11, multModulo(0,400, 11));
   printf("multModulo(%7d,%7d,%7d) = %10d\n", 12345, 67890, 30, multModulo(12345,67890,30));
   printf("multModulo(%7d,%7d,%7d) = %10d\n", -100000, 100000, 123, multModulo(-100000,100000, 123));
   printf("multModulo(%7d,%7d,%7d) = %10d\n", 100000, 100000, 123000, multModulo(100000,100000, 123000));
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");


   return 0;
}

