#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"


class MyDataStore : public DataStore{
    public:
         ~MyDataStore();

        /**
         * Adds a product to the data store
         */
        void addProduct(Product* p);

        /**
         * Adds a user to the data store
         */
        void addUser(User* u);

        void addCart(std::string username, Product* p);
        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        std::vector<Product*> getCart(std::string username);
        void buyCart(std::string username);
        void viewCart(std::vector<Product*> vect);

        /**
         * Reproduce the database file from the current Products and User values
         */
        void dump(std::ostream& ofile);

    private:
    //first in first out, act like a queue
        std::vector<Product*> products_;
        std::set<User*> users_;
        std::map<User*, std::vector<Product*>> cart_;
};

#endif
