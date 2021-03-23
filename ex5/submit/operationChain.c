#include <stdio.h>
#include <string.h>
#define MAX_INT_LEN 12
#define MAX_NUMS 10

/*####################################################################
*  operationChain.c
*  ----------
*  This file do arithmetic operation on int array
#####################################################################*/

/*###################################################################*/
/**  Declarations  **/
/*##################################################################*/

char* intToString(int num, char* buffer);
char* intToStringList(const int* numArray, int arrayLen, char* buffer);
char* nextIntString(char* intStrList);
int doOpChain(char* intStrList, char op, char* res_intStr);
int doOp(char* intStr1, const char* intStr2, char op);
int isIntString(const char* str);
int stringToInt(const char* str);

/*#######################################################################
* Problem 3
* Description: program take at most 10 int numbers and chain op them
* Parameters: none (scanf input)    
* Return: 1 if all the process was legit, 0 otherwise.
#######################################################################*/
int main () {
    printf("Please enter an operator (+ or *) followed by up to 10 integer numbers.\n");
    char op;
    scanf("%c", &op);
    if (op!='+'&&op!='*'){
        printf("Invalid operator %c\n",op);
        return 1;
    }
    char buffer1[MAX_INT_LEN*MAX_NUMS];
    char buffer2[MAX_INT_LEN*MAX_NUMS];
    int arrNum [10]={0};
    int arrLength=0;
    double currentNum;
    for(int i=0;i<MAX_NUMS;i++){
        if(scanf("%lf", &currentNum)==1){
           if (currentNum==0 || currentNum / (int) currentNum == 1) {
                arrNum[i] = (int) currentNum;
                arrLength++;
            } else {
                if (i == 0) {
                    printf("No valid numbers were entered\n");
                    return 1;
                } else {
                    i = MAX_NUMS;
                }
            }
        }else {
                if (i == 0) {
                    printf("No valid numbers were entered\n");
                    return 1;
                } else {
                    i = MAX_NUMS;
                }
            }
    }
    intToStringList(arrNum,arrLength,buffer1);
    if(doOpChain(buffer1,op,buffer2)!=1){
        printf("Result is out of bound\n");
        return 1;
    }else{
       printf("= %d\n",stringToInt(buffer2));
       return 0;
    }          
}
 
                