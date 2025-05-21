#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib>

#include "game_ui.hpp"
#include "crew_manager.hpp"
#include "save_manager.hpp"

void GameUi::clearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/Mac
#endif
}

void GameUi::displayWelcomeScreen()
{
    std::cout << "=====================================" << std::endl;
    std::cout << "          StarshipAscension          " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Welcome aboard, Captain " << playerName << "!\n";
    std::cout << "A galaxy of adventure awaits you, Captain!" << std::endl;
    std::cout << "Prepare to explore the stars and achieve ascension." << std::endl;
    std::cout << "\nPress Enter to continue..." << std::endl;
    std::cin.get(); // Wait for the user to press Enter
    clearScreen();  // Clear the screen after input
}

void GameUi::displayMainMenu()
{
    std::cout << "=====================================" << std::endl;
    std::cout << "             Main Menu               " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Continue Game" << std::endl;
    // TODO: Implement save GameUi functionality, renumber the menu options accordingly
    std::cout << "3. Save Game" << std::endl;
    std::cout << "3. Load Saved Game" << std::endl;
    std::cout << "4. Captain's Log" << std::endl;
    std::cout << "5. Mission Briefing" << std::endl;
    std::cout << "6. Ship Systems Overview" << std::endl;
    std::cout << "7. Help" << std::endl;
    std::cout << "8. Setup Game" << std::endl;
    std::cout << "9. Credits" << std::endl;
    std::cout << "10. Exit" << std::endl;
    std::cout << "11. Resume Last Mission" << std::endl;
    std::cout << "12. Tactical Overview" << std::endl;
    std::cout << "13. Manage Crew" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Welcome, Captain " << playerName << "!" << std::endl;
    std::cout << "Your current position: " << playerPosition << std::endl;
    std::cout << "Your ship: " << shipName << std::endl;
    std::cout << "Crew Size: " << crewSize << std::endl;
    std::cout << "First Officer: " << firstOfficer << std::endl;
    std::cout << "Second Officer: " << secondOfficer << std::endl;
    std::cout << "Chief Security Officer: " << chiefSecurity << std::endl;
    std::cout << "Chief Medical Officer:" << chiefMed << std::endl;
    std::cout << "Chief Engineer: " << chiefEng << std::endl;
    std::cout << "Chief Tactical Officer: " << chiefTac << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Available Commands:\n";
    std::cout << "1. Move: Move to a new position." << std::endl;
    std::cout << "2. Quit: Exit the GameUi." << std::endl;
    std::cout << "3. Menu: Display the main menu." << std::endl;
    std::cout << "4. Scan: Scan the surrounding area." << std::endl;
    std::cout << "5. Help: Display help information." << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << std::endl << "Select an option: ";

    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        std::cout << "\nStarting a new GameUi...\n";
        // TODO: Implement new GameUi functionality
        // std:cout << "\nLoading playing field...\n";
        // std::cout << "Initializing GameUi...\n";
        // std::cout << "Initializing player...\n";
        // std::cout << "Initializing ship...\n";
        // std::cout << "Initializing crew...\n";
        // std::cout << "Initializing mission...\n";
        // std::cout << "loading mission..\n";
        // std::cout << "Initializing ship systems...\n";
        // std::cout << "Initializing ship inventory...\n";
        // std::cout << "Initializing ship map...\n";
        // std::cout << "Initializing ship log...\n";
        // std::cout << "Initializing ship settings...\n";
        // std::cout << "Initializing systems...\n";
        // std::cout << "Initializing inventory...\n";
        // std::cout << "Initializing map...\n";
        // std::cout << "Initializing log...\n";
        // std::cout << "Initializing settings...\n";

        break;
    case 2:
        std::cout << "\nContinuing GameUi...\n";
        break;
        case 3:
        {
            std::cout << "\nLoading saved GameUi...\n";
            std::cout << "Choose a format to load your GameUi:\n";
            std::cout << "1. Plain Text (.txt)\n";
            std::cout << "2. JSON (.json)\n";
            std::cout << "3. XML (.xml)\n";
            std::cout << "4. Binary (.dat)\n";
            std::cout << "Enter your choice: ";
            int loadChoice;
            std::cin >> loadChoice;

            std::cout << "Here are the available save files:\n";
            listSaveFiles(); // Display available save files

            std::cout << "Enter the name of the saved GameUi file (with extension): ";
            std::string fileName;
            std::cin.ignore();
            std::getline(std::cin, fileName);

            switch (loadChoice)
            {
            case 1:
                loadFromPlainText(fileName);
                break;
            case 2:
                // loadFromJSON(fileName);
                break;
            case 3:
                loadFromXML(fileName);
                break;
            case 4:
                loadFromBinary(fileName);
                break;
            default:
                std::cout << "Invalid choice. Returning to menu...\n";
                return;
            }

            std::cout << "\nPress Enter to return to the Main Menu.";
            std::cin.get();
            clearScreen();
            displayMainMenu();
            break;
        }
        case 4:
{
    clearScreen();
    std::cout << "Initializing Captain's Log...\n";

    int progress = 0;
    int total = 100;

    for (progress = 0; progress <= total; progress += 10) // Simulate loading in increments
    {
        renderProgressBar(progress, total);
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate loading delay
    }
    std::cout << std::endl; // Move to a new line after the progress bar completes

    std::cout << "Captain's Log initialized successfully.\n";
    std::cout << "\nDisplaying Captain's Log...\n";
    std::cout << "=====================\n";

    // Display mock Captain's Log entries (for testing)
    std::cout << "[TODO: Implement Captain's Log functionality]\n";
    std::cout << "\nPress Enter to return to the Main Menu.";
    std::cin.ignore();
    std::cin.get();
    clearScreen();
    displayMainMenu();
    break;
    }

    case 5:
        std::cout << "\nDisplaying mission briefing...\n";
        std::cout << "[TODO: Implement Mission Briefing]\n";
        std::cout << "\nPress Enter to return to the Main Menu.";
        std::cin.ignore();
        std::cin.get();
        clearScreen();
        // TODO: Implement mission briefing functions
        // createMissionBriefing();
        // saveMissionBriefing();
        // loadMissionBriefing();
        // displayMissionBriefing();
        displayMainMenu();
        break;
    case 6:
        std::cout << "\nDisplaying ship systems overview...\n";
        std::cout << "\nPress Enter to return to the Main Menu.";
        std::cin.ignore();
        std::cin.get();
        clearScreen();
        displayShipSystemsOverview();
        displayMainMenu();
        break;
    case 7:
        displayHelpMenu();
        break;
    case 8:
        displaySetupMenu();
        break;
    case 9:
        displayCredits();
        break;
    case 10:
        std::cout << "\nExiting. Goodbye!\n";
        stopGame();
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        clearScreen();
        manageCrew();
        break;
    default:
        std::cout << "\nInvalid choice. Returning to menu...\n";
        clearScreen();
        displayMainMenu();
    }
}

void GameUi::displayCaptainsLog()
{
    clearScreen(); // Optional: Clear the screen for better readability
    std::cout << "=====================================\n";
    std::cout << "          Captain's Log              \n";
    std::cout << "=====================================\n";

    if (captainsLog.empty())
    {
        std::cout << "The Captain's Log is empty. No entries recorded yet.\n";
    }
    else
    {
        for (size_t i = 0; i < captainsLog.size(); ++i)
        {
            std::cout << i + 1 << ". " << captainsLog[i] << std::endl;
        }
    }

    std::cout << "\nPress Enter to return to the Main Menu.";
    std::cin.ignore();
    std::cin.get();
}

void GameUi::displayHelpMenu()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "               Help Menu              " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Welcome to StarshipAscension!" << std::endl;
    std::cout << "Here are some tips to help you get started:\n";
    std::cout << "- Use 'move' to explore the galaxy." << std::endl;
    std::cout << "- Use 'quit' to end the GameUi." << std::endl;
    std::cout << "- Complete missions to gain points and advance." << std::endl;
    std::cout << "\nPress Enter to return to the Main Menu." << std::endl;
    std::cin.ignore();
    std::cin.get();
    clearScreen();
    displayMainMenu();
}

void GameUi::displaySetupMenu()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "            Setup Game Menu          " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Configure your Game settings here.\n";

    std::cout << "Enter the number of players: ";
    int numPlayers;
    std::cin >> numPlayers;

    std::cout << "Enter your ship's name: ";
    std::string shipName;
    std::cin.ignore(); // Clear buffer before getline
    std::getline(std::cin, shipName);

    std::cout << "Enter your name, Captain: ";
    std::getline(std::cin, playerName); // Store the player name

    std::cout << "Enter your First Officer's name: ";
    std::getline(std::cin, firstOfficer); // Store the first officer's name

    std::cout << "Enter your Second Officer's name: ";
    std::getline(std::cin, secondOfficer); // Store the second officer's name

    std::cout << "Enter your Chief Security Officer's name: ";
    std::getline(std::cin, chiefSecurity); // Store the chief security officer's name

    std::cout << "Enter your Chief Medical Officer's name: ";
    std::getline(std::cin, chiefMed); // Store the chief medical officer's name

    std::cout << "Enter your Chief Engineer's name: ";
    std::getline(std::cin, chiefEng); // Store the chief engineer's name

    std::cout << "Enter your Chief Tactical Officer's name: ";
    std::getline(std::cin, chiefTac); // Store the chief tactical officer's name

    std::cout << "Enter your Chief Science Officer's name: ";
    std::getline(std::cin, chiefScience); // Store the chief science officer's name

    std::cout << "Would you like to manage your crew, captain? (yes/no): ";
    std::string manageCrewChoice;
    std::getline(std::cin, manageCrewChoice); // Store the crew management choice
    if (manageCrewChoice == "yes" || manageCrewChoice == "y")
    {
        std::cout << "You can manage your crew in the Manage Crew Menu.\n";
        manageCrew();
        clearScreen();
    } else if (manageCrewChoice == "no" || manageCrewChoice == "n")
    {
        std::cout << "You can manage your crew later in the GameUi.\n";
        clearScreen();
    }
    clearScreen();
    std::cout << "\nConfiguration complete!\n";
    std::cout << "Players: " << numPlayers << "\nShip Name: " << shipName << "\nCaptain: " << playerName << std::endl;
    std::cout << "\nPress Enter to return to the Main Menu." << std::endl;
    std::cin.get();
    // TODO: Implement saveSetup function to save the setup
    // saveSetup();
    clearScreen();

    displayMainMenu();
}

void GameUi::displayShipSystemsOverview()
{
    clearScreen(); // Clear the screen for better visibility
    std::cout << "=====================================" << std::endl;
    std::cout << "         Ship Systems Overview        " << std::endl;
    std::cout << "=====================================" << std::endl;

    // General Ship Info
    std::cout << "Ship Name: " << shipName << std::endl; // Dynamically update ship name
    std::cout << "Captain:   " << playerName << std::endl; // Display captain's name
    std::cout << "First Officer: " << firstOfficer << std::endl; // Placeholder for first officer
    std::cout << "Second Officer: " << secondOfficer << std::endl; // Placeholder for second officer
    std::cout << "Chief Security Officer: " << chiefSecurity << std::endl; // Placeholder for chief security officer
    std::cout << "Chief Medical Officer: " << chiefMed << std::endl; // Placeholder for chief medical officer
    std::cout << "Chief Engineer: " << chiefEng << std::endl; // Placeholder for chief engineer
    std::cout << "Chief Tactical Officer: " << chiefTac << std::endl; // Placeholder for chief tactical officer
    std::cout << "Current Location: " << currentLocation << std::endl; // Placeholder for current location
    std::cout << "Current Position: " << playerPosition << std::endl; // Placeholder for current position
    std::cout << "Ship Status:  Online" << std::endl; // Placeholder for ship status
    std::cout << "Mission Status: In Progress" << std::endl; // Placeholder for mission status
    std::cout << "Crew Size: " << crewSize << std::endl; // Placeholder for crew size
    std::cout << "=====================================" << std::endl;

    // Ship Systems Status
    std::cout << "Power Core:  Online (85% capacity)" << std::endl; // Example data
    std::cout << "Engines:     Operational (Warp Speed: 3.5)" << std::endl;
    std::cout << "Shields Status: " << shieldStatus << std::endl;
    std::cout << "Sheilds Strength: " << shieldStrength << std::endl;
    std::cout << "Hull Integrity: " << hullIntegrity << std::endl; // Example data
    std::cout << "Weapons:     Armed (Photon Torpedoes: 8 remaining)" << std::endl;
    std::cout << "Sensors:     Calibrated (Range: 20,000 km)" << std::endl;
    std::cout << "Life Support: Nominal (Oxygen: 95%)" << std::endl;
    std::cout << "=====================================" << std::endl;

    // Mission Objectives
    std::cout << "Mission Objectives:" << std::endl;
    std::cout << "- Explore the Alpha Centauri System" << std::endl; // Placeholder mission
    std::cout << "- Deliver supplies to Station Delta" << std::endl;
    std::cout << "- Respond to distress signal near Proxima Centauri" << std::endl;
    std::cout << "=====================================" << std::endl;

    // Cargo Bay Inventory
    std::cout << "Cargo Bay:" << std::endl;
    std::cout << "- Medical Supplies: 20 crates" << std::endl;
    std::cout << "- Food Rations:     15 crates" << std::endl;
    std::cout << "- Exotic Minerals:  5 crates" << std::endl;
    std::cout << "=====================================" << std::endl;

    // Ship's Log
    std::cout << "Ship's Log:" << std::endl;
    std::cout << "- Last docked: Starbase 23" << std::endl; // Placeholder log
    std::cout << "- Current Location: " << currentLocation << std::endl;
    std::cout << "- Distress signals received: 1" << std::endl;
    std::cout << "=====================================" << std::endl;

    // Return to Main Menu
    std::cout << "Press Enter to return to the Main Menu..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    clearScreen();
    displayMainMenu(); // Navigate back to the main menu
}

void GameUi::displayCredits()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "               Credits                " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "StarshipAscension was created by Gregory K. Bowne!" << std::endl;
    std::cout << "Special thanks to our interstellar community!\n";
    std::cout << "\nPress Enter to return to the Main Menu." << std::endl;
    std::cin.ignore();
    std::cin.get();
    clearScreen();
    displayMainMenu();
}

void renderProgressBar(int progress, int total)
{
    int barWidth = 50;
    int filledWidth = (progress * barWidth) / total;

    std::cout << "[";
    for (int i = 0; i < filledWidth; ++i)
        std::cout << "=";
    for (int i = filledWidth; i < barWidth; ++i)
        std::cout << " ";
    std::cout << "] " << (progress * 100) / total << "%\r" << std::flush;
}

void GameUi::listSaveFiles() {
    std::cout << "Listing save files..." << std::endl;
}

void GameUi::loadFromPlainText(const std::string& filename) {
    std::cout << "Loading from plain text file: " << filename << std::endl;
}

void GameUi::loadFromXML(const std::string& filename) {
    std::cout << "Loading from XML: " << filename << std::endl;
}

void GameUi::loadFromBinary(const std::string& filename) {
    std::cout << "Loading from binary: " << filename << std::endl;
}

void GameUi::stopGame() {
    std::cout << "Stopping game..." << std::endl;
}

void GameUi::manageCrew() {
    std::cout << "Managing crew..." << std::endl;
}
