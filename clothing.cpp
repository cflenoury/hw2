#include <sstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <set>
#include "clothing.h"

using namespace std;

//Book child class constructor
Clothing::Clothing( const string category,
	const string name, 
	double price, 
	int qty, 
	string size, 
	string brand)
	 :
	Product(category, name, price, qty),
	size_(size),
	brand_(brand)
{

}

set<string> Clothing::keywords() const{
	//Use the string parser to find all words in the title of the book and the author(s)
	set<string> fin;
	
	set<string> temp = parseStringToWords(brand_);

	set<string>::iterator it;//Create an iterator to traverse one of the sets
	
	//Add everything from the temp (brand set) to the final set that holds all keywords
	for(it = temp.begin(); it != temp.end(); ++it){
			fin.insert(*it);
	}

	temp = parseStringToWords(name_);//Add words in title to final set

	for(it = temp.begin(); it != temp.end(); ++it){
		fin.insert(*it);
	}

	return fin;
}

string Clothing::displayString() const{//Display product info? (title, author, ISBN, qty, and price?)
	//string fin = "Title: " + name_ + ", Author(s): " + author_ + ", ISBN: " + isbn_ + ", Quantity: "+ qty_ + ", Price: " +price_ + "\n"
	
	//Create a string stream
	stringstream ss;

	ss << name_ << "\nSize: " << size_ << " Brand: " << brand_ << endl << fixed << setprecision(2) <<
	price_ << " " << qty_ << " left.\n";

	//Return the sstream as a string
	return (ss.str());
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl << size_ << endl << brand_ << endl;
}