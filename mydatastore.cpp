#include "util.h"
#include <set>
#include <vector>
#include "mydatastore.h"
#include <utility>
#include <string>

using namespace std;


MyDataStore::MyDataStore(){

}

void MyDataStore::addProduct(Product* p){
	products.insert(p);//insert the product pointer into the products set
}

void MyDataStore::addUser(User* u){
	std::vector<Product*> tV;//Create an empty cart for the user
	//pair<User, std::vector<Product*>> tp(*u, tV);
	//string tS = u->getName();
	//std::string userName = u->getName();
	users.insert(make_pair(u->getName(), make_pair(*u, tV)));//insert the user value to the user set
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	
	std::vector<Product*> returnVec;//Return std::vector	
	std::set<std::string> searchedWords;//Create a std::set out of the terms (keywords in seach bar)

	std::set<Product*>::iterator sit;//Create an iterator to traverse products std::set
	std::vector<std::string>::iterator vit;//Create iterator for terms

	//Iterate through all items in terms
	for(vit = terms.begin(); vit != terms.end(); ++vit){
		searchedWords.insert(*vit);//Add all strings to the std::set of searched words
	}
	
	//Iterate through all products		
	for(sit = products.begin(); sit != products.end(); ++sit){

		if(type){//OR 

			//If the intersection of the searched words and the keywords of a product is not empty,
			//(any of those) words from the serach bar are in the key words of the item
			std::set<std::string> kwSet = (*sit)->keywords();
			std::set<std::string> tempSet = setIntersection(kwSet, searchedWords);

			
			if(!tempSet.empty()){
				returnVec.push_back(*sit);//Add product to returnVec
			}

		}else{//AND
			//Create a set containing words from the search and key words
			std::set<std::string> kwSet = (*sit)->keywords();
			std::set<std::string> tempSet = setIntersection(kwSet, searchedWords);

			//If tempSet is the same size as the original set, every word in the search bar is in 
			//the product's key words
			if(tempSet.size() == searchedWords.size()){
				returnVec.push_back(*sit);//Add the product to the return std::vector
			}
		}
	}

	return returnVec;
	/*	Alternate Alg. w/ n^3 runtime (uses setUnion)
	Create a set of products for each term (where the products' keywords contain the term)
	dynamically allocate mem for each set
	delete the sets when done
	Terms could be invalid key words - use parseStringToWords (which will return a set)
  Loop through terms and create sets including products that have keywords with those terms
  use intersection or union repeatedly for pairs of sets until there is one left
	*/
}

void MyDataStore::dump(std::ostream& ofile){
	//Print ALL products then ALL users

	//Go through all products and use dump() method
	for(set<Product*>::iterator sit = products.begin(); sit != products.end(); ++sit){
		(*sit)->dump(ofile);
	}

	//Go through all users and use dump() method
	for(std::map< std::string, std::pair<User, std::vector<Product*>> >::iterator mit = users.begin(); mit != users.end(); ++mit){
		//Access the vallue of the map ( a pair ). Access the first item of the pair (the User), use the dump members
		mit->second.first.dump(ofile);
	}
}

//buy cart functions

bool MyDataStore::containsUser(std::string username){//Is a user in the database
	
	if(users.find(username) != users.end()){
		return true;
	}
	
	return false;	
}

void MyDataStore::addToCart(std::string username, Product* p){
	//Add product to <username>'s cart

	//cart must be managed fifo & products can't be removed by user

	//push back, pop front (FIFO)
	//on std::vector of prodcucts (cart) associated with User's key in map
	//(thier username)

	//Access the value at the username key and add to the front of that std::vector
	//Access the pair at the username. Add to the 2nd item of the pair (the cart std::vector). Add to the end of that std::vector
	users[username].second.push_back(p);
}

void MyDataStore::printCart(std::string username){

	if(users[username].second.empty()){
		cout << "User's cart is empty\n";
		return;
	}
	//Iterate through every item in the users cart and print out its name
	int i = 1;

	for(std::vector<Product *>::iterator it = users[username].second.begin(); it != users[username].second.end(); ++it){
		std::cout << i << ": " << (*it)->getName() << std::endl;
		i++;
	}
}

void MyDataStore::buyCart(std::string username){

	if(users[username].second.empty()){
		cout << "User's cart is empty\n";
		return;
	}

	//Starting at the back of the std::vector of products (users cart), attempt to purchase items

	//If the items is in stock AND the user has enough money
		//1. reduce the items quantity
		//2. deduct the price from the users account balance
		//3. Remove the item from the cart

	int item = 0;//Tracks index of item to be bought in vector

	//Go to pair associated with username; access first item in pair (User); call getBalance() member
	unsigned int endCond = users[username].second.size();
	for(unsigned int i = 0; i < endCond; i++){//Visit each item of interest once (loop runs for the length of the vector)

		//Checking conditions
		if(users[username].second[item]->getPrice() > users[username].first.getBalance() ){
			cout << "Insufficient funds for \"" << users[username].second[item]->getName() << "\" \n";
			//Skip item
			item++;
		}else if(users[username].second[item]->getQty() == 0){
			cout << "Item \"" << users[username].second[item]->getName() << "\" is out of stock\n";			
			//Skip item
			item++;
		}//Since the  carts are 'FIFO' (but not really because you purchase all items in stock and that you can afford regardles of order),
		//if an item can't be purchased, leave the item in the cart and move on to the next item in the cart
		else {
			users[username].second[item]->subtractQty(1);//Reduce qty
			//DEBUG: cout << "Buying " << users[username].second[0]->getName() << ". New qty = " << users[username].second[0]->getQty() <<endl;

			users[username].first.deductAmount(users[username].second[item]->getPrice());//Debit user
			//DEBUG: cout <<  users[username].first.getName() << " now has " <<  users[username].first.getBalance() << " left.\n";
			
			users[username].second.erase(users[username].second.begin() + item);//remove item from cart
		}
	}
}