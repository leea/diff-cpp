/* 
 * Copyright (c) 2012 Allen Lee
 */


#include <cstdio>
#include <iostream>

#ifdef DEBUG
#define debugOut std::cout
#else
#define debugOut if (false) std::cout
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
