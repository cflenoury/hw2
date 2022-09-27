#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};

void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{

	//Testing

	//1. Finding key words
	
	// set<string> test1 = parseStringToWords("Crew Men's Fitted Shirt");

	// for(set<string>::iterator sit = test1.begin(); sit != test1.end(); ++sit){
	// 	cout << *sit << endl;
	// }	

	//2. mydatastore (saving users, saving products)

	if(argc < 2) {
			cerr << "Please specify a database file" << endl;
			return 1;
	}

	/****************
		* Declare your derived DataStore object here replacing
		*  DataStore type to your derived type
		****************/
	//DataStore ds;
	MyDataStore ds;

	// Instantiate the individual section and product parsers we want
	ProductSectionParser* productSectionParser = new ProductSectionParser;
	productSectionParser->addProductParser(new ProductBookParser);
	productSectionParser->addProductParser(new ProductClothingParser);
	productSectionParser->addProductParser(new ProductMovieParser);
	UserSectionParser* userSectionParser = new UserSectionParser;

	// Instantiate the parser
	DBParser parser;
	parser.addSectionParser("products", productSectionParser);
	parser.addSectionParser("users", userSectionParser);

	// Now parse the database to populate the DataStore
	if( parser.parse(argv[1], ds) ) {
			cerr << "Error parsing!" << endl;
			return 1;
	}

	// if(ds.containsUser("adal")){
	// 	cout << "adal is in the database\n";
	// }

	//ds.dump(cout);

	// Checking products
	// for(std::set<Product*>::iterator sit = ds.products.begin(); sit != ds.products.end(); ++sit){
	// 	cout << (*sit)->getName() << ": ";//Print product name
  //   std::set<std::string> kw = (*sit)->keywords();//Create keywords set
	// 	for(set<string>::iterator sit1 = kw.begin(); sit1 != kw.end(); ++sit1){//Print keywords set
	// 	cout << *sit1 << endl;
	// 	}	
		
	// }

	//Testing search: AND & OR
	// std::vector<std::string> tV = {"men","and"};
	// std::vector<Product*> fHit = ds.search( tV,1 );
	// displayProducts(fHit);
	// cout << "Hits: ";
	// for(std::vector<Product*>::iterator vit = fHit.begin(); vit != fHit.end(); ++vit){

	// 	(*vit)->dump(cout);

	// }

	//cout << "How many hits?: " << fHit.size();


    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
						else if( cmd == "ADD"){
							string username;
							int hit_result_index;
							ss >> username >> hit_result_index;
							username = convToLower(username);
							if( !ds.containsUser(username) || hit_result_index < 0){
								cerr << "Invalid requeset\n";
								return 1;
							}
							ds.addToCart(username, hits[hit_result_index - 1]);							
						}else if( cmd == "VIEWCART"){
							string username;
							ss >> username;
							username = convToLower(username);
							if( !ds.containsUser(username)){
								cerr << "Invalid requeset\n";
								return 1;
							}
							ds.printCart(username);							
						}else if( cmd == "BUYCART"){
							string username;
							ss >> username;
							username = convToLower(username);
							if( !ds.containsUser(username)){
								cerr << "Invalid requeset\n";
								return 1;
							}
							ds.buyCart(username);							
						}
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
