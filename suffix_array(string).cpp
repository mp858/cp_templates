// C++ program for building suffix array of a given text
// T.C= O(n(logn)^2) n=> text length
#include<bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
// Structure to store information of a suffix
struct suffix
{
	int index; // To store original index
	int rank[2]; // To store ranks and next rank pair
};

// A comparison function used by sort() to compare two suffixes
// Compares two pairs, returns 1 if first pair is smaller
int cmp(struct suffix a, struct suffix b)
{
	return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
			(a.rank[0] < b.rank[0] ?1: 0);
}

// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
vector<int> buildSuffixArray(string &txt, int n)
{
	// A structure to store suffixes and their indexes
	struct suffix suffixes[n];

	// Store suffixes and their indexes in an array of structures.
	// The structure is needed to sort the suffixes alphabetically
	// and maintain their old indexes while sorting
	for (int i = 0; i < n; i++)
	{
		suffixes[i].index = i;
		suffixes[i].rank[0] = txt[i] - 'a';
		suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
	}

	// Sort the suffixes using the comparison function
	// defined above.
	sort(suffixes, suffixes+n, cmp);

	// At this point, all suffixes are sorted according to first
	// 2 characters. Let us sort suffixes according to first 4
	// characters, then first 8 and so on
	int ind[n]; // This array is needed to get the index in suffixes[]
				// from original index. This mapping is needed to get
				// next suffix.
	for (int k = 4; k < 2*n; k = k*2)
	{
		// Assigning rank and index values to first suffix
		int rank = 0;
		int prev_rank = suffixes[0].rank[0];
		suffixes[0].rank[0] = rank;
		ind[suffixes[0].index] = 0;

		// Assigning rank to suffixes
		for (int i = 1; i < n; i++)
		{
			// If first rank and next ranks are same as that of previous
			// suffix in array, assign the same new rank to this suffix
			if (suffixes[i].rank[0] == prev_rank &&
					suffixes[i].rank[1] == suffixes[i-1].rank[1])
			{
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = rank;
			}
			else // Otherwise increment rank and assign
			{
				prev_rank = suffixes[i].rank[0];
				suffixes[i].rank[0] = ++rank;
			}
			ind[suffixes[i].index] = i;
		}

		// Assign next rank to every suffix
		for (int i = 0; i < n; i++)
		{
			int nextindex = suffixes[i].index + k/2;
			suffixes[i].rank[1] = (nextindex < n)?
								suffixes[ind[nextindex]].rank[0]: -1;
		}

		// Sort the suffixes according to first k characters
		sort(suffixes, suffixes+n, cmp);
	}

	// Store indexes of all sorted suffixes in the suffix array
	vector<int> suffixArr(n);
	for (int i = 0; i < n; i++)
		suffixArr[i] = suffixes[i].index;

	// Return the suffix array
	return suffixArr;
}

/* To construct and return LCP 
T.C for building LCP =O(n)
lcp[i]-> reprents  length of the longest common prefix 
         of the suffixes indexed by suffix[i] and suffix[i+1].
		suffix[n-1] is not defined as there is no suffix after it.
		hence lcp[suffix[n-1]]=0;
		e.g if lcp[i]=3=> means there is 3 length  common prefix 
		of suffix of s starting from suffixAtt[i] and suffix of s starting from suffixArr[i+1].
		means there can be 3 duplicate substring of s generated from theses suffixes
		total number of duplicate substrings= sum lcp[i] for all i->[0,n-1].
*/
vector<int> kasai(string &orgnlString, vector<int> &suffixVector) { 
   int n = suffixVector.size();
   // To store lcp array 
   vector<int> longPrefix(n, 0);  
   // To store inverse of suffix array elements
   vector<int> suffixInverse(n, 0); 
   // to fill values in suffixInverse[] array
   for (int i=0; i < n; i++)
      suffixInverse[suffixVector[i]] = i;     
   int k = 0;
   for (int i=0; i<n; i++) {    
      if (suffixInverse[i] == n-1) {    
         k = 0;
         continue;
      }
      int j = suffixVector[suffixInverse[i]+1];
      while (i+k<n && j+k<n && orgnlString[i+k]==orgnlString[j+k]) 
         k++;
      longPrefix[suffixInverse[i]] = k;   
      if (k>0)
         k--;  
   }
   return longPrefix; 
}
// A utility function to print an array of given size
void printArr(vector<int>&arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// Driver program to test above functions
int main()
{
	string txt= "banana";
	int n = txt.length();
	vector<int> suffixArr = buildSuffixArray(txt, n);
	cout << "Following is suffix array for " << txt << endl;
	printArr(suffixArr, n);
	return 0;
}
