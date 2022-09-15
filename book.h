#include <iostream>
#include <string>
#include "util.h"
#include "product.h"

class Book : protected Product{
	public:
		Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
		
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
	
	private://Add  derived class specific member variables
		std::string isbn_;
		std::string author_;
};