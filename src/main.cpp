#include <iostream>
#include <string>
#include <cstdlib>  /* for getenv */
#include <glog/logging.h>  /* google log */
#include "game.h"

int main(int argc, char* argv[]) {
  /* Initialize glog */
  google::InitGoogleLogging(argv[0]);

  starship::Game game;

  /* Command line flags */
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--version") {
      std::cout << "StarshipAscension v" << game.GetVersion() << std::endl;
      return 0;
    } else if (arg == "--help") {
      std::cout << "Usage: StarshipAscension [--version] [--help] [--no-color]" << std::endl;
      return 0;
    } else if (arg == "--no-color") {
      game.SetColorEnabled(false);
    }
  }

  game.Run();

  return 0;
}
