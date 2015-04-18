#include "buffer.h"

#define BUFFERSIZE 10
int putPos = 0;
int getPos = 0;
 
int buffer[BUFFERSIZE];
 
int nextPos(int pos) 
{
   return (pos + 1) & (BUFFERSIZE-1);
}
 
int isEmpty(void) {
   return getPos == putPos;
}
 
int isFull(void) {
   return nextPos(putPos) == getPos;
}
 
void put(int value)
{
   buffer[putPos] = value;
   putPos = nextPos(putPos);
}
 
int get(void)
{
   int value = buffer[getPos];
   getPos = nextPos(getPos);
   return value;
}

int * getarray(void){
  return buffer;
}