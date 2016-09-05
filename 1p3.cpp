#include <iostream>
using namespace std;
/*URLify: given a string with spaces, replace each space with %20
initial thoughts:
read through string - counting whitespace:
start at "true length" count spaces until end to find total length
total length / true length / 3 == number of spaces to replaces

starting at end, move each charachter 3*number of spcaes to replace back, until coming to a space
then insert %20 and decrease the number of spaces to replace by 1
*/
string urlify(string input, int trueLength)
{
  int totalLength = trueLength+1;
  while(input[totalLength] != 0)
  {
    totalLength++;
  }

  int spacesToReplace = (totalLength - trueLength) / 2;
  int offset = totalLength - trueLength;
  int newIndex = totalLength - 1;

  for(int i =0; i<totalLength; i++){
    cout<< input[i] << " : " << i << endl;
  }

  while(spacesToReplace > 0)
  {
    if(input[(newIndex - offset)] == ' '  ){
      input[newIndex] = '0';
      input[newIndex - 1] = '2';
      input[newIndex - 2] = '%';
      newIndex -= 3;
      spacesToReplace--;
      offset-=2;
    }
    else
    {
      input[newIndex] = input[newIndex - offset];
      newIndex--;
    }
  }

 return input;
}

int main()
{
 cout << urlify("John Smith  ", 10) << endl;

return 0;
}
