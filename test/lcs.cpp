#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "lcs.h"

const char* usage = "Usage:\n lcs <file> <file>\n";

using namespace std;

template < typename T >
void run_lcs(vector<T> &o, vector<T> &n) 
{
  clock_t start_time = clock();

  vector<T> LCS(n.size());
  typename vector<T>::iterator end = lcs(o.begin(), o.end(),
					 n.begin(), n.end(), 
					 LCS.begin());
  clock_t end_time = clock();
  
  LCS.resize(end-LCS.begin());

  cout << string(LCS.begin(), LCS.end());
  
  double cpu_time_secs = ((end_time - start_time)/(double)CLOCKS_PER_SEC)*1000;
  cerr << " Time spent = " << cpu_time_secs <<" ms\n";
}

vector<char> * read_ascii_file (string name)
{
  FILE * f = fopen (name.c_str(), "r");
  if (f == NULL) perror("fopen");
  int err = fseek(f, 0, SEEK_END) != 0;
  if (err) perror("fseek");
  int fSize=ftell(f);
  if (fSize < 0) perror("ftell");
  rewind(f);
  vector<char> *bufferp=new vector<char>;
  bufferp->resize(fSize);
  err = fread (&((*bufferp)[0]), 1, fSize, f);
 
  if (err < 0) perror ("fread");

  fclose (f);
  return bufferp;
}

int main(int argc, char* argv[]) {

  if (argc < 3){
    fprintf(stderr, "%s", usage);
    exit(-1);
  }

  vector<char> * lisp = read_ascii_file(argv[1]);
  vector<char> * lisp1 = read_ascii_file(argv[2]);
 
  run_lcs<char>(*lisp, *lisp1);
  delete lisp;
  delete lisp1;

  return 0;
}
