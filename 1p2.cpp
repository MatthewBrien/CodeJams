#include <iostream>
#include "myQuickSort.h"
using namespace std;
//TODO: write a strin sorter
//TODO: split redundant code into functions, not repeated lines
/*
permutations :  given two input strings determine if one is a permutations of the other

idea 1: sort both lists - then compare
O(NlogN + N)

idea 2: count number of each charchter in each string:
compare

Questions to ask: does upper and lower case count?
Do spaces count? if they do, and strings are of different lengths - then not a permutation


*/

int main()
{
  cout << "Comparing strings with method one" << endl;
  string one = "Hello, Wo rld!";
  string two = "World, Hello!";

  int length[2];

  length[0] = 0;
  while(one[length[0]] != 0)
  {
    cout<<one[length[0]];
    length[0]++;
  }
  cout<<endl;

  length[1] = 0;
  while(two[length[1]] != 0)
  {
    cout<<two[length[1]];
    length[1]++;
  }
  cout<<endl;

  //check if strings are the same length
  if(length[0]!=length[1]){
    cout<<"Strings are different length, cannont be permutations"<<endl;
  }
  else
  {
    cout<<"Strings are at least the same length"<<endl;
    //TODO: write string, char quick sort algorithm
    //myQuickSort(one, length);
    //myQuickSort(two, length);
  }


  cout << "Comparing strings with method two" << endl;
  //create two char arrays of length 256
  char charachterCount[2][256];
  for(int i =0; i<256; i++)
  {
      charachterCount[0][i] = 0;
      charachterCount[1][i] = 0;
  }
  for(int i =0; i < length[0]; i++)
  {
    charachterCount[0][(int)one[i]]++;
  }
  for(int i =0; i < length[1]; i++)
  {
    charachterCount[1][(int)two[i]]++;
  }
  for(int i = 0; i < 256; i++)
  {
    if(charachterCount[0][i] != charachterCount[1][i])
    {
      cout<<"Can't be a permutation, '" << (char)i << "' doesn't appear the same number of times" << endl;
    }
  }
}
