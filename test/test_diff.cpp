#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "lcs.h"
//#include "Difference.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;

const char * usage = "Prints the difference between two strings\n %s: <string> <string>\n";
const bool longstr = true;

template < typename T >
bool test_case(vector<T> &o, vector<T> &n, vector<T> &ExpectedLCS, bool longstr=false) 
{
  cout << "========\n";
  if (longstr){
    cout << " A[0]..A["<< o.size() <<"] = "<< string(o.begin(), o.begin() + 10) << "..."
	 << string(o.end()-10, o.end()) <<"\n" 
	 << " B[0]..B["<< n.size() <<"] = " << string(n.begin(), n.begin()+ 10) << "..."
	 << string(n.end()-10, n.end()) <<"\n";
  } else {
    cout << " A = "<< string(o.begin(), o.end())
	 << " B = " << string(n.begin(), n.end()) << "\n";
  }

  clock_t start_time = clock();

  vector<T> LCS(n.size());
  typename vector<T>::iterator end = lcs(o.begin(), o.end(),
					 n.begin(), n.end(), 
					 LCS.begin());
  clock_t end_time = clock();
  
  LCS.resize(end-LCS.begin());

  if (longstr){
    cout << " LCS(A,B) = " <<  string(LCS.begin(), LCS.begin()+10) << "..."
	 << string(LCS.end()-10, LCS.end()) <<"\n";
    cout << " Length = " << LCS.end() - LCS.begin() << endl;
  } else {
    cout << " LCS(A,B) = " <<  string(LCS.begin(), LCS.end()) << "\n";
  }
  

  // Test calculating the LCS in both directions.  The LCS function is
  // a commutative function so the result should be the same.
  
  vector<T> LCSSwap(n.size());
  typename vector<T>::iterator endSwap = lcs(n.begin(), n.end(),
					     o.begin(), o.end(), 
					     LCSSwap.begin());
  LCSSwap.resize(endSwap-LCSSwap.begin());

  if (longstr) {
    cout << " LCS(B,A) = " <<  string(LCSSwap.begin(), LCSSwap.begin()+10) << "..."
	 << string(LCSSwap.end()-10, LCSSwap.end()) <<"\n"
         << " Length = " << LCSSwap.end() - LCSSwap.begin() << endl
	 << " Expected   " << string (ExpectedLCS.begin(), ExpectedLCS.begin()+10) << "..." 
	 << string(ExpectedLCS.end()-10, ExpectedLCS.end()) << endl
         << " Length = " << ExpectedLCS.end() - ExpectedLCS.begin() << endl;
  
  } else {
    cout << " LCS(B,A) = " <<  string(LCSSwap.begin(), LCSSwap.end()) << endl
	 << " Expected   " << string (ExpectedLCS.begin(), ExpectedLCS.end()) << endl;
  }
  double cpu_time_secs = ((end_time - start_time)/(double)CLOCKS_PER_SEC)*1000;
  cout << " Time spent = " << cpu_time_secs <<" ms\n";

  if ((LCS == ExpectedLCS) && (LCSSwap == ExpectedLCS)) {
    cout << "Passed!" << endl;
    return true;
  } else {
    cout << "FAIL!" << endl;
    exit(-1);
    return false;
  }
}

template < typename T >
bool test_length(vector<T> &o, vector<T> &n, vector<T> &ExpectedLCS, bool longstr=false) 
{
  cout << "========\n";
  if (longstr){
    cout << " A[0]..A["<< o.size() <<"] = "<< string(o.begin(), o.begin() + 10) << "..."
	 << string(o.end()-10, o.end()) <<"\n" 
	 << " B[0]..B["<< n.size() <<"] = " << string(n.begin(), n.begin()+ 10) << "..."
	 << string(n.end()-10, n.end()) <<"\n";
  } else {
    cout << " A = "<< string(o.begin(), o.end())
	 << " B = " << string(n.begin(), n.end()) << "\n";
  }

  clock_t start_time = clock();

  vector<T> LCS(n.size());
  typename vector<T>::iterator end = lcs(o.begin(), o.end(),
					 n.begin(), n.end(), 
					 LCS.begin());
  clock_t end_time = clock();
  
  LCS.resize(end-LCS.begin());

  if (longstr){
    cout << " LCS(A,B) = " <<  string(LCS.begin(), LCS.begin()+10) << "..."
	 << string(LCS.end()-10, LCS.end()) <<"\n";
    cout << " Length = " << LCS.end() - LCS.begin() << endl;
  } else {
    cout << " LCS(A,B) = " <<  string(LCS.begin(), LCS.end()) << "\n";
  }

  // Test calculating the LCS in both directions.  The LCS function is
  // a commutative function so the result should be the same.
  
  vector<T> LCSSwap(n.size());
  typename vector<T>::iterator endSwap = lcs(n.begin(), n.end(),
					     o.begin(), o.end(), 
					     LCSSwap.begin());
  LCSSwap.resize(endSwap-LCSSwap.begin());

  if (longstr) {
    cout << " LCS(B,A) = " <<  string(LCSSwap.begin(), LCSSwap.begin()+10) << "..."
	 << string(LCSSwap.end()-10, LCSSwap.end()) <<"\n"
         << " Length = " << LCSSwap.end() - LCSSwap.begin() << endl
	 << " Expected   " << string (ExpectedLCS.begin(), ExpectedLCS.begin()+10) << "..." 
	 << string(ExpectedLCS.end()-10, ExpectedLCS.end()) << endl
         << " Length = " << ExpectedLCS.end() - ExpectedLCS.begin() << endl;
  
  } else {
    cout << " LCS(B,A) = " <<  string(LCSSwap.begin(), LCSSwap.end()) << endl
	 << " Expected   " << string (ExpectedLCS.begin(), ExpectedLCS.end()) << endl;
  }
  double cpu_time_secs = ((end_time - start_time)/(double)CLOCKS_PER_SEC)*1000;
  cout << " Time spent = " << cpu_time_secs <<" ms\n";

  if ((LCS == ExpectedLCS) && (LCSSwap == ExpectedLCS)) {
    cout << "Passed!" << endl;
    return true;
  } else {
    cout << "FAIL!" << endl;
    exit(-1);
    return false;
  }
}

template < typename T >
bool test_speed(vector<T> &o, vector<T> &n, vector<T> &ExpectedLCS, bool longstr=false) 
{
  cout << "========\n";
  if (longstr){
    cout << " A[0]..A["<< o.size() <<"] = "<< string(o.begin(), o.begin() + 10) << "..."
	 << string(o.end()-10, o.end()) <<"\n" 
	 << " B[0]..B["<< n.size() <<"] = " << string(n.begin(), n.begin()+ 10) << "..."
	 << string(n.end()-10, n.end()) <<"\n";
  } else {
    cout << " A = "<< string(o.begin(), o.end())
	 << " B = " << string(n.begin(), n.end()) << "\n";
  }

  clock_t start_time = clock();

  vector<T> LCS(n.size());
  typename vector<T>::iterator end = lcs(o.begin(), o.end(),
					 n.begin(), n.end(), 
					 LCS.begin());
  clock_t end_time = clock();
  
  LCS.resize(end-LCS.begin());

  if (longstr){
    cout << " LCS(A,B) = " <<  string(LCS.begin(), LCS.begin()+10) << "..."
	 << string(LCS.end()-10, LCS.end()) <<"\n";
  } else {
    cout << " LCS(A,B) = " <<  string(LCS.begin(), LCS.end()) << "\n";
  }

  double cpu_time_secs = ((end_time - start_time)/(double)CLOCKS_PER_SEC)*1000;
  cout << " Time spent = " << cpu_time_secs <<" ms\n";

  return true;
}


bool test_case(string o, string n, string ExpectedLCS, bool longstr=false)
{
  vector<char> O(o.begin(), o.end());
  vector<char> N(n.begin(), n.end());
  vector<char> E(ExpectedLCS.begin(), ExpectedLCS.end());

  return test_case<char>(O,N,E, longstr);
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

int main(int argc, char *argv[])
{
  
  //Base cases - Empty LCS
  test_case("", "a", "");
  test_case("b", "a", "");
  test_case("ab", "cd", "");
  test_case("asdfghjk","qwertyiu","");

  //Base cases - Length 1 LCS
  test_case("a", "a", "a");
  test_case("ba", "a", "a");
  test_case("ab", "a", "a");
  test_case("bad", "a", "a");
  test_case("ba", "ac", "a");
  test_case("bad", "ac", "a");
  test_case("bad", "tac", "a");
  test_case("bad", "taca", "a");
  test_case("bab", "atacata", "a");
  test_case("bad", "atacat", "a");

  test_case("bad", "ad", "ad");
  test_case("bad", "ba", "ba");
  test_case("bad", "dba", "ba");
  test_case("read", "ea", "ea");
  test_case("bad", "bacad", "bad");

  test_case("34cd78w", "78z", "78");
  test_case("7890", "78a90", "7890");
  test_case("7890a", "7890", "7890");
  test_case("a7890", "7890", "7890");
  test_case("a7890b", "e7890", "7890");
  test_case("a7890b", "7890", "7890");
  test_case("a7890b", "c7890d", "7890"); 
  test_case("a7890b", "c78e90d", "7890");
  test_case("a123b345c678d", "e123f345g678h", "123345678");
  test_case("a78f90b", "c78e90d", "7890");
  test_case("aa78f90b", "c78e90d", "7890");
  test_case("a7890", "7890b", "7890");

  test_case("78907890", "78a90", "7890");
  test_case("78a90", "78907890", "7890");
  test_case("7890", "78a907890", "7890");
  test_case("7890", "7890a7890", "7890");
  test_case("XMJYAUZ", "MZJAWXU", "MJAU");

  test_case("x1234ab34cd78w", "y12345678z", "123478");

  const char * A = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
  const char * B = "123456789012345678901234567890a1234567890b1234567890123456789012c34567890123456789012345678901d231456789012345678901234567890123456789012345678901234567890";
  test_case(A,B,A,longstr);

  vector<char> * lisp = read_ascii_file("lisp.txt");
  vector<char> * lisp1 = read_ascii_file("lisp1.txt");
  vector<char> * lisp_lcs = read_ascii_file("lisp_lcs.txt");

  test_case<char>(*lisp, *lisp1, *lisp_lcs,longstr);

  vector<char> * sp1 = read_ascii_file("speedtest1.txt");
  vector<char> * sp2 = read_ascii_file("speedtest2.txt");
  vector<char> * WRONG_lcs = read_ascii_file("lisp_lcs.txt");

  test_speed<char>(*sp1, *sp2, *WRONG_lcs, longstr);

  exit(0);
}
int main_sp(){
  vector<char> * lisp = read_ascii_file("lisp.txt");
  vector<char> * lisp1 = read_ascii_file("lisp1.txt");
  vector<char> * lisp_lcs = read_ascii_file("lisp_lcs.txt");

  test_case<char>(*lisp, *lisp1, *lisp_lcs);

  return 0;
}
