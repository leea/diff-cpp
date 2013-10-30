#ifndef LCH_H
#define LCS_H

#include "Matrix.h"
#include "RandomAccessSequence.h"
#include "DiffErr.h"
#include <cassert>
#include <sstream>
#include <list>


//TODO get rid of these
#define max(N,M) ((N)>(M)? N : M)
#define min(N,M) ((N)<(M)? N : M)

typedef NegIndexVector<uint32_t> Vector;

/** 
    This class encapsulates operations used on (col, row) positions
    in the matrix that's used to trace the D-Path
*/

class Position {
public:
  u_int x;
  u_int y;
  Position(){}
  Position(u_int col, u_int row):
    x(col), y(row){}
  inline bool operator==(Position RHS)
  { return y==RHS.y && x == RHS.x; }
  inline bool operator!=(Position RHS)
  { return !(*this == RHS); }

  inline Position operator--(){
    --y; --x; 
    return *this;
  }
  inline Position operator++(){
    ++y; ++x;
    return *this;
  }
  friend std::ostream &operator << (std::ostream &out, Position &p) {  
    return out << "(" << p.x << "," << p.y << ")"; 
  } 
};

/*  Hirshberg's linear space refinement relies on being able to run
 *  the same algorithm in the forward and reverse direction. When the
 *  direction is FORWARD, the algorithm starts at (0, 0) and searches
 *  forward. When the direction is REVERSE, the algorithm stars at
 *  (Orig.size(), New.size()) and searches backward. */
typedef enum {FORWARD, REVERSE} Direction;

template < Direction dir,
           typename _RandomAccessSequenceTy >
class MyersAlgorithm {

  typedef std::list<typename _RandomAccessSequenceTy::ElemTy> LCSList;

  _RandomAccessSequenceTy Orig;
  _RandomAccessSequenceTy New;
  int size_delta;

  unsigned D;
  Vector V;

/** Takes a position that would be an offset from the beginning of the
    seqence in the forward direction and mirrors it so that it's an
    offset from the end of the sequence.
 */
  inline Position normalize(Position p){
    if(dir == REVERSE)
      return Position(New.size() - p.x, Orig.size() - p.y);
    else
      return p;
  }

/** Extends the longest possible snake from position front,
    returning the last position of the snake
    
    @param Front the first position
*/
  inline Position snake(Position front) {

    Position norm = normalize(front);

    debugOut << " snake: front=" << front  << " normalized=" << norm << std::endl;
    
    assert(front.y <= Orig.size() && front.x <= New.size());
    while (front.y < Orig.size() && front.x < New.size() && 
           (dir==FORWARD ? 
            Orig[norm.y] == New[norm.x] : Orig[norm.y-1] == New[norm.x-1])) {
      ++front;
      norm = normalize(front);
    }
    return front;

  }

  /**
   * Computes the starting diagonal for Myer's algorithm
   *
   */
  int k_begin() {

    // if D has grown larger than Orig.size(), set the k to the first
    // starting diagonal within the matrix

    if (D >= Orig.size()) {
      // Since diagonals are increased with steps of 2, set the
      // starting diagonal depending on whether the delta of D and
      // Orig.size is even or odd.
      const int delta = D - Orig.size();
      
      if (delta % 2 == 0){
        return -(Orig.size()-2);
      } else {
        return -(Orig.size()-1);
      }
    } 
    else return -D;
  }

  /**
   * Computes the stopping diagonal for Myer's algorithm
   *
   * 
   */
  int k_end(){

    // if D has grown larger than New.size(), set the end to the last
    // diagonal within the matrix

    if (D >= New.size()){ 
      // Since diagonals are increased with steps of 2, set the
      // ending diagonal depending on whether the delta of D and
      // New.size is even or odd.
      const int delta = D - New.size();
      if (delta % 2 == 0){
        return (New.size()-2);
      } else {
        return (New.size()-1);
      }
    } 
    else return D;
  }


public:
  
  /** 
   * Computes the furthest reaching D-paths.  
   *
   * This function makes one "step", computing the furthest reaching D
   * path for all diagonals from k_begin() to k_end()
   */
  bool trace_D_path() {
    if(dir==FORWARD) {debugOut<< "Forward: \n";} else debugOut<< "Reverse: \n";
    debugOut << " trace_D_path: ";

    int kBegin = k_begin();
    int kEnd = k_end();

    debugOut << "D=" << D << " k=" << kBegin << " to " << kEnd << "\n";

    assert(D < INT_MAX); //TODO make this an error case?

    // For each diagonal k
    for (int k = kBegin; k <= kEnd; k+=2) {
      unsigned row, col;

      if ((k == -(int)D) || 
          (k != (int)D && V[k-1] < V[k+1]))
        col = V[k+1];
      else
        col = V[k-1] + 1;
      row = col - k;
      
      debugOut << "  x=" << col << " y=" << row << std::endl; 
      
      if (row > Orig.size() || col > New.size()) {
        debugOut << "  Outside Matrix col=" << col << " row=" <<row <<"\n";
        continue;
      }
      
      Position furthest =  snake(Position(col, row));
      debugOut << "  end=" << furthest << std::endl; 

      V[k] = furthest.x;

      if ((furthest.y == Orig.size()) && (furthest.x == New.size())){
        debugOut << "  Reached End";
        return true;
      }
    }
    return false;
  }

  /**
   * Checks if the forward algorithm has collided with the reverse algorithm.
   * If it has, return the point of the overlap, where the two sequences can be bisected
   * 
   * @param reverse IN the vector of furthest reaching paths in the reverse direction
   * @param bisect OUT the position where the overlap occurred.  
   */
  
  bool is_overlapped(Vector &forward, Position &bisect) {
    debugOut << " is_overlapped: \n"; 
    
    assert(dir==REVERSE);

    int32_t kBegin = k_begin();
    int32_t kEnd = k_end();

    //Only check the diagonals that have been walked in the other direction
    int32_t kb = max(size_delta - kEnd, kBegin);
    int32_t ke = min(size_delta - kBegin, kEnd);

    for (int k =  kb; k <= ke; k++) {
      int k_r = size_delta - k;

      //TODO add function (V,k) -> Position
      Position reversePos = Position(V[k], V[k] - k);
      Position forwardPos = Position(forward[k_r], forward[k_r] - k_r);
            
      reversePos = normalize(reversePos);

      debugOut << "  k=" << k << " forwardPos=" << forwardPos 
               << " reversePos=" << reversePos << std::endl;

      if (forwardPos.x >= reversePos.x){
        bisect = forwardPos;
        return true;
      }
    }
    return false;
  }
  
  MyersAlgorithm(_RandomAccessSequenceTy O, 
                 _RandomAccessSequenceTy N)
    :Orig(O), New(N), size_delta(New.size() - Orig.size()),
     D(0), V(Orig.size(), New.size())
  {
    if(dir==FORWARD) { debugOut<< "Forward: \n"; } else debugOut<< "Reverse: \n";
   
  }
  
  Vector & getV() {return V;}
  void incr_D() { ++D; }
};


template <typename _RandomAccessSequenceTy>
class Diff  { 
  typedef std::list<typename _RandomAccessSequenceTy::ElemTy> LCSList;

  //The Longest Common Subsequence for the two sequences
  LCSList _LCS;
  
  //Eat up common elements at the beginning of both sequences
  inline void eatPrefix(_RandomAccessSequenceTy &Orig, 
                        _RandomAccessSequenceTy &New, 
                        LCSList &prefix) {

    while ((Orig.size() != 0 && New.size() != 0) &&
           (*Orig.begin() == *New.begin())) {

      debugOut << "Added " <<  *Orig.begin() <<"\n";
      //Append the common element to the LCS
      prefix.push_back(New.pop_front());
      //Remove it from both sequences
      Orig.pop_front();
    
    }
  }

  //Eat up common elements at the end of both sequences
  inline void eatSuffix(_RandomAccessSequenceTy &Orig, 
                        _RandomAccessSequenceTy &New,
                        LCSList &suffix) {

    while ((Orig.size() != 0 && New.size() != 0) &&
           (*(Orig.end()-1) == *(New.end()-1))) {
  
      debugOut << "Added " << *(Orig.end()-1)<< "\n";
      //Append the common element to the LCS
      suffix.push_front(New.pop_back());
      //Remove it from both sequences
      Orig.pop_back();
  
    }
  }

  void do_diff(_RandomAccessSequenceTy Orig, 
               _RandomAccessSequenceTy New,
               LCSList &LCS) {

    debugOut << "do_diff Orig.size=" << Orig.size()
             << " New.size=" << New.size() << std::endl;
    
    dprintMatrix(Orig, New);
 
    LCSList prefix, suffix;
    //Eat up common elements at the beginning and end of the sequence
    eatPrefix(Orig, New, prefix);
    eatSuffix(Orig, New, suffix);
    
    //If the problem is trivial, solve it
    if (Orig.size() == 0 || New.size() == 0){
      //lcs is empty do nothing
    } 
    else if (Orig.size() == 1){
      if (New.contains(Orig[0]))
        LCS.push_front(Orig[0]);
    } 
    else if (New.size() == 1) { 
      if  (Orig.contains(New[0]))
        LCS.push_front(New[0]);

    //Otherwise find the bisection point, and compute the diff of the left and right part
    } else {
     _RandomAccessSequenceTy origLeft, origRight, newLeft, newRight;
      // Get the bisection point
      Position bisection = bisect(Orig, New);

      Orig.split(bisection.y, origLeft, origRight);
      New.split(bisection.x, newLeft, newRight);
    
      // Compute the diffs of the left and right part
      LCSList left, right;
      do_diff(origLeft, newLeft, left);
      do_diff(origRight, newRight, right);
      
      // Join the results
      LCS.splice(LCS.begin(), right);
      LCS.splice(LCS.begin(), left);

    }

    //Add the prefix and suffix back;
    if (!prefix.empty()) LCS.splice(LCS.begin(), prefix);
    if (!suffix.empty()) LCS.splice(LCS.end(), suffix);
  }

  Position bisect( _RandomAccessSequenceTy Orig, 
                   _RandomAccessSequenceTy New ) {
   
    MyersAlgorithm<FORWARD,_RandomAccessSequenceTy> forward(Orig, New);
    MyersAlgorithm<REVERSE,_RandomAccessSequenceTy> reverse(Orig, New);

    bool overlap = false;
    Position bisection;

    // D is the length of the Shortest Edit Script.
    // Search D-paths until the end of each string is reached
    while (!overlap) {

      forward.trace_D_path();
      reverse.trace_D_path();
      
      overlap = reverse.is_overlapped(forward.getV(), bisection);

      forward.incr_D(); reverse.incr_D();
    }

    return bisection;
  }

public:
  Diff(_RandomAccessSequenceTy Orig, 
       _RandomAccessSequenceTy New)
  {
    do_diff(Orig, New, _LCS);   
  }

  inline LCSList & LCS() {    
    return _LCS;
  }
};


template < typename RandomAccessIterator, 
           typename OutputIterator >
OutputIterator 
lcs (RandomAccessIterator begin1, RandomAccessIterator end1,
     RandomAccessIterator begin2, RandomAccessIterator end2,
     OutputIterator output){
  
  typedef RandomAccessSequence<RandomAccessIterator> RandAccSeqTy;

  RandAccSeqTy Orig(begin1, end1);
  RandAccSeqTy New(begin2, end2);
  
  
  Diff<RandAccSeqTy> Instance(Orig, New);
  
  return std::copy(Instance.LCS().begin(), Instance.LCS().end(), output);
}


#endif
