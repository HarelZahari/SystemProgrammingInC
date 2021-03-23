#include <stdio.h>
#include <string.h>

/*####################################################################
*  intString.c
*  ----------
*  This file include functions that make manipulation on strings
#####################################################################*/

/*###################################################################*/
/**  Declarations  **/
/*##################################################################*/

int stringToInt(const char* str);
int isIntString(const char* str);
char* intToString(int num, char* buffer);
int doOp(char* intStr1, const char* intStr2, char op);

/*#######################################################################
* Problem 1.1
* Description: convert string to int
* Parameters: const char* str (the string that need to convert)
* Return: int number that represent by the str input
#######################################################################*/
int stringToInt(const char* str) {
    double parseResult=0;
    int sign=1;
    if ((*str != '-')&&((*str > '9') || (*str < '1')))
        return parseResult;
    if ((*str == '-'))
    {
        if((*(++str))=='0'){
            return parseResult;
        }else{
            sign=-1;
        }
    }
   
    while (*str){
        if ((*str <= '9') && (*str >= '0')) {
            parseResult=parseResult*10+(*str-'0');
        } else{
            return 0;
        }
        str++;
    }
    if((sign*parseResult)/(int)(sign*parseResult)==1){
        return (int)(sign*parseResult);
    }else
        return 0;
}
/*#######################################################################
* Problem 1.2
* Description: check if string represent legal number
* Parameters: const char* str (the string that need to check)
* Return: 1 if str is a legal number, 0 otherwise.
#######################################################################*/
int isIntString(const char* str){
    if(strlen(str)==1 && *str=='0')
        return 1;
    else
        if(stringToInt(str)!=0)
            return 1;
        else
            return 0;
}
/*#######################################################################
* Problem 1.3
* Description: convert int to string
* Parameters: int num (the number that need to convert)
*             char* buffer the location for the string representation    
* Return: pointer for the string representation
#######################################################################*/
char* intToString(int num, char* buffer){
    int currentIndex=0;
    if(num/10==0){
        if(num<0)
        {
            *buffer='-';
            buffer++;
            *buffer=((num*(-1))%10)+'0';
            buffer++;
            *buffer='\0';
            return buffer-2;
        }else
            *buffer=((num)%10)+'0';
        buffer++;
        *buffer='\0';
        return --buffer;
    }
    intToString(num/10,buffer);
    currentIndex=strlen(buffer);
    if(num<0)
            *(buffer+currentIndex)=((num*(-1))%10)+'0';
        else
            *(buffer+currentIndex)=((num)%10)+'0';
    
    currentIndex++;
    *(buffer+currentIndex)='\0';
    return buffer;
}
/*#######################################################################
* Problem 1.4
* Description: the function do a arithmetic operations on two string
* Parameters: intStr1 first string for operation
*             intStr2 second string for operation 
*             op char that represent the operation symbol    
* Return: pointer for the string representation the result (intStr1)
#######################################################################*/
int doOp(char* intStr1, const char* intStr2, char op){
  double opResult=0;
    if(isIntString(intStr1)==0 || isIntString(intStr2)==0)
        return 0;
    double num1=stringToInt(intStr1);
    double num2=stringToInt(intStr2);
    switch(op){
        case '+':
            opResult=num1+num2;
            if( opResult==0 || (int)opResult/opResult==1){
                intToString((int)opResult,intStr1);
                return 1;
            }else{
                return 0;
            }
            break;
        case '-':
            opResult=num1-num2;
            if(opResult==0 || (int)opResult/opResult==1){
                intToString((int)opResult,intStr1);
                return 1;
            }else{
                return 0;
            }
            break;
        case '*':
            opResult=num1*num2;    
            if(opResult==0 || (int)opResult/opResult==1){
                intToString((int)opResult,intStr1);
                return 1;
            }else{
                return 0;
            }
            break;
        default:
            return 0;
    }
}



