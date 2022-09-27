#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	//Create a set to return
	std::set<T> final;
	
	typename std::set<T>::iterator it;//Create an iterator to traverse one of the sets

	for(it = s1.begin(); it != s1.end(); ++it){//Traverse the set
		if( s2.find(*it) != s2.end()){//If the item in s1 is also in s2
			//Add it to the returning set
			final.insert(*it);
		}

	}

	return final;

}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

	//Alg: Add all the elements from one set to the other and return that set

	typename std::set<T>::iterator it;//Create an iterator to traverse one of the sets

	std::set<T> final;

	if( s1.size() > s2.size() ){
		//add everything in s2 to s1
		final = s1;
		for(it = s2.begin(); it != s2.end(); ++it){
			final.insert(*it);
		}
	}else{
		//add everything in s1 to s2
		final = s2;
		for(it = s1.begin(); it != s1.end(); ++it){
			final.insert(*it);
		}		
	}

	//return the vector that has everything
	return final;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
