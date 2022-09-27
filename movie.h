#include <iostream>
#include <string>
#include "util.h"
#include "product.h"

class Movie : public Product{
	public:
		Movie(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
		
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
	
	private://Add  derived class specific member variables
		std::string genre_;
		std::string rating_;
};