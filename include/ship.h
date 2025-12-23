#pragma once

#include <string>
#include "shipsystem.h"

namespace starship {

class Ship {
public:
    Ship(std::string n, int x, int y, bool hostile);
    ~Ship();

    bool IsAlive() const;

    void TakeDamage(double amount);

private:
  std::string name;
  std::pair<int, int> pos;
  ShipSystem stats;
  bool is_hostile;
};

}  // namespace starship
