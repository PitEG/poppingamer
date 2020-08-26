#include <poppingamer/poppingamer.hpp> 
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

int main() {
  int fire_count = 30;
  int projectile_count = 24;
  int player_count = 2;
  std::vector<pg::Entity*>* fires = new std::vector<pg::Entity*>();
  for (int i = 0; i < fire_count; i++) {
    fires->push_back(new pg::Entity(NULL,std::to_string(i)));
  }
  std::vector<pg::Entity*>* projectiles = new std::vector<pg::Entity*>();
  for (int i = 0; i < projectile_count; i++) {
    projectiles->push_back(new pg::Entity(NULL,std::to_string(i)));
  }
  std::vector<pg::Entity*>* players = new std::vector<pg::Entity*>();
  for (int i = 0; i < player_count; i++) {
    players->push_back(new pg::Entity(NULL,std::to_string(i)));
  }
  
  pg::ObjectPooler op;
  op.AddPool(*fires, std::string("fire"));
  op.AddPool(*projectiles, std::string("projectiles"));
  op.AddPool(*players, std::string("player"));

  int gets = 100;
  std::cout << "getting fire" << std::endl;
  for (int i = 0; i < gets; i++) {
    std::cout << op.GetEntity("fire")->Name() << std::endl;
  }
  std::cout << "getting player" << std::endl;
  for (int i = 0; i < gets; i++) {
    std::cout << op.GetEntity("player")->Name() << std::endl;
  }
  std::cout << "getting projectiles" << std::endl;
  for (int i = 0; i < gets; i++) {
    std::cout << op.GetEntity("projectiles")->Name() << std::endl;
  }

  class A {};
  class B : public A {};

  std::cout << "testing typeid" << std::endl;
  std::cout << (typeid(A) == typeid(B)) << std::endl;
  A a;
  B b;
  A& bA = b;
  std::cout << (typeid(a) == typeid(bA)) << std::endl;
  
  delete fires;
  return 0;
}
