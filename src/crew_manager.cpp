#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

#include "crew_manager.hpp"
#include "game_ui.hpp"
#include "save_manager.hpp"

void CrewManager::manageCrew()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "           Manage Crew Menu           " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Crew Management System\n";
    std::cout << "1. View Crew List\n";
    std::cout << "2. Assign Roles\n";
    std::cout << "3. Dismiss Crew Member\n";
    std::cout << "4. Add Crew Member\n";
    std::cout << "5. View Crew Status\n";
    std::cout << "6. Return to Main Menu\n";
    std::cout << "=====================================" << std::endl;

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        viewCrewList();
        break;
    case 2:
        assignRoles();
        break;
    case 3:
        dismissCrewMember();
        break;
    case 4:
        addCrewMember();
        break;
    case 5:
        viewCrewStatus();
        break;
    case 6:
        displayMainMenu();
        break;
    default:
        std::cout << "Invalid choice. Returning to Manage Crew Menu...\n";
        manageCrew();
        break;
    }
}

void CrewManager::addCrewMember()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "          Add Crew Member             " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "[TODO: Implement Crew Member Addition]\n";
    std::cout << "\nPress Enter to return to Manage Crew Menu.";
    std::cin.ignore();
    std::cin.get();
    manageCrew(); // Return to the manage crew menu
}

void CrewManager::assignRoles()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "           Assign Roles               " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "[TODO: Implement Role Assignment]\n";
    std::cout << "\nPress Enter to return to Manage Crew Menu.";
    std::cin.ignore();
    std::cin.get();
    manageCrew();
}

void CrewManager::viewCrewList()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "             Crew List                " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "[TODO: Display Crew List]\n";
    std::cout << "\nPress Enter to return to Manage Crew Menu.";
    std::cin.ignore();
    std::cin.get();
    manageCrew();
}

void CrewManager::dismissCrewMember()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "         Dismiss Crew Member          " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "[TODO: Implement Crew Member Dismissal]\n";
    std::cout << "\nPress Enter to return to Manage Crew Menu.";
    std::cin.ignore();
    std::cin.get();
    manageCrew();
}

void CrewManager::viewCrewStatus()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "           Crew Status                " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "[TODO: Display Crew Status]\n";
    std::cout << "\nPress Enter to return to Manage Crew Menu.";
    std::cin.ignore();
    std::cin.get();
    manageCrew();
}

void CrewManager::clearScreen() {
    // e.g., system("cls"); on Windows
}

void CrewManager::displayMainMenu() {
    // your menu logic
}
