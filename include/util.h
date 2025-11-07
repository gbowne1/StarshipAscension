#pragma once

#include <string>
#include <cstdint>  /* for uint32_t */

namespace starship {

class Util {
public:
  static std::string Sha256(const std::string& input);
};

}  // namespace starship


#pragma once

#include <string>
#include <cstdint>  /* for uint32_t */

namespace starship {

class Util {
public:
  static std::string Sha256(const std::string& input);
  static std::string getPasswordInput(char mask_char = '*');
};

}  // namespace starship