#include <poppingamer/poppingamer.hpp>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

class cTransform : public pg::Component {
public:
  cTransform() : pg::Component(1) {
  }
  virtual void OnTick() override {
    cout << "cTransform\n"; 
  }

};

class FakeComponent : public pg::Component {
};

void copyConstructor(pg::ComponentManager* src, pg::ComponentManager* target) {
  std::vector<cTransform>* copiedList = 
    new std::vector<cTransform>(src->CopyComponentList<cTransform>());
  auto list = src->CopyComponentList<cTransform>();
  target->AddComponents<cTransform>(list);
}

int main() {
  pg::ComponentManager cm;
  cTransform t;
  std::vector<cTransform> tL({t});
  cout << "Add() and Tick() tests\n";
  cm.AddComponents<cTransform>(tL);
  cm.AddComponents<cTransform>(tL);
  cm.Tick<cTransform>();

  cout << "copy constructor tests\n";
  pg::ComponentManager cm2(&cm, copyConstructor);
  cm2.Tick<cTransform>();

  return 0;
}
