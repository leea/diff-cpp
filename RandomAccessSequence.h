#ifndef RANDOMACCESSSEQUENCE_H
#define RANDOMACCESSSEQUENCE_H

/** 
    A generic random access sequence type whose values are stored externally
 */
template < typename _RandomAccessInputIterator >
class RandomAccessSequence {
  _RandomAccessInputIterator _begin;
  _RandomAccessInputIterator _end;
  size_t _len;
public:
  typedef typename std::iterator_traits<_RandomAccessInputIterator>::value_type ElemTy;
  RandomAccessSequence() {}
  RandomAccessSequence(_RandomAccessInputIterator b,
                       _RandomAccessInputIterator e):
    _begin(b), _end(e), _len(e-b) {}
  ~RandomAccessSequence() {}
  inline _RandomAccessInputIterator begin() { return _begin; }
  inline _RandomAccessInputIterator end() { return _end; }
  inline ElemTy pop_front() { ElemTy tmp = *_begin; ++_begin; --_len; return tmp; }
  inline ElemTy pop_back() {  ElemTy tmp = *(_end-1); --_end; --_len;  return tmp; }
  inline size_t size() const { return _len; }
  inline ElemTy operator[] (size_t index) const {assert(index < _len); return *(_begin + index); }
  bool contains(ElemTy elem) {
    for (_RandomAccessInputIterator i = _begin; i < _end; ++i) if (*i == elem) return true;
    return false;
  }
  void split(size_t index, RandomAccessSequence &left, RandomAccessSequence &right) {
    left = RandomAccessSequence(_begin, _begin + index);
    right = RandomAccessSequence(_begin + index, _end);
  }
};
 
#endif
