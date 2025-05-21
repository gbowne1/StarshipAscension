#ifndef GAME_UI_HPP
#define GAME_UI_HPP

#include <string>
#include <vector>

class GameUi
{
public:
    // UI & Main Menu
    void clearScreen();
    void displayWelcomeScreen();
    void displayMainMenu();
    void displayCaptainsLog();
    void displayHelpMenu();
    void displaySetupMenu();
    void displayShipSystemsOverview();
    void displayCredits();
    void listSaveFiles();
    // Assume these are implemented elsewhere
    void manageCrew(); // From crew_manager.hpp, can optionally forward declare here

private:
    // Member variables assumed from context
    std::string playerName;
    std::string shipName;
    std::string currentLocation;
    std::string playerPosition;

    int crewSize = 0;

    std::string firstOfficer;
    std::string secondOfficer;
    std::string chiefSecurity;
    std::string chiefMed;
    std::string chiefEng;
    std::string chiefTac;
    std::string chiefScience;

    std::string shieldStatus;
    int shieldStrength = 0;
    int hullIntegrity = 0;

    std::vector<std::string> captainsLog;

    // Stub for stopGame, assumed to be implemented
    void stopGame();

    // Save/load stubs assumed to exist

    void loadFromPlainText(const std::string& filename);
    void loadFromXML(const std::string& filename);
    void loadFromBinary(const std::string& filename);
};

void renderProgressBar(int progress, int total); // Non-member utility function

#endif // GAME_UI_HPP
