#include <sstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <set>
#include "book.h"

using namespace std;

//Book child class constructor
Book::Book( const string category,
	const string name, 
	double price, 
	int qty, 
	string isbn, 
	string author)
	 :
	Product(category, name, price, qty),
	isbn_(isbn),
	author_(author)
{

}

set<string> Book::keywords() const{
	//Use the string parser to find all words in the title of the book and the author(s)
	set<string> fin;

	fin.insert(isbn_);//Add isbn to set of keywords
	
	set<string> temp = parseStringToWords(author_);

	set<string>::iterator it;//Create an iterator to traverse one of the sets
	
	//Add everything from the temp (author set) to the final set that holds all keywords
	for(it = temp.begin(); it != temp.end(); ++it){
			fin.insert(*it);
	}

	temp = parseStringToWords(name_);

	for(it = temp.begin(); it != temp.end(); ++it){
		fin.insert(*it);
	}

	return fin;
}

string Book::displayString() const{//Display product info? (title, author, ISBN, qty, and price?)
	//string fin = "Title: " + name_ + ", Author(s): " + author_ + ", ISBN: " + isbn_ + ", Quantity: "+ qty_ + ", Price: " +price_ + "\n"
	
	//Create a string stream
	stringstream ss;

	ss << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ << endl <<
	price_ << " " << qty_ << " left.\n";

	//Return the sstream as a string
	return (ss.str());
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl << isbn_ << endl << author_ << endl;
}