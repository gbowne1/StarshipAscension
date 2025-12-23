#include "ship.h"

namespace starship {

Ship::Ship(std::string n, int x, int y, bool hostile = true) 
  : name(n), pos({x, y}), is_hostile(hostile) {
  stats.health = 100.0;
  stats.shields = 50.0; // Enemies start with weaker shields
}

Ship::~Ship() {

}

bool Ship::IsAlive() const { return stats.health > 0; }

void Ship::TakeDamage(double amount) {
  if (stats.shields > 0) {
    stats.shields -= amount;
    if (stats.shields < 0) {
      stats.health += stats.shields; // Carry over damage to health
      stats.shields = 0;
    }
  } else {
    stats.health -= amount;
  }
}

}  // namespace starship
