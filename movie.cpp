#include <sstream>
#include <iostream>
#include <algorithm>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : 
Product(category, name, price, qty), genre_(genre), rating_(rating) {

}
Movie::~Movie() {

}
std::set<std::string> Movie::keywords() const {
    std::set<std::string> keywords = parseStringToWords(name_);
    keywords.insert(convToLower(genre_));
    return keywords;
}

std::string Movie::displayString() const {
    std::stringstream ss;
    ss << name_ << std::endl;
    ss << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
    ss <<  price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    <<  "\n" << genre_ <<  "\n" << rating_ << std::endl;

}

std::string Movie::getGenre() const {
    return genre_;
}

std::string Movie::getRating() const {
    return rating_;
}