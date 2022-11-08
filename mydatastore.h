#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <vector>
#include <map>
#include "user.h"
#include "product.h"
#include "datastore.h"
#include <utility>

class MyDataStore : public DataStore {
	public:
		MyDataStore();//Constructor
		~MyDataStore();//Destructor
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		void addToCart(std::string username, Product* p);
		bool containsUser(std::string username);
		void printCart(std::string username);
		void buyCart(std::string username);

	private:
		//Member variables
		std::set<Product*> products;//A set to store all the products

		//Map users to carts 
		//Create carts (store products) ~ maybe vectors
		//Initialize carts to be empty product vectors

		//Map takes usernames as keys and values are pairs of Users and thier Carts
		std::map<std::string, std::pair<User, std::vector<Product*>> > users;		
};