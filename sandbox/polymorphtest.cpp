#include <string>
#include <iostream>
#include <vector>
 
using std::cout;
using std::endl;

class A {
public:
  int a_thing;
  int a_wow;

  virtual void talk() {
    cout << "I'm A\n";
  }
};

class B : public A {
private:
  int b_thing;
public:
  virtual void talk() override {
    cout << "I'm B\n";
  }

};

int main() { 
  std::vector<A>* a_vector = new std::vector<A>(10);
  std::vector<B>* b_vector = new std::vector<B>(10);
  std::vector<A>* b2a_vector = (std::vector<A>*)b_vector;

  for (int i = 0; i < a_vector->size(); i++) {
    (*a_vector)[i].talk();
  }
  for (int i = 0; i < b_vector->size(); i++) {
    (*b_vector)[i].talk();
  }

  return 0;
}
