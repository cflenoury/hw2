#include <sstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <set>
#include "movie.h"

using namespace std;

//Book child class constructor
Movie::Movie( const string category,
	const string name, 
	double price, 
	int qty, 
	string genre, 
	string rating)
	 :
	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating)	
{

}

set<string> Movie::keywords() const{
	//Use the string parser to find all words in the title of the book and the author(s)
	set<string> fin;

	fin.insert(genre_);//Add genre to set of keywords

	set<string>::iterator it;//Create an iterator to traverse one of the sets
	
	set<string> temp = parseStringToWords(name_);//Parse the words in the name of the book
	
	for(it = temp.begin(); it != temp.end(); ++it){//Add key words to final set
		fin.insert(*it);
	}

	return fin;
}

string Movie::displayString() const{//Display product info? (title, author, ISBN, qty, and price?)
	//string fin = "Title: " + name_ + ", Author(s): " + author_ + ", ISBN: " + isbn_ + ", Quantity: "+ qty_ + ", Price: " +price_ + "\n"
	
	//Create a string stream
	stringstream ss;

	ss << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << endl << fixed << setprecision(2) <<
	price_ << " " << qty_ << " left.\n";

	//Return the sstream as a string
	return (ss.str());
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl << genre_ << endl << rating_ << endl;
}