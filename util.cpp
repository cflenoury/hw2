#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
		//set the words to be all lower case
		std::string lowerWords = convToLower(rawWords);

		//Create a set of type string to return
    std::set<std::string> parsedWords;

		//Create a temp string to look at parsed strings
		std::string temp;

		//Past version of 'i'
		unsigned int pindx = 0;

		//Traverse the entire string, looking at each char
		for(unsigned int i = 0; i < lowerWords.length(); i++){

			//If the char is not lowercase letter
			if(lowerWords[i] < 96 && lowerWords[i] > 123 ){
			//if(isalpha(lowerWords[i])){

				//Create a subtring from the last pindx to char before the current index
				temp = lowerWords.substr(pindx, i - pindx);

				//Make pindx be the char after the current one
				pindx = i + 1;

				//If the size of the sub string is sufficient, add it to the return set
				if(temp.size() > 2 ){
					parsedWords.insert(temp);
				}
			}
		}

    return parsedWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
