#include <string>
#include <iomanip>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::~MyDataStore() { 
    for(size_t i = 0; i < products_.size(); i++){
        delete products_[i];
    }
    for(set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        delete *it;
    }
    
    
}

       
void MyDataStore::addProduct(Product* p){
    products_.push_back(p);
}


void MyDataStore::addUser(User* u){
    users_.insert(u);
}

void MyDataStore::addCart(std::string username, Product* p){
    bool found = false;
    for(set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        if((*it)->getName().compare(username) == 0){
            User* u = *it;
            cart_[u].push_back(p);
            found = true;
        }
    }
    if(found == false){
        cout << "Invalid request" << endl;
    }
}
void MyDataStore::viewCart(std::vector<Product*> vect){
    int resultNo = 1;
    if (vect.begin() == vect.end()) {
    	cout << "No results found!" << endl;
    }
    for(vector<Product*>::iterator it = vect.begin(); it != vect.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    };
}




void MyDataStore::buyCart(std::string username){
    bool found = false;
    User* u;
    for(set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        if((*it)->getName().compare(username) == 0){
            u = *it;
            found = true;
        }
    }
    if(found == false){
        cout << "Invalid username" << endl;
    }
    else{
        for(size_t i = 0; i < cart_[u].size(); i++){
            if(cart_[u][i]->getQty() > 0){
                if(u->getBalance() >= cart_[u][i]->getPrice()){
                    u->deductAmount(cart_[u][i]->getPrice()); //deduct money by the product's price

                    cart_[u][i]->subtractQty(1); //substract quantity by 1

                    cart_[u].erase(cart_[u].begin()); //remove from the cart
                    i--;
                }
            }
        }
    }
}


std::vector<Product*> MyDataStore::getCart(std::string username){
    bool found = false;
    for(set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        if((*it)->getName().compare(username) == 0){
            User* u = *it;
            found = true;
            return cart_[u];
        }
    }
    if(found == false){
        cout << "Invalid username" << endl;
    }
    vector<Product*> empty;
    return empty;
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    // 0 = and 
    // 1 = or
    vector<Product*> searchVect;
    if(terms.size() == 0){
        return searchVect;
    }    
    map<string, set<Product*>> productMap;
    for(size_t i=0; i < products_.size(); i++){
        set<string> setOfKeywords = products_[i]->keywords();
        for(set<string>::iterator it = setOfKeywords.begin(); it != setOfKeywords.end(); ++it){
            productMap[*it].insert(products_[i]); 
        }
    }

    set<Product*> resultSet;
    if(terms.size() == 1){

        resultSet = productMap[terms[0]];
        for(set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it){
            searchVect.push_back(*it);
        }
        return searchVect;
    }
    if(type == 0){
        for(size_t i =0; i < terms.size()-1; i++){
            resultSet = setIntersection(productMap[terms[i]], productMap[terms[i+1]]);
        }
    }
    else if(type == 1){
        for(size_t i =0; i < terms.size(); i++){
         
            resultSet = setUnion(productMap[terms[i]], resultSet);
        }
    }
    

    for(set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it){
            searchVect.push_back(*it);
    }
    return searchVect;


}


void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << endl;
    for (size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;

    // write user information
    ofile << "<users>" << endl;
    for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;
}





