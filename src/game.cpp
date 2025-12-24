#include "game.h"
#include "util.h"
#include <iostream>
#include <termios.h>
#include <unistd.h> // Required for STDIN_FILENO

namespace starship
{

  constexpr double PI = 3.14159265358979323846;

#define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 200809L
  /* #define _WIN32 */ /* If for Windows */
  /* #define _WIN64 */
  /* #define _GNU_SOURCE */
  /* #define _CRT_SECURE_NO_WARNINGS */

  void setStdinEcho(bool enable = true)
  {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (enable)
    {
      tty.c_lflag |= ECHO;
    }
    else
    {
      tty.c_lflag &= ~ECHO;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
  }

  Game::Game() : rng_(std::random_device{}())
  {
    Initialize();
  }

  Game::~Game()
  {
    SaveConfig();
  }

  void Game::Run()
  {
    DetectTerminalSize();
    if (term_width_ < 80 || term_height_ < 25)
    {
      std::cerr << "Terminal too small. Minimum 80x25 required." << std::endl;
      return;
    }

    CreateDataDir();

    LoadConfig();

    while (true)
    {
      switch (current_state_)
      {
      case State::TITLE:
        ShowTitle();
        current_state_ = State::LOGIN;
        break;
      case State::LOGIN:
        Login();
        break;
      case State::MAIN_MENU:
        MainMenu();
        break;
      case State::PLAYING:
        PlayGame();
        break;
      case State::SETTINGS:
        Settings();
        break;
      case State::HELP:
        Help();
        break;
      case State::CAPTAINS_LOG:
        CaptainsLog();
        break;
      }
    }
  }

  std::string Game::GetVersion() const
  {
    return version_;
  }

  void Game::SetColorEnabled(bool enabled)
  {
    color_enabled_ = enabled;
  }

  void Game::Initialize()
  {
    /* Initial game setup */
    enemies_ = {{10, 10}, {20, 20}};
    friends_ = {{5, 5}};
    planets_ = {{15, 15}};
    starbases_ = {{25, 25}};
    LogEntry("Game initialized.");
  }

  void Game::LoadConfig()
  {
    std::ifstream ifs("data/config.cfg");
    if (!ifs)
    {
      /* Default config */
      config_["color"] = "true";
      config_["sound"] = "true";
      return;
    }

    std::string line;
    while (std::getline(ifs, line))
    {
      if (line.empty() || line[0] == ';')
        continue;
      std::size_t eq = line.find('=');
      if (eq != std::string::npos)
      {
        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        config_[key] = val;
      }
    }
    color_enabled_ = (config_["color"] == "true");
    sound_enabled_ = (config_["sound"] == "true");
    ifs.close();
  }

  void Game::SaveConfig()
  {
    std::ofstream ofs("data/config.cfg");
    if (!ofs)
      return;

    config_["color"] = color_enabled_ ? "true" : "false";
    config_["sound"] = sound_enabled_ ? "true" : "false";

    for (const auto &kv : config_)
    {
      ofs << kv.first << "=" << kv.second << std::endl;
    }
    ofs.close();
  }

  void Game::ShowTitle()
  {
    ClearScreen();
    SetColor("yellow");
    std::cout << std::setw(term_width_ / 2) << std::left << "StarshipAscension v" << version_ << std::endl;
    std::cout << std::setw(term_width_ / 2) << std::left << "Copyright 2025" << std::endl;
    ResetColor();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    ClearScreen();
  }

  void Game::Login()
  {
    ClearScreen();
    std::string choice;
    std::cout << "1. Login\n2. Register\nChoice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string username, password;
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    setStdinEcho(false); // Disable echoing
    std::getline(std::cin, password);
    setStdinEcho(true); // Re-enable echoing

    if (choice == "1")
    {
      if (VerifyUser(username, password))
      {
        player_name_ = username;
        current_state_ = State::MAIN_MENU;
        LogEntry("User logged in: " + username);
      }
      else
      {
        SetColor("red");
        std::cout << "Invalid credentials.\n";
        ResetColor();
        Beep();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Login();
      }
    }
    else if (choice == "2")
    {
      if (RegisterUser(username, password))
      {
        player_name_ = username;
        current_state_ = State::MAIN_MENU;
        LogEntry("User registered: " + username);
      }
      else
      {
        SetColor("red");
        std::cout << "Registration failed.\n";
        ResetColor();
        Login();
      }
    }
    else
    {
      Login();
    }
  }

  bool Game::RegisterUser(const std::string &username, const std::string &password)
  {
    std::filesystem::path user_path = "data/users/" + username + ".dat";
    if (std::filesystem::exists(user_path))
      return false;

    std::filesystem::create_directory("data/users");

    std::ofstream ofs(user_path, std::ios::binary);
    if (!ofs)
      return false;

    std::string hashed = Util::Sha256(password);
    ofs << hashed;
    ofs.close();

    std::filesystem::permissions(user_path, std::filesystem::perms::owner_read | std::filesystem::perms::owner_write);

    return true;
  }

  bool Game::VerifyUser(const std::string &username, const std::string &password)
  {
    std::filesystem::path user_path = "data/users/" + username + ".dat";
    if (!std::filesystem::exists(user_path))
      return false;

    std::ifstream ifs(user_path, std::ios::binary);
    if (!ifs)
      return false;

    std::string stored_hash;
    ifs >> stored_hash;
    ifs.close();

    return (Util::Sha256(password) == stored_hash);
  }

  void Game::MainMenu()
  {
    ClearScreen();
    std::vector<std::string> options = {
        "New Game",
        "Resume Game",
        "Load Game",
        "Save Game",
        "Settings",
        "Help",
        "Captain's Log",
        "Quit"};

    int choice = GetMenuChoice(options);

    switch (choice)
    {
    case 0:
      NewGame();
      break;
    case 1:
      Resume();
      break;
    case 2:
      LoadGame();
      break;
    case 3:
      SaveGame();
      break;
    case 4:
      current_state_ = State::SETTINGS;
      break;
    case 5:
      current_state_ = State::HELP;
      break;
    case 6:
      current_state_ = State::CAPTAINS_LOG;
      break;
    case 7:
      std::exit(0);
      break;
    }
  }

  void Game::NewGame()
  {
    ClearScreen();
    std::cout << "Starting a new game" << std::endl;
    ShowProgressBar("Loading", 2000);
    Initialize();
    current_state_ = State::PLAYING;
  }

  void Game::Resume()
  {
    current_state_ = State::PLAYING;
  }

  void Game::LoadGame()
  {
    std::ifstream ifs("data/save.dat", std::ios::binary);
    if (!ifs)
    {
      SetColor("red");
      std::cout << "No save file." << std::endl;
      ResetColor();
      return;
    }
    Deserialize(ifs);
    ifs.close();
    current_state_ = State::PLAYING;
    LogEntry("Game loaded.");
  }

  void Game::SaveGame()
  {
    std::ofstream ofs("data/save.dat", std::ios::binary);
    if (!ofs)
      return;
    Serialize(ofs);
    ofs.close();
    LogEntry("Game saved.");
  }

  void Game::Settings()
  {
    ClearScreen();
    std::cout << "Settings Menu" << std::endl;
    std::cout << "1. Toggle Color: " << (color_enabled_ ? "On" : "Off") << std::endl;
    std::cout << "2. Toggle Sound: " << (sound_enabled_ ? "On" : "Off") << std::endl;
    std::cout << "3. Back" << std::endl;
    std::string choice;
    std::cin >> choice;
    if (choice == "1")
      color_enabled_ = !color_enabled_;
    else if (choice == "2")
      sound_enabled_ = !sound_enabled_;
    else
      current_state_ = State::MAIN_MENU;
  }

  void Game::Help()
  {
    ClearScreen();
    std::cout << "Help System" << std::endl;
    std::cout << "Navigation: WASD or arrows" << std::endl;
    /* Add more help */
    std::cout << "Press enter to return." << std::endl;
    std::cin.get();
    current_state_ = State::MAIN_MENU;
  }

  void Game::CaptainsLog()
  {
    ClearScreen();
    std::cout << "Captain's Log" << std::endl;
    for (const auto &entry : captains_log_)
    {
      std::cout << entry << std::endl;
    }
    std::cout << "Enter new entry (or empty to back): ";
    std::string entry;
    std::getline(std::cin, entry);
    if (!entry.empty())
      LogEntry(entry);
    current_state_ = State::MAIN_MENU;
  }

  void Game::PlayGame()
  {
    ClearScreen();
    std::cout << "Player: " << player_name_ << " Score: " << score_ << std::endl;
    std::cout << "Position: (" << position_.first << ", " << position_.second << ")" << std::endl;
    std::cout << "Health: " << systems_.health << std::endl;
    /* Show other systems */

    std::cout << "Commands: n - navigate, s - scan (long), c - scan (short), f - fire, r - raise shields, m - main menu" << std::endl;
    char cmd = GetKey();
    if (cmd == 'n')
      Navigate();
    else if (cmd == 's')
      ScanLongRange();
    else if (cmd == 'c')
      ScanShortRange();
    else if (cmd == 'f')
      FireWeapons();
    else if (cmd == 'r')
      RaiseShields();
    else if (cmd == 'm')
      current_state_ = State::MAIN_MENU;
    else
      PlayGame();
  }

  void Game::Navigate()
  {
    /* Simple movement */
    char dir = GetKey();
    if (dir == 'w' || dir == 'A')
      --position_.second;
    else if (dir == 's' || dir == 'B')
      ++position_.second;
    else if (dir == 'a' || dir == 'D')
      --position_.first;
    else if (dir == 'd' || dir == 'C')
      ++position_.first;
    LogEntry("Navigated to (" + std::to_string(position_.first) + ", " + std::to_string(position_.second) + ")");
    PlayGame();
  }

  void Game::ScanLongRange()
  {
    /* Show coordinates */
    ClearScreen();
    std::cout << "Long Range Scan:" << std::endl;
    for (const auto &e : enemies_)
      std::cout << "Enemy at (" << e.first << ", " << e.second << ")" << std::endl;
    for (const auto &f : friends_)
      std::cout << "Friendly at (" << f.first << ", " << f.second << ")" << std::endl;
    for (const auto &p : planets_)
      std::cout << "Planet at (" << p.first << ", " << p.second << ")" << std::endl;
    for (const auto &s : starbases_)
      std::cout << "Starbase at (" << s.first << ", " << s.second << ")" << std::endl;
    std::cout << "Press enter..." << std::endl;
    std::cin.get();
    PlayGame();
  }

  void Game::ScanShortRange()
  {
    ClearScreen();
    constexpr int RANGE = 5;

    std::cout << "Short Range Scan (10x10)" << std::endl;
    std::cout << "Legend: @=You E=Enemy F=Friendly P=Planet B=Starbase"
              << std::endl
              << std::endl;

    int px = position_.first;
    int py = position_.second;

    for (int y = py - RANGE; y < py + RANGE; ++y)
    {
      for (int x = px - RANGE; x < px + RANGE; ++x)
      {
        char cell = '.';
        // player
        if (x == px && y == py)
        {
          cell = '@';
        }
        // enemies
        for (const auto &e : enemies_)
        {
          if (e.first == x && e.second == y)
          {
            cell = 'E';
            break;
          }
        }
        // friends
        for (const auto &f : friends_)
        {
          if (f.first == x && f.second == y)
          {
            cell = 'F';
            break;
          }
        }
        // planets
        for (const auto &p : planets_)
        {
          if (p.first == x && p.second == y)
          {
            cell = 'P';
            break;
          }
        }
        // starbases
        for (const auto &s : starbases_)
        {
          if (s.first == x && s.second == y)
          {
            cell = 'B';
            break;
          }
        }

        std::cout << cell << ' ';
      }
      std::cout << std::endl;
    }

    std::cout << std::endl
              << "Press Enter to return..." << std::endl;
    std::cin.get();

    PlayGame();
  }

  void Game::EnemyTurn()
  {
    if (enemies_.empty())
      return;

    /* Find nearest enemy */
    double min_dist = std::numeric_limits<double>::max();
    std::pair<int, int> nearest = enemies_[0];
    bool found = false;

    for (const auto &e : enemies_)
    {
      double dx = e.first - position_.first;
      double dy = e.second - position_.second;
      double dist = std::sqrt(dx * dx + dy * dy);
      if (dist < min_dist)
      {
        min_dist = dist;
        nearest = e;
        found = true;
      }
    }

    if (found)
    {
      SetColor("red");
      std::cout << "Enemy at (" << nearest.first << ", " << nearest.second << ") attacks you!" << std::endl;
      ResetColor();
      systems_.health -= 10.0;
      if (systems_.health < 0)
        systems_.health = 0;
      LogEntry("Attacked by enemy at (" + std::to_string(nearest.first) + ", " + std::to_string(nearest.second) + ")");
      ShowProgressBar("Taking Damage", 500);
    }
  }

  void Game::FireWeapons()
  {
    /* Simple fire */
    if (systems_.weapons > 0)
    {
      std::cout << "Firing weapons!" << std::endl;
      Beep();
      /* Remove enemy if hit */
      score_ += 10;
      EnemyTurn();
    }
    else
    {
      SetColor("red");
      std::cout << "Weapons offline!" << std::endl;
      ResetColor();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    PlayGame();
  }

  void Game::RaiseShields()
  {
    if (systems_.shields < 100)
    {
      systems_.shields += 10;
      std::cout << "Shields raised to " << systems_.shields << std::endl;
    }
    PlayGame();
  }

  void Game::LogEntry(const std::string &entry)
  {
    std::lock_guard<std::mutex> lock(log_mutex_);
    std::string stamped = GetTimeStamp() + " " + entry;
    captains_log_.push_back(stamped);
    std::ofstream ofs("data/captains_log.log", std::ios::app);
    if (ofs)
    {
      ofs << stamped << std::endl;
      ofs.close();
    }
    LOG(INFO) << stamped; /* glog */
  }

  void Game::ShowProgressBar(const std::string &label, int duration_ms)
  {
    int steps = 20;
    int sleep_ms = duration_ms / steps;
    std::cout << label << ": [";
    for (int i = 0; i < steps; ++i)
    {
      std::cout << "=";
      std::cout.flush();
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
    }
    std::cout << "]" << std::endl;
  }

  void Game::ClearScreen()
  {
    std::cout << "\033[2J\033[1;1H\n";
  }

  void Game::SetColor(const std::string &color)
  {
    if (!color_enabled_)
      return;
    if (color == "black")
      std::cout << "\033[30m";
    else if (color == "white")
      std::cout << "\033[37m";
    else if (color == "blue")
      std::cout << "\033[34m";
    else if (color == "gray")
      std::cout << "\033[90m";
    else if (color == "yellow")
      std::cout << "\033[33m";
    else if (color == "green")
      std::cout << "\033[32m";
    else if (color == "cyan")
      std::cout << "\033[36m";
    else if (color == "amber")
      std::cout << "\033[33m"; /* approx */
    else if (color == "red")
      std::cout << "\033[31m";
    else if (color == "orange")
      std::cout << "\033[33m"; /* approx */
  }

  void Game::ResetColor()
  {
    if (!color_enabled_)
      return;
    std::cout << "\033[0m";
  }

  void Game::InverseText(bool enable)
  {
    if (enable)
      std::cout << "\033[7m";
    else
      std::cout << "\033[0m";
  }

  void Game::FlashingText(bool enable)
  {
    if (enable)
      std::cout << "\033[5m";
    else
      std::cout << "\033[0m";
  }

  char Game::GetKey()
  {
    char c = std::getchar();
    if (c == '\033')
    {
      std::getchar();     /* [ */
      c = std::getchar(); /* A B C D */
      return c;
    }
    return std::tolower(c);
  }

  int Game::GetMenuChoice(const std::vector<std::string> &options)
  {
    int selected = 0;
    while (true)
    {
      ClearScreen();
      for (std::size_t i = 0; i < options.size(); ++i)
      {
        if (static_cast<int>(i) == selected)
        {
          InverseText(true);
        }
        std::cout << options[i] << std::endl;
        InverseText(false);
      }
      char key = GetKey();
      if (key == 'A' || key == 'w')
        selected = std::max(0, selected - 1);
      else if (key == 'B' || key == 's')
        selected = std::min(static_cast<int>(options.size() - 1), selected + 1);
      else if (key == '\n' || key == '\r')
        return selected;
    }
  }

  void Game::DetectTerminalSize()
  {
    char *lines = std::getenv("LINES");
    char *columns = std::getenv("COLUMNS");
    if (lines)
      term_height_ = std::stoi(lines);
    if (columns)
      term_width_ = std::stoi(columns);
  }

  void Game::CreateDataDir()
  {
    std::filesystem::create_directory("data");
    std::filesystem::create_directory("data/users");
  }

  std::string Game::GetTimeStamp()
  {
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);
    std::stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
  }

  void Game::Beep()
  {
    if (sound_enabled_)
      std::cout << '\a' << std::flush;
  }

  void Game::Serialize(std::ofstream &ofs) const
  {
    ofs.write(reinterpret_cast<const char *>(&score_), sizeof(score_));
    ofs.write(reinterpret_cast<const char *>(&systems_), sizeof(systems_));
    ofs.write(reinterpret_cast<const char *>(&position_), sizeof(position_));
    /* Serialize vectors */
    std::size_t size = enemies_.size();
    ofs.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (const auto &e : enemies_)
      ofs.write(reinterpret_cast<const char *>(&e), sizeof(e));
    /* Similar for others */
    /* Captains log as text */
    for (const auto &log : captains_log_)
    {
      std::size_t len = log.size();
      ofs.write(reinterpret_cast<const char *>(&len), sizeof(len));
      ofs.write(log.c_str(), len);
    }
  }

  void Game::Deserialize(std::ifstream &ifs)
  {
    ifs.read(reinterpret_cast<char *>(&score_), sizeof(score_));
    ifs.read(reinterpret_cast<char *>(&systems_), sizeof(systems_));
    ifs.read(reinterpret_cast<char *>(&position_), sizeof(position_));
    std::size_t size;
    ifs.read(reinterpret_cast<char *>(&size), sizeof(size));
    enemies_.resize(size);
    for (auto &e : enemies_)
      ifs.read(reinterpret_cast<char *>(&e), sizeof(e));
    /* Similar for others */
    captains_log_.clear();
    while (ifs)
    {
      std::size_t len;
      ifs.read(reinterpret_cast<char *>(&len), sizeof(len));
      if (ifs.eof())
        break;
      std::string log(len, ' ');
      ifs.read(&log[0], len);
      captains_log_.push_back(log);
    }
  }

} // namespace starship
