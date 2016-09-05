/*

Problem

After years of study, scientists at Google Labs have discovered an alien language transmitted from a faraway planet.
The alien language is very unique in that every word consists of exactly L lowercase letters.
Also, there are exactly D words in this language. Once the dictionary of all the words in the alien language was built,
the next breakthrough was to discover that the aliens have been transmitting messages to Earth for the past decade.
Unfortunately, these signals are weakened due to the distance between our two planets and some of the words may be misinterpreted.
In order to help them decipher these messages, the scientists have asked you to devise an algorithm that will determine the number of possible interpretations for a given pattern.
A pattern consists of exactly L tokens. Each token is either a single lowercase letter (the scientists are very sure that this is the letter) or a group of unique lowercase letters surrounded by parenthesis ( and ). For example: (ab)d(dc) means the first letter is either a or b, the second letter is definitely d and the last letter is either d or c. Therefore, the pattern (ab)d(dc) can stand for either one of these 4 possibilities: add, adc, bdd, bdc.

Input

The first line of input contains 3 integers, L, D and N separated by a space.
D lines follow, each containing one word of length L.
These are the words that are known to exist in the alien language.
N test cases then follow, each on its own line and each consisting of a pattern as described above.
You may assume that all known words provided are unique.

Output

For each test case, output
Case #X: K

where X is the test case number, starting from 1, and K indicates how many words in the alien language match the pattern.

Limits
Small dataset
1 ≤ L ≤ 10
1 ≤ D ≤ 25
1 ≤ N ≤ 10

Large dataset
1 ≤ L ≤ 15
1 ≤ D ≤ 5000
1 ≤ N ≤ 500

Sample
Input
3 5 4
abc
bca
dac
dbc
cba
(ab)(bc)(ca)
abc
(abc)(abc)(abc)
(zyx)bc

Output
Case #1: 2
Case #2: 1
Case #3: 3
Case #4: 0
*/
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct CharNode{
  bool leaf;
  map<char, CharNode> children;
};

void addWord(CharNode *start, string word){
  //cout << "Adding " << word << endl;
  if(word.length() == 0){
    start->leaf = true;
    //cout << "made " <<  start <<" node a leaf" << endl;
  }
  else
  {
    char currL = word[0];
      if(start->children.find(currL) == start->children.end()){
        CharNode *newNode = new CharNode;
        newNode->leaf = false;
        start->children[currL] = *newNode;
      }
      word.erase(0,1);
      addWord(&(start->children[currL]), word);
  }
}
bool checkWord(CharNode *start, string word){
  char currL = word[0];

  if(word.length() == 0 && start->leaf == true){
    return true;
  }
  if(start->children.find(currL) == start->children.end()){
    //cout << "this node " << &start << " isnt't a leaf" << endl;
    return false;
  }
  else{
    word.erase(0,1);
    return checkWord(&(start->children[currL]),word);
  }
}
int unscrambleHelper( CharNode *currentNode, vector <char> wordBlocks[], int blocksRemaining){
  int possibilities = 0;
  /*
  cout << "printing wordblock " << endl;
  for(int i = 0; i<blocksRemaining; i++){
    for(int ii = 0; ii<wordBlocks[i].size(); ii++){
      cout << wordBlocks[i][ii] << " ";
    }
    cout <<",";
  }*/
  //cout << endl;
  for(int i = 0; i<wordBlocks[0].size(); i++ ){


    if(blocksRemaining == 0 && currentNode->leaf == true){
    //  cout << "got to leaf with length " << blocksRemaining << endl;
      return 1;
    }
      if(currentNode->children.find(wordBlocks[0][i]) != currentNode->children.end()){
      //  cout << "going to next with " << wordBlocks[0][i] << " length "<<  blocksRemaining << endl;
        possibilities += unscrambleHelper(&(currentNode->children[wordBlocks[0][i]]), wordBlocks+1, blocksRemaining-1);
      }
  }
  //cout << "returning " << possibilities << " length is " << blocksRemaining << endl;
  return possibilities;
}
int unscramble(CharNode *start, string scrambledMessage, int wordLength)
{
  vector <char> wordBlocks[wordLength];
  int currentPosition = 0;
  for(int i =0; i< wordLength; i++){
    if(scrambledMessage[currentPosition] == '('){
      currentPosition++;
      while(scrambledMessage[currentPosition] != ')'){
        wordBlocks[i].push_back(scrambledMessage[currentPosition]);
        //cout << "pushing " <<scrambledMessage[currentPosition]<< " into " << i << endl;
        currentPosition++;
      }
    }
    else
    {
      wordBlocks[i].push_back(scrambledMessage[currentPosition]);
    //  cout << "pushing " <<scrambledMessage[currentPosition]<< " into " << i << endl;
    }
    currentPosition++;
  }
  return unscrambleHelper( start, wordBlocks, wordLength);
}


int main(){
  ifstream inputFile;
  inputFile.open(".\\inputFiles\\largeAliens.txt");
  fstream outputFile;
  outputFile.open(".\\outputFiles\\largeAliens.txt", ios::out);
  if(inputFile.is_open() && outputFile.is_open()){
    cout << "files opened" << endl;
    int wordLength;
    int vocabSize;
    int numCases;
    inputFile >> wordLength;
    inputFile >> vocabSize;
    inputFile >> numCases;

    CharNode *dictionary = new CharNode;
    dictionary->leaf = false;
    string word;
    getline(inputFile, word); //clear first line
    //add all words to the dictionary
    for(int i = 0; i < vocabSize; i++){
          getline(inputFile, word);
        addWord(dictionary, word);
          /*
          (checkWord(dictionary, word)) ? cout << "correct, " << word <<" is a word" << endl : cout << "d-oh, " << word <<" was flagged as not being a word" << endl;
          word = 'f' + word;
          (checkWord(dictionary, word)) ? cout << "d-oh " << word <<" was flagged as a word" << endl : cout << "correct, " << word <<" was flagged as not being a word" << endl;
          */
    }
    //get scrambled messages
    for(int i = 1; i <= numCases; i++ ){
      getline(inputFile, word);
      //cout << word << endl;
      int possibilities = unscramble(dictionary, word, wordLength);
      //cout << "----------------------------------------------------------"<< endl;
      cout << "Case #" << i << ": " << possibilities << endl;
      outputFile << "Case #" << i << ": " << possibilities << endl;
      //cout << "----------------------------------------------------------" << endl;
    }
  }
  else{
    cout << "files did not open " << endl;
    if(inputFile.is_open()){  inputFile.close();    }
    if(outputFile.is_open()){ outputFile.close();  }
    return 0;
  }


  inputFile.close();
  outputFile.close();
  return 0;
}
