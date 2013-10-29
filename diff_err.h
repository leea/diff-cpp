/* 
 * Copyright (c) 2012 Allen Lee
 */


/* Error handling functions from Richard Steven's "Advanced
   Programming in the Unix Environment" */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

#define MAXLINE 256

#ifdef DEBUG
#define debugOut cout
#else
#define debugOut if (false) cout
#endif


template <typename _RandomAccessSequence1Ty, 
          typename _RandomAccessSequence2Ty>
void dprintMatrix(_RandomAccessSequence1Ty Orig, 
                   _RandomAccessSequence2Ty New) {    
#ifdef DEBUG_MATRIX
  printf("   ");
  for (unsigned int x = 0; x < New.size(); ++x)
    printf ("%2c ", New[x]);
  printf ("\n");
  for (unsigned int y = 0; y < Orig.size(); ++y){
    printf ("%2c ", Orig[y]);
    for (unsigned int x = 0; x < New.size(); ++x)
      printf(" . ");
    printf ("\n");
  }
#else
#ifdef DEBUG
  printf("New: ");
  for (unsigned int x = 0; x < New.size(); ++x)
    printf ("%c", New[x]);
  printf ("\nOrig: ");
  for (unsigned int y = 0; y < Orig.size(); ++y)
    printf ("%c", Orig[y]);
  printf ("\n");
#endif
#endif
}
