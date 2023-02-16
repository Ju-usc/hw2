#include <sstream>
#include <iostream>
#include <algorithm>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : 
Product(category, name, price, qty), size_(size), brand_(brand) {

}
Clothing::~Clothing() {

}
std::set<std::string> Clothing::keywords() const {
    std::set<std::string> nameKeys = parseStringToWords(name_);
    std::set<std::string> brandKeys = parseStringToWords(brand_);
    std::set<std::string> keywords = setUnion(nameKeys, brandKeys);

    return keywords;
}

std::string Clothing::displayString() const {
    std::stringstream ss;
    ss << name_ << std::endl;
    ss << "Size: " << size_ << " Brand: " << brand_ << std::endl;
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    <<  "\n" << size_ <<  "\n" << brand_ << std::endl;

}

std::string Clothing::getSize() const {
    return size_;
}

std::string Clothing::getBrand() const {
    return brand_;
}