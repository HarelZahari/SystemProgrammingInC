#ifndef SORTED_BIG_INT_LIST_H
#define SORTED_BIG_INT_LIST_H

/**************************************
*  Header file for the SortedBigIntList
*  data structure for holding a sorted
*  linked list of BigInt objects
**************************************/
#include "/share/ex_data/ex6/bigInt.h"


/*************************************/
/**     SYMBOLIC  CONSTANTS         **/
/*************************************/
#define INC   0
#define DEC   1

/*************************************/
/**           OBJECT  TYPE          **/
/*************************************/

/*** The object type is a pointer to the
     structure type that you are required
     to define in Problem 2.1 in the
     source file sortedBigIntList.c
***/
typedef struct SortedBigIntList_st* SortedBigIntList;

/*************************************/
/**      FUNCTION  DECLARATION      **/
/*************************************/

/*** Problem 2.2: allocate space for SortedBigIntList object on the heap ***/
SortedBigIntList newSortedBigIntList(int listType);

/*** Problem 2.3: add a BigInt object to a given sorted list (in place) ***/
int addBigIntToSortedList(SortedBigIntList list, BigInt bigInt);

/*** Problem 2.4: print all BigInt objects in a given SortedBigIntList ***/
void printSortedBigIntList(SortedBigIntList list, int precision);

/*** Problem 2.5: free all space allocated by a given SortedBigIntList object ***/
void freeSortedBigIntList(SortedBigIntList list);

#endif
