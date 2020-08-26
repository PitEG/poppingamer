#include <poppingamer/poppingamer.hpp> 
#include <vector>
#include <string>
#include <iostream>

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
    players->push_back(new pg::Entity(NULL));
    players->push_back(new pg::Entity(NULL,std::to_string(i)));
  }
  
  pg::ObjectPooler op;
  op.AddPool(*fires, std::string("fire"));
  op.AddPool(*projectiles, std::string("proejctiles"));
  op.AddPool(*players, std::string("players"));

  int gets = 100;
  for (int i = 0; i < gets; i++) {
    std::cout << op.GetEntity("fire")->Name() << std::endl;
  }
  
  delete fires;
  return 0;
}
