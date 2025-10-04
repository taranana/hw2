#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) : Product("clothing",name,price,qty) , size_(size), brand_(brand) {};

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> keys = parseStringToWords(convToLower(name_));
  std::set<std::string> brandKeys = parseStringToWords(convToLower(brand_));
  keys = setUnion(keys, brandKeys);
  keys.insert(convToLower(size_));
  return keys;
}

std::string Clothing::displayString() const {
  std::ostringstream ss;
  ss << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Clothing::dump(std::ostream& os) const {
  os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}