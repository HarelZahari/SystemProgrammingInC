/**************************************
*  Source file for the virtual heap
*  code module which records all memory
*  allocation operations
**************************************/
#include <stdio.h>
#include <stdlib.h>

/*************************************/
/**       SYMBOLIC CONSTANTS        **/
/*************************************/
#define MAX_ALLOCATED_BLOCKS         10000
#define DEFAULT_MAX_ALLOCATED_BYTES  10000

/*************************************/
/**          TYPE DEFINITIONS       **/
/*************************************/
typedef struct {
   void* address;
   int numBytes;
} AllocatedBlocks;

/*************************************/
/**         GLOBAL VARIABLES        **/
/*************************************/
/*** number of successfully allocated bytes ***/
int numAllocatedBytes  = 0;
/*** number of successfully allocated blocks ***/
int numAllocatedBlocks = 0;
/*** max size of "virtual heap" ***/
int maxAllocatedBytes  = DEFAULT_MAX_ALLOCATED_BYTES;
/*** array of allocated blocks - start address and size ***/
AllocatedBlocks allocatedBlocks[MAX_ALLOCATED_BLOCKS];


/*************************************/
/**      FUNCTION  DEFINITIONS      **/
/*************************************/

/*** memory allocation function ***/
void* ourMalloc(int numBytes) {
   void* ptr;
   if(numAllocatedBytes + numBytes > maxAllocatedBytes) {
      printf("Virtual heap: Allocation tries to exceed max number of bytes - %d\n" , maxAllocatedBytes);
      return NULL;
   }
   if(numAllocatedBlocks + 1 > MAX_ALLOCATED_BLOCKS) {
      printf("Virtual heap: Allocation tries to exceed max number of blocks - %d\n", MAX_ALLOCATED_BLOCKS);
      return NULL;
   }
   ptr = malloc(numBytes);
   if(!ptr) {
      printf("Virtual heap: malloc failed when current allocation sizse is %d bytes and asking for %d additional bytes\n", numAllocatedBytes, numBytes);
      return NULL;
   }
   allocatedBlocks[numAllocatedBlocks].address = ptr;
   allocatedBlocks[numAllocatedBlocks].numBytes = numBytes;
   numAllocatedBlocks++;
   numAllocatedBytes += numBytes;
   // fprintf(stderr, "Virtual heap: allocating block with %d bytes.\n", numBytes);

   return ptr;
}   

/*** memory freeing function ***/
void ourFree(void* ptr) {
   int i;
   for(i=0; i<numAllocatedBlocks; i++) {
      if(allocatedBlocks[i].address == ptr) break;
   }
   if(i==numAllocatedBlocks) {
      printf("Virtual heap: Error - trying to free address %p that was never returned by ourMalloc()\n", ptr);
      return;
   }
   free(ptr);

   numAllocatedBlocks--;
   numAllocatedBytes -= allocatedBlocks[i].numBytes;
   allocatedBlocks[i] = allocatedBlocks[numAllocatedBlocks];
   allocatedBlocks[numAllocatedBlocks].address =  NULL;
   allocatedBlocks[numAllocatedBlocks].numBytes =  0;
}

/*** free all resources allocated by virtual heap ***/
void freeAll() {
   while(numAllocatedBlocks>0) {
      ourFree(allocatedBlocks[numAllocatedBlocks-1].address);
   }
}

/*** returns bound on number of bytes user can allocate ***/
int getMaxBytes() {
   return maxAllocatedBytes;
}

/*** set bound on number of bytes user can allocate ***/
void setMaxBytes(int maxBytes) {
   if(maxBytes < numAllocatedBytes) {
      printf("Virtual heap: Error - trying to reduce max number of allocated bytes to %d when virtual heap has %d allocated bytes\n", maxBytes, numAllocatedBytes);
      return;
   }
   maxAllocatedBytes = maxBytes;
}


/*** returns number of allocated bytes ***/
int getNumAllocatedBytes() {
   return numAllocatedBytes;
}


/*** returns number of allocated blocks of memory ***/
int getNumAllocatedBlocks() {
   return numAllocatedBlocks;
}
