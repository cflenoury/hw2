#include <iostream>
#include <string>
#include "util.h"
#include "product.h"

class Clothing : protected Product{
	public:
		Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
		
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
	
	private://Add  derived class specific member variables
		std::string size_;
		std::string brand_;
};