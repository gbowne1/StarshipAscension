#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

#include "game_ui.hpp"
#include "input_utils.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();
    void stopGame();
    void listSaveFiles();
    void displayShipSystemsOverview();
    void viewCrewList(); // View list of crew members
    void assignRoles(); // Assign roles to crew members
    void dismissCrewMember(); // Dismiss a crew member
    void addCrewMember(); // Add a new crew member
    void viewCrewStatus(); // View

private:
    GameUi ui;
    void addToCaptainsLog(const std::string &entry); // Add entry to captain's log
    void initializeCaptainsLog(); // Initialize captain's log
    void initializeStep(const std::string &step); // Initialize game step
    void processPlayerInput();
    void updateGameState();
    void manageCrew();
    void render();
    bool getIsRunning() const;
    void saveGame();                                   // Save game method
    void loadGame();                                   // Load game method
    void saveAsPlainText(const std::string &fileName); // Save as plain text
    // void saveAsJSON(const std::string &fileName);        // Save as JSON
    void saveAsXML(const std::string &fileName);         // Save as XML
    void saveAsBinary(const std::filesystem::path &filePath);      // Save as binary
    void loadFromPlainText(const std::string &fileName); // Load from plain text
    // void loadFromJSON(const std::string &fileName);      // Load from JSON
    void loadFromXML(const std::string &fileName);    // Load from XML
    void loadFromBinary(const std::string &fileName); // Load from binary
    // TODO: implement scanField function to scan the field
    // void scanField(const std::vector<std::vector<char>> &field, int playerX, int playerY);

    // Game attributes
    void setPlayerName(std::string& name);
    std::vector<std::string> captainsLog;
    std::string getPlayerName() const;
    std::string playerInput;
    std::string playerName;
    std::string shipName;
    std::string chiefEng;
    std::string chiefTac;
    std::string chiefSecurity;
    std::string firstOfficer;
    std::string secondOfficer;
    std::string chiefMed;
    std::string chiefScience;
    int currentLocation;
    int playerPosition;
    int shieldStrength;
    int shieldStatus;
    int hullIntegrity;
    bool sheieldStrength;
    bool isRunning;
    int crewSize;
};

#endif // GAME_HPP
