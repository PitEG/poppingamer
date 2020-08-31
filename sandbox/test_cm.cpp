#include <poppingamer/poppingamer.hpp> 

#include <string>
#include <iostream>
#include <filesystem>

using std::cout;
using std::endl;
struct Position {
  float x = 0;
  float y = 0;

  Position(float x = 0, float y = 0) : x(x), y(y) {}
};

struct Health {
  unsigned int current = 10;
  unsigned int max = 10;
};

int main(int argc, const char* argv[]) {
  //file pat
  std::cout << std::filesystem::canonical("/proc/self/exe") << std::endl;

  pg::ComponentManager<Position> positions;
  pg::ComponentManager<Health> healths;
  pg::ComponentManager<pg::Sprite> sprites;

  pg::Entity e0(0, "entity 0");
  pg::Entity e1(1, "entity 1");
  pg::Entity e2(2, "entity 2");

  Position p1(1.f, 1.f);
  Position p2(2.f, 2.f);

  /*
  cout << "creating p0: " << positions.Create(e0) << endl;
  cout << "creating p1: " << positions.Create(e1, p1) << endl;
  cout << "creating p2: " << positions.Create(e2, p2) << endl;
  cout << "creating p2 (again): " << positions.Create(e2, p2) << endl;
  */

  auto pos_components = positions.GetComponents();
  //cout << "components: " << pos_components.size() << endl;
  for (int i = 0; i < pos_components.size(); i++) {
    auto& c = pos_components[i];
    unsigned int eId = c.entityId;
  }

  //disable a component
  

  //Position System, just move things to the left
  {
    cout << "MOVED TO THE LEFT!\n";
    //passed positions
    auto pos_components = positions.GetComponents();
    for (int i = 0; i < pos_components.size(); i++) {
      auto& c = pos_components[i];
      c.component.x += 1;

      unsigned int eId = c.entityId;
    }
  }

  return 0;
}
