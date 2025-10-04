#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <set>

using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {

  for(vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
    delete *it;
  }

  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    delete it->second;
  }

}

void MyDataStore::addProduct(Product* p) {
  products_.push_back(p);
}

void MyDataStore::addUser(User* u) {
  users_[convToLower(u->getName())] = u;
}

vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  set<Product*> searchResults;

  if(terms.empty()){
    return vector<Product*>();
  }

  string firstTerm = convToLower(terms[0]);
  set<Product*> firstSet;
  for(Product* p : products_) {
    set<string> keys = p->keywords();
    if(keys.find(firstTerm) != keys.end()) {
      firstSet.insert(p);
    }
  }

  searchResults = firstSet;

  for (int i = 1; i < (int)terms.size(); i++) {
    string term = convToLower(terms[i]);
    set<Product*> foundSet;

    for(Product* p : products_) {
      set<string> keys = p->keywords();
      if(keys.find(term) != keys.end()) {
        foundSet.insert(p);
      }
    }
    if(type == 0) {
      searchResults = setIntersection(searchResults, foundSet);
    }
    else {
      searchResults = setUnion(searchResults, foundSet);
    }

  }
  vector<Product*> results(searchResults.begin(), searchResults.end());

  return results;
  
}

void MyDataStore::addToCart(const std::string& username, Product* p) {
  string name = convToLower(username);
  if(users_.find(name) != users_.end()) {
    carts_[name].push_back(p);
  }
  else {
    cout << "Invalid request" << endl;
  }
}

void MyDataStore::viewCart(const std::string& username) const {
  string name = convToLower(username);
  if(carts_.find(name) == carts_.end()) {
    cout << "Invalid username" << endl;
    return;
  }

  const vector<Product*>& cart = carts_.at(name);
  for(int i =0; i < (int)cart.size(); i++) {
    cout << "Item " << i+1 << endl;
    cout << cart[i]->displayString() << endl;
  }
}

void MyDataStore::buyCart(const std::string& username) {
  string name = convToLower(username);
  if(carts_.find(name) == carts_.end()) {
    cout << "Invalid username" << endl;
    return;
  }

  vector<Product*>& cart = carts_[name];
  vector<Product*> cartRemainder;

  for(Product* p : cart) {
    User* u = users_[name];
    double bal = u->getBalance();
    double pr = p->getPrice();
    if(p->getQty() > 0 && bal >= pr) {
      u->deductAmount(pr);
      p->subtractQty(1);

    }
    else {
      cartRemainder.push_back(p);
    }
  }

  cart = cartRemainder;
}

void MyDataStore::dump(ostream& ofile) {
  ofile << "<products>" << endl;
  for(Product* p : products_) {
    p->dump(ofile);
  }
  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    it->second->dump(ofile);
  }
  ofile << "</users>" << endl;
}