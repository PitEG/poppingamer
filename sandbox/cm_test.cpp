#include <poppingamer/poppingamer.hpp>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

class cTransform : public pg::Component {
private:
  int positionx;
  int positiony;
public:
  cTransform() : pg::Component(1) {
  }
  virtual void OnTick() override {
    cout << "cTransform\n"; 
  }

};

class FakeComponent : public pg::Component {
private:
  char a = 'a';

public:
  virtual void OnTick() override {
    cout << "FakeComponent\n";
  }
};

void copyConstructor(const pg::ComponentManager* src, pg::ComponentManager* target) {
  std::vector<cTransform>* copiedList = 
    new std::vector<cTransform>(src->CopyComponentList<cTransform>());
  auto list = src->CopyComponentList<cTransform>();
  target->AddComponents<cTransform>(list);
}

int main() {
  pg::ComponentManager cm;
  cTransform t;
  FakeComponent f;
  std::vector<cTransform> tL({t});
  cout << "Add() and Tick() tests\n";
  cm.AddComponents<cTransform>(tL);
  cm.AddComponents<cTransform>(tL);
  cm.Update<cTransform>(pg::UpdateType::Tick);

  cout << "copy constructor tests\n";
  pg::ComponentManager cm2(&cm, copyConstructor);
  cm2.Update<cTransform>(pg::UpdateType::Tick);

  return 0;
}
