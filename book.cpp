#include <sstream>
#include <iostream>
#include <algorithm>
#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : 
Product(category, name, price, qty), isbn_(isbn), author_(author) {

}
Book::~Book() {

}
std::set<std::string> Book::keywords() const {
    std::set<std::string> nameKeys = parseStringToWords(name_);
    std::set<std::string> authorKeys = parseStringToWords(author_);
    std::set<std::string> keywords = setUnion(nameKeys, authorKeys);
    keywords.insert(convToLower(isbn_));

    return keywords;
}

std::string Book::displayString() const {
    std::stringstream ss;
    ss << name_ << std::endl;
    ss << "Author: " << author_ << " ISBN: " << isbn_ << std::endl;
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    <<  "\n" << isbn_ <<  "\n" << author_ << std::endl;

}

std::string Book::getIsbn() const {
    return isbn_;
}

std::string Book::getAuthor() const {
    return author_;
}