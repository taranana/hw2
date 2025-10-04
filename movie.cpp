#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product("movie",name,price,qty) , genre_(genre), rating_(rating) {};

std::set<std::string> Movie::keywords() const {
  std::set<std::string> keys = parseStringToWords(convToLower(name_));
  keys.insert(convToLower(genre_));
  return keys;
}

std::string Movie::displayString() const {
  std::ostringstream ss;
  ss << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Movie::dump(std::ostream& os) const {
  os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}