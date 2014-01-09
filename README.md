diff-cpp is a template library for computing the longest common subsequence.

# Usage

    template < typename RandomAccessIterator, typename OutputIterator >
    OutputIterator 
    lcs (RandomAccessIterator begin1, RandomAccessIterator end1,
    	 RandomAccessIterator begin2, RandomAccessIterator end2,
     	 OutputIterator output);


diff-cpp follows the calling convention similar to STL <algorithm>.
The two sequences must be accessible through a Random Access Iterator,
and the longest common subsequence is copied into the Output Iterator
output.  The return value is the iterator pointing past the last
element is returned.


# Example

    #include "lcs.h"

    template < typename T >
    void run_lcs(vector<T> &o, vector<T> &n) 
    {
        vector<T> LCS(n.size());
        typename vector<T>::iterator end = lcs(o.begin(), o.end(),
	                                       n.begin(), n.end(), 
                                               LCS.begin());
        LCS.resize(end-LCS.begin());
    }

# Algorithm 

diff-cpp implements the Longest Common Subsequence algorithm described
by Eugene Myers[1] with the divide and conquer linear space refinement
described by Hirshberg[2], and optimizations from Neil Fraser's
diff-patch-match library[3]. The final algorithm is highly performant -
with sequence lengths near 10,000 and SES length around 10%, this
algorithm typically finishes under 10ms my test system (1.8Ghz Core2
Duo).

[1] An O(ND) Difference Algorithm and Its Variations.  Eugene
Myers. Algorithmica 1986

[2] A Linear Space Algorithm for Computing Maximal Common
Subsequences. Dan S. Hirshberg. Communications of the ACM. 1975
Vol. 18 No. 6

[3] Google-diff-patch-match. https://code.google.com/p/google-diff-match-patch/