#include <stdio.h>
#include <string.h>

/*####################################################################
*  intStringList.c
*  ----------
*  This file include functions that make manipulation on list of strings
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
* Problem 2.1
* Description: create a string list of numbers from array of int
* Parameters: numArray the array of the integers
*             arrayLen the length of the numArray
*            buffer pointer the string list of the number       
* Return: pointer to the string list (buffer)
#######################################################################*/
char* intToStringList(const int* numArray, int arrayLen, char* buffer){
  char* buffercpy=buffer;
    int currentIndex=0;
    int currentLength=0;
    if(arrayLen<=0){
        *buffercpy='\0';
        *(buffercpy++)='\0';
        return buffer;
    }else{
        for(int i=0;i<arrayLen;i++){
            intToString(numArray[i],(buffercpy+currentIndex));
            currentLength=strlen(buffercpy+(currentIndex))+1;
            currentIndex=currentLength+currentIndex;
        }
        *(buffercpy+currentIndex)='\0';
        return buffer;
    }    
}
/*#######################################################################
* Problem 2.2
* Description: function return a pointer the the next number in the list
* Parameters: intStrList pointer the the start of the string list
* Return: pointer to the next number in the string list
#######################################################################*/
char* nextIntString(char* intStrList){
    static char* lastString=NULL;
    static char* lastIntStrPointer=NULL;
    if(intStrList==NULL){
        lastString=NULL;
        lastIntStrPointer=NULL;
        return NULL;
    }else{
        if (intStrList != lastString || lastIntStrPointer==NULL || lastString==NULL) {
            lastString = intStrList;
            lastIntStrPointer = intStrList;
            return lastIntStrPointer;
        } else {
            if (*lastIntStrPointer != '\0') {
                while(*lastIntStrPointer!='\0'){
                    lastIntStrPointer++;
                }
                lastIntStrPointer++;
            } else {
                return lastIntStrPointer;
            }
            return lastIntStrPointer;
        }
    }
}
/*#######################################################################
* Problem 2.3
* Description: the function do the op operation on all numbers of list
* Parameters: intStrList pointer the the start of the string list
*             op char that represent the operation symbol
*             res_intStr pointer to string representation of the result  
* Return: 1 if all the process was legit, 0 otherwise.
#######################################################################*/
int doOpChain(char* intStrList, char op, char* res_intStr){
    int keepBeforedoOp;
    nextIntString(NULL);
    if((op!='*'&&op!='+')||isIntString(intStrList)==0){
        return 0;
    }else{
        strcpy(res_intStr,nextIntString(intStrList));
        char * currentNum=nextIntString(intStrList);
        while(*currentNum!='\0'){
            if(isIntString(currentNum)==0){
                nextIntString(NULL);
                return 0;
            }
                keepBeforedoOp=stringToInt(res_intStr);
                if(doOp(res_intStr,currentNum,op)==0){
                    nextIntString(NULL);
                    return 0;
                }
                if(isIntString(res_intStr)==0){
                    intToString(keepBeforedoOp,res_intStr);
                    nextIntString(NULL);
                    return 0;
                }
                currentNum=nextIntString(intStrList);          
        }
        nextIntString(NULL);
        return 1;
    }
}


