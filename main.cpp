#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

//Function declarations
bool open_file(ifstream &inFile);
string trim(string &);
void split(const string& s, char delim, vector<string> &tokens);
bool buildMap(map<string, set<int>> &wordMap);
void writeIndex(map<string, set<int>>);
 
//Begin Main
int main()
{
    map <string, set<int>> wordMap;
   
    if (buildMap(wordMap))
    {
        cout << "The map has " << wordMap.size() << " elements." << endl;
        writeIndex(wordMap);      
    }
}
//End Main

// openFile Function
bool open_file(ifstream &inFile)
{
    bool success;

    inFile.open("testFile.txt");

    if(!inFile)
    {
        cout << "Unable to open text file" << endl;
        success; // Default declartion is false
    }
    else
    {
        success = true; // true when file is opened
    }
  
  return success;
}
// End openFile function

// trim function 
string trim(string &str)
{
    // Check the front of the word if any punctuation remove until we see letters
    while ( ! ((str[0] >= 65 && str[0] <= 90) || (str[0] >= 97 && str[0] <= 122)) )
    {
        str.erase(0);
    }
   // Check the end of the word if any punctuation remove until we get to LAST letter of string
    while ( ! ((str[str.length()-1] >= 65 && str[str.length()-1] <= 90) ||
             (str[str.length()-1] >= 97 && str[str.length()-1] <= 122)))
    {
        str.erase(str.length()-1);
    }
   
    return str;
}
//End trim 

// split function
void split(const string& s, char delim, vector<string> &tokens)
{
    ifstream inFile;

    bool status = open_file(inFile);

    int tokenStart = 0; //Starting position of the next token

    int delimPosition = s.find(delim); //Find first occurrence of the delimeter.

    if(status)
    {
        while(delimPosition != string::npos)
        {
            //Extract the token
            string tok = s.substr(tokenStart, delimPosition - tokenStart);

            //Push the token onto the tokens vector
            tokens.push_back(tok);

            //Trimming off any punctuations
            tok = trim(tok);

            //Move delimPosition to next character position
            delimPosition++;

            //Move tokenStart to delimPosition
            tokenStart = delimPosition;

            //Find next occurance of dthe delimiter
            delimPosition = s.find(delim, delimPosition);

            //If no more delimeters extract the last token
            if(delimPosition == string::npos)
            {
                //Extract the token
                string tok = s.substr(tokenStart, delimPosition - tokenStart);

                //Push the token onto the vector
                tokens.push_back(tok);
            }
        }
    }
}
//End split function

// buildMap function 
bool buildMap(map<string, set<int>> &wordMap)
{
    ifstream inputFile; // The input file
    string line; // To hold a line from the file
    int lineCount = 0; // To hold the line numbers
    vector<string> tokens; // To hold tokens
   
    // Open the file.
    bool status = open_file(inputFile);
    // If the file was successfully opened...
    if (status)
    {
        // Get the first line from the file.
        getline(inputFile, line);
        // While we're not at the end of the file...
        // CSE 111 – Introduction to Computer Science II
       
        while (inputFile)
        {
            // Update the line counter.
            lineCount++;
           
            // Clear previous tokens.
            tokens.clear();
           
            // Split the line into tokens.
            split(line, ' ', tokens); // "She sells sea shells" -> ["She", "sells", "sea", "shells"]
           
            // Create elements from the tokens.
            for (auto element : tokens)
            {
                // Create an empty set.
                set<int> mySet;
               
                // Emplace the new element.
                wordMap.emplace(element, mySet); // checks to see if element exists already
               
                // Add the current line number to the element's set.
                wordMap[element].insert(lineCount); // wordMap[element] = wordMap["She"]                                     
            }
            // Get the next line from the file.
            getline(inputFile, line);
        }
        // Close the input file.
        inputFile.close();
    }
    return status;
}
//End buildMap

// writeIndex function
void writeIndex(map<string, set<int>> wordMap)
{
    ofstream outFile;

    outFile.open("results.txt");

    //setting iterators
    map<string, set<int>>::iterator mapIter;
    set<int>:: iterator setIter;
    
    for (mapIter = wordMap.begin(); mapIter != wordMap.end(); mapIter++)
    {
        cout << mapIter->first << " : "; //sea :
        outFile << mapIter->first << " : ";

        for(setIter = mapIter->second.begin(); setIter != mapIter->second.end(); setIter++)
        {
           cout << *setIter << " "; //  1 2 4
           outFile << *setIter << " ";
         }
      
      cout << endl;
      outFile << endl;
    }
}
// End writeIndex