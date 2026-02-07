#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <chrono>
#include <thread>
#include <atomic>
#include <random>
#include <array>
#include <numeric>
#include <regex>
#include <mutex>
#include <set>
#include <utility>
#include <locale>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cstdio>  /* for getchar */
#include <cctype>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <glog/logging.h>
#include <functional>


namespace starship {

class Game {
public:
  Game();
  ~Game();

  void Run();

  std::string GetVersion() const;

  void SetColorEnabled(bool enabled);

private:
  enum class State {
    TITLE,
    LOGIN,
    MAIN_MENU,
    PLAYING,
    SETTINGS,
    HELP,
    CAPTAINS_LOG,
    EXIT
  };

  enum class MenuOption {
    NEW_GAME,
    RESUME,
    LOAD,
    SAVE,
    SETTINGS,
    HELP,
    CAPTAINS_LOG,
    QUIT
  };

  struct ShipSystem {
    double health = 100.0;
    double shields = 100.0;
    double engines = 100.0;
    double weapons = 100.0;
  };

  std::string version_ = "0.0.1";
  std::string player_name_;
  int score_ = 0;
  ShipSystem systems_;
  std::pair<int, int> position_ = {0, 0};
  std::vector<std::pair<int, int>> enemies_;
  std::vector<std::pair<int, int>> friends_;
  std::vector<std::pair<int, int>> planets_;
  std::vector<std::pair<int, int>> starbases_;
  std::vector<std::string> captains_log_;
  State current_state_ = State::TITLE;
  bool color_enabled_ = true;
  bool sound_enabled_ = true;
  int term_width_ = 80;
  int term_height_ = 25;
  std::map<std::string, std::string> config_;
  std::mt19937 rng_;
  std::mutex log_mutex_;

  void Initialize();

  void LoadConfig();

  void SaveConfig();

  void ShowTitle();

  void Login();

  bool RegisterUser(const std::string& username, const std::string& password);

  bool VerifyUser(const std::string& username, const std::string& password);

  void MainMenu();

  void NewGame();

  void Resume();

  void LoadGame();

  void SaveGame();

  void Settings();

  void Help();

  void CaptainsLog();

  void PlayGame();

  void Navigate();

  void ScanLongRange();

  void ScanShortRange();

  void FireWeapons();

  void RaiseShields();

  void LogEntry(const std::string& entry);

  void ShowProgressBar(
  const std::vector<std::pair<std::string, std::function<void()>>>& tasks
  );


  void ClearScreen();

  void SetColor(const std::string& color);

  void ResetColor();

  void InverseText(bool enable);

  void FlashingText(bool enable);

  char GetKey();

  int GetMenuChoice(const std::vector<std::string>& options);

  void DetectTerminalSize();

  void CreateDataDir();

  std::string GetTimeStamp();

  void Beep();

  void EnemyTurn();

  /* Getters/Setters */
  double GetHealth() const { return systems_.health; }
  void SetHealth(double h) { systems_.health = h; }
  /* Similar for others... */

  /* Serialize */
  void Serialize(std::ofstream& ofs) const;

  void Deserialize(std::ifstream& ifs);

  /* TODO: Add more features */
};

}  // namespace starship
