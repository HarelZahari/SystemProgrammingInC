#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int multModulo(int a, int b, int n);
int expMod(int a, int exp, int n);
int expMod_efficient(int a, int exp, int n);
int findFermatWitness(int n, int numReps);
int getMSBpos(int a);
int getNextBitPos(int a);
int getLSBpos(int a);

int multModulo(int a, int b, int n) {
    double x = (double) (a % n)*(b % n);
    return ((long) x) % n;
}

int expMod(int a, int exp, int n){
    if(a<=0 || n<=0 || exp <0){
        return 0;
    }else{
        if(exp!=0){
            int aWithExp=a;
            for(int i=0;i<exp-1;i++){
                aWithExp=multModulo(aWithExp,a,n);
            }
            return aWithExp%n;
            }
        else return 1%n;
    }
}

int getMSBpos(int a)  {
    int msbPos = -1;
    unsigned newA = (unsigned) a;
    if (a == 0) {
        return msbPos;
    } else {
        msbPos = (getMSBpos(newA >> 1) + 1);
        return (msbPos);
    }
}

int getLSBpos(int a) {
    int lsbPos = -1;
    if (a == 0) {
        return -1;
    } else {
        if (a & 1 == 1) {
            return ++lsbPos;
        } else {
            lsbPos = (getLSBpos(a >> 1) + 1);
            return (lsbPos);
        }
    }
}

int getNextBitPos(int a) {
   static int last_a   =  0;
   static int last_pos = -1;

    int msbOfA = getMSBpos(a);
    if (msbOfA == last_pos && a == last_a) {
        last_pos = -1;
        return -1;
    }
    if (a != last_a) {
        last_a = a;
        last_pos = getLSBpos(a);
    } else {
        a = a >> last_pos + 1;
        int currentPos = getLSBpos(a);
        last_pos = currentPos + last_pos + 1;
    }
   return last_pos;
}

int expMod_efficient(int a, int exp, int n){
    if(a<=0 || n<=0 || exp <0){
        return 0;
    }else{
        int posMSB=getMSBpos(a);
        int Ak=a%n;
        int MultModResult=1;
        int currentIndex=getNextBitPos(a);
        for(int i=0;i<=posMSB;i++){
            if(currentIndex==i){
                MultModResult=multModulo(Ak,MultModResult,n);
                currentIndex=getNextBitPos(a);
            }
            Ak=multModulo(Ak,Ak,n);
        }
        return MultModResult;
    }
}

int findFermatWitness(int n, int numReps){
 if(numReps<1 || n<3)
     return 0;
 for(int i=0;i<numReps;i++){
     int currentN=(rand() % (n-2))+2;
     int x=expMod_efficient(n,currentN-1,currentN);
     if(x!=1){
         return currentN;
     }
 }
 return 0;
}

int main () {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("multModulo(%7d,%7d,%7d) = %10d\n", 2, -3, 5, multModulo(2, -3, 5));
    printf("multModulo(%7d,%7d,%7d) = %10d\n", 0, 400, 11,
            multModulo(0, 400, 11));
    printf("multModulo(%7d,%7d,%7d) = %10d\n", 12345, 67890, 30,
            multModulo(12345, 67890, 30));
    printf("multModulo(%7d,%7d,%7d) = %10d\n", -100000, 100000, 123,
            multModulo(-100000, 100000, 123));
    printf("multModulo(%7d,%7d,%7d) = %10d\n", 100000, 100000, 123000,
            multModulo(100000, 100000, 123000));
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    
    printf("%d\n",expMod(2, 10, 5));
    printf("%d\n",expMod(10, 111, 3));
    printf("%d\n",expMod(10, 1, 3));
    printf("%d\n",expMod(123, 123, 321));
    printf("%d\n",expMod(3063695, 6700412,6700413));
    printf("%d\n",expMod(6700415, 6700416, 6700417));
    printf("%d\n",expMod(10, 0, 5));
    printf("%d\n",expMod(10, -1,5));
    printf("%d\n",expMod(10, 3, 0));
    printf("%d\n",expMod(-10, 3, 2));
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    //srand(time(NULL));
    //printf("%d\n",findFermatWitness(5,100));
  // printf("%d\n",findFermatWitness(4,1));
   // printf("%d\n",findFermatWitness(3,100));
   // printf("%d\n",findFermatWitness(2,11));
   // printf("%d\n",findFermatWitness(1,13));
   // printf("%d\n",findFermatWitness(0,1));
  //  printf("%d\n",findFermatWitness(10,0));
  //  printf("%d\n",findFermatWitness(10,-10));
  //  printf("%d\n",findFermatWitness(11,100));
  //  printf("%d\n",findFermatWitness(353,1000));
  //  printf("%d\n",findFermatWitness(6700417,1000000));
  //  printf("%d\n",findFermatWitness(6700413, 1000));
        
  //  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    
    printf("%d\n",expMod_efficient(2, 10, 5));
    printf("%d\n",expMod_efficient(10, 111, 3));
    printf("%d\n",expMod_efficient(10, 1, 3));
    printf("%d\n",expMod_efficient(123, 123, 321));
    printf("%d\n",expMod_efficient(3063695, 6700412,6700413));
    printf("%d\n",expMod_efficient(6700415, 6700416, 6700417));
    printf("%d\n",expMod_efficient(10, 0, 5));
    printf("%d\n",expMod_efficient(10, -1,5));
    printf("%d\n",expMod_efficient(10, 3, 0));
    printf("%d\n",expMod_efficient(-10, 3, 2));
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    return 0;
}
/*
int main () {
    srand(time(NULL));
    printf("Plesae enter a positive integer to be tested for primality\n");
    double x;
    int a;
    scanf("%lf", &x);
    if (x < 2147483647 && x > -(2147483647)){
        a=(int) x;
        if(a!=x){
            printf("Not a valid positive int\n");
            return 1;
        }
        int witnessRes=findFermatWitness(a,100);
        if(witnessRes!=0){
            printf("The number %d is a Fermat witness that number %d is not prime\n",witnessRes,a);
        }else{
            printf("The number %d is potentially prime. not Fermat witness found\n",a);
        }
    }else{
        printf("Not a valid positive int\n");
        return 1;
    } 
    return 0; 
}
 */