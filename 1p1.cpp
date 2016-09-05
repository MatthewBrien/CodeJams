/*
Is Unique? Implement an alorithm to determine if a string has all unique charachters. what if you cannot use additional data strucuters?
Questions: Do upper and lower cases of the same letter count as repeated charachters?
Do spaces count?
*/
#include <iostream>
#include "myQuickSort.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using sorty::myQuickSort;

int main(){
/*-------Bute force solution-----------,
compare every char to every other char -
N + N-1  + N-2 ... 2 + 1 = Sum 0:N = N(N-1) / 2
O(N^2)
*/
  cout<<"Please enter a test string: ";
  string inputString;
  cin>>inputString;
  int i = 0;
  int j = 0;
  while ((int)inputString[i] != 0)
  {
    j=i+1;
    while((int)inputString[j] != 0)
    {
      if(inputString[i] == inputString[j]){
        cout<<"Repeat found: " << inputString[i] << " at " << i << " and " << j << endl;
        //return 0;
      }
      j++;
    }
    i++;
  }

/*
thoughts: Pigeon hole: supposed spaces can't repeat, and upper and lower case charachters do not counta against eachother
If we are using standard charachters, there are 256 charachters in the 8bit charachter set
if there are 257 or more charachters, we can gurantee that some charachters repeat

working with an additional data strucutre : a boolean array of length 256 could be used as a hashmap.
Each charachter converted to an integer could be used as an array index
O(N)
*/

cout<<"Now testing pigeon hole case " << endl;
int length = 0;
while((int)inputString[length] != 0){
  length++;
}
if(length > 256){
  cout<<"It's impossible to have no duplicates"<<endl;
}


bool charMap[256];
//initialize the boolean array
for(i=0; i<256; i++){
  charMap[i] = false;
}

i = 0;
do{
  if(!charMap[(int)inputString[i]])
  {
    charMap[(int)inputString[i]] = true;
  }
  else
  {
    cout<<"Repeat found: " << inputString[i] << " at " << i << endl;
    //return 0;
  }
  i++;
}while((int)inputString[i] != 0);


/*more throughts:
suppose charachters are of n-bits, or we don't want addition spaces
An algorithm could be implemented to find duplicates in place -
Sort the string, then comare neighbors
Best sequntial sort O(NlogN) + comparing neighbors is O(N);

*/
int numString[length];
for(int i = 0; i<length; i++)
{
  numString[i] = (int)inputString[i];
}
myQuickSort(numString, length);

for(int i =1; i < length; i++){
  if(numString[i] == numString[i-1])
  {
    cout<<(char)numString[i]<<" repeats " << endl;
  }
}


  return 1;
}
