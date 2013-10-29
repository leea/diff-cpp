#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdint.h>
#include <assert.h>
#include <cstdio>

typedef unsigned int u_int;

using std::vector;
// Static 2D Vector class using a 1D array as the backing store.
template <typename T>
class Matrix
{
  uint16_t ColLen;
  uint16_t Rows;
  T * _matrix;

public:
  Matrix(T rows, T cols): 
    Rows(rows) {_matrix = new T[Rows*cols];}
  ~Matrix() {delete[] _matrix;}
  void DebugPrint();
  // Returning a pointer here allows the double array index [][] to
  // work correctly
  inline T* operator[](size_t row) {return _matrix + (row*Rows); }
};

template <typename T>
void Matrix<T>::DebugPrint()
{
#ifdef DEBUG_MATRIX
  u_int i,j;
  printf ("   ");
  for (j = 0; j < ColLen; ++j)
    printf ("%2d ", j);
  printf ("\n");
  for (i = 0; i < Rows; ++i){
    printf ("%2d ", i);
    for (j = 0; j < ColLen; ++j)
      printf("%2.2d ", (*this)[i][j]);
    printf("\n");
  }
#endif
}

// 2D vector class that supports negative column indexes used to
// translate Myers Algorithm.  The number of columns in this matrix is
// 2 times larger than the max column.  IE the range of the column
// indexes is [-MAXCOL, MAXCOL-1]
template <typename T>
class NegIndexVector
{
  size_t MaxNegIndex;
  size_t MaxPosIndex;
  size_t size;
  T* _vector;
public:
  NegIndexVector() {}
  NegIndexVector(size_t MaxNegIndex, size_t MaxPosIndex):
    MaxNegIndex(MaxNegIndex), MaxPosIndex(MaxPosIndex),
    size(MaxNegIndex + MaxPosIndex +1),
    _vector(new T[size]()){}
  ~NegIndexVector() { delete[] _vector; }
  inline T& operator[] (int index) { 
    assert((index + (int)MaxNegIndex >= 0) && (index + MaxNegIndex < size));
    return _vector[index + MaxNegIndex];
  }
};

template <typename T>
class NegColMatrix 
{
  typedef NegIndexVector<T> NegVector;
  uint16_t Rows;
  vector <NegVector> _matrix;

public:
  NegColMatrix():
    Rows(1), _matrix(vector<NegVector> (1, NegVector(1, 1))){}

  void NewRow() {
    Rows++;
    _matrix.push_back(NegVector(Rows, Rows));

    for (int i = -Rows +1; i < Rows-1; i++)
      _matrix[Rows-1][i] = _matrix[Rows-2][i];
  }
  inline NegVector& operator[](size_t row) {
    // cout << "Accessed _matrix " << row << "\n";
    assert (row < Rows); 
    return _matrix[row]; 
  }
  void DebugPrint();
};

template <typename T>
void NegColMatrix<T>::DebugPrint()
{
#ifdef DEBUG_MATRIX
  int j;
  printf ("  ");
  for (j = -Rows; j < Rows; ++j)
    printf ("%3.2d", j);
  printf ("\n");
  for (int i = 0; i < Rows; ++i){
    printf ("%2d ", i);
    for (j = -Rows; j < Rows; ++j){
      if (j < -(i+1))
        printf ("   ");
      else if (j > i+1)
        printf ("   ");
      else
        printf("%2.2d ", (*this)[i][j]); 
    }
    printf("\n");
  }
#endif
}

#endif
