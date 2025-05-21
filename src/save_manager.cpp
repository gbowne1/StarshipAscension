#include <iostream>            // For std::cout, std::cin, std::endl
#include <fstream>             // For std::ifstream, std::ofstream
#include <string>              // For std::string
#include <filesystem>          // For std::filesystem::path, etc. (C++17+)
#include <sstream>             // Optional: for string parsing, if needed
#include <cstdlib>             // For system() in clearScreen()
#include "../include/nlohmann/json.hpp"
#include "save_manager.hpp"
#include "game_ui.hpp"
#include "game.hpp"

void SaveGame::saveGame()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "           Save Game Menu             " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Choose a format to save your game:\n";
    std::cout << "1. Plain Text (.txt)\n";
    std::cout << "2. JSON (.json)\n";
    std::cout << "3. XML (.xml)\n";
    std::cout << "4. Binary (.dat)\n";

    int choice;
    std::cin >> choice;

    std::string fileName = "saved_game";
    switch (choice)
    {
    case 1:
        fileName += ".txt";
        saveAsPlainText(fileName); // Call method for plain text saving
        break;
    // case 2:
    //     fileName += ".json";
    //     saveAsJSON(fileName); // Call method for JSON saving
    //     break;
    case 3:
        fileName += ".xml";
        saveAsXML(fileName); // Call method for XML saving
        break;
    case 4:
        fileName += ".dat";
        saveAsBinary(fileName); // Call method for binary saving
        break;
    default:
        std::cout << "Invalid choice. Returning to menu...\n";
        return;
    }

    std::cout << "Game saved successfully to " << fileName << "!\n";
    std::cout << "\nPress Enter to return to the Main Menu.";
    std::cin.ignore();
    std::cin.get();
    displayMainMenu();
}

void SaveGame::loadGame()
{
    clearScreen();
    std::cout << "=====================================" << std::endl;
    std::cout << "           Load Game Menu             " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Choose the format of your saved game:\n";
    std::cout << "1. Plain Text (.txt)\n";
    std::cout << "2. JSON (.json)\n";
    std::cout << "3. XML (.xml)\n";
    std::cout << "4. Binary (.dat)\n";

    int choice;
    std::cin >> choice;

    std::string fileName;
    std::cout << "Enter the name of the saved game file (with extension): ";
    std::cin.ignore(); // Clear buffer
    std::getline(std::cin, fileName);

    switch (choice)
    {
    case 1:
        loadFromPlainText(fileName); // Call method for plain text loading
        break;
    case 2:
        loadFromJSON(fileName); // Call method for JSON loading
        break;
    case 3:
        loadFromXML(fileName); // Call method for XML loading
        break;
    case 4:
        loadFromBinary(fileName); // Call method for binary loading
        break;
    default:
        std::cout << "Invalid choice. Returning to menu...\n";
        return;
    }

    std::cout << "Game loaded successfully from " << fileName << "!\n";
    std::cout << "\nPress Enter to return to the Main Menu.";
    std::cin.get();
    displayMainMenu();
}

void SaveGame::listSaveFiles()
{
    std::cout << "Available save files:\n";
    std::filesystem::path saveDir = "saves"; // Directory where save files are stored
    if (std::filesystem::exists(saveDir))
    {
        for (const auto &entry : std::filesystem::directory_iterator(saveDir))
        {
            if (entry.is_regular_file())
            {
                std::cout << "- " << entry.path().filename().string() << std::endl;
            }
        }
    }
    else
    {
        std::cout << "No save files found.\n";
    }
}

void SaveGame::saveAsPlainText(const std::string &fileName)
{
    std::ofstream saveFile(fileName);
    saveFile << "PlayerName: " << playerName << '\n';
    saveFile << "PlayerPosition: " << playerPosition << '\n';
    saveFile << "Score: 500\n"; // Example score
    saveFile.close();
}

void SaveGame::saveAsXML(const std::string &fileName)
{
    std::ofstream saveFile(fileName);
    saveFile << "<Game>\n";
    saveFile << "  <Player>\n";
    saveFile << "    <Name>" << playerName << "</Name>\n";
    saveFile << "    <Position>" << playerPosition << "</Position>\n";
    saveFile << "  </Player>\n";
    saveFile << "  <Score>500</Score>\n";
    saveFile << "</Game>\n";
    saveFile.close();
}

void SaveGame::saveAsBinary(const std::filesystem::path &filePath)
{
    try
    {
        // Ensure the parent directory exists
        if (!std::filesystem::exists(filePath.parent_path()))
        {
            std::filesystem::create_directories(filePath.parent_path());
        }

        // Open file for binary writing
        std::ofstream saveFile(filePath, std::ios::binary);
        if (!saveFile)
        {
            throw std::ios_base::failure("Failed to open file for saving.");
        }

        // Write binary data
        saveFile.write(reinterpret_cast<const char *>(&playerPosition), sizeof(playerPosition));
        saveFile.close();

        std::cout << "Game saved successfully to: " << filePath << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving game: " << e.what() << std::endl;
    }
}

void SaveGame::loadFromPlainText(const std::string& fileName)
{
    std::ifstream file(fileName);

    // Check if file exists and is accessible
    if (!file.is_open())
    {
        std::cout << "Error: Unable to open file " << fileName << std::endl;
        std::cout << "Please ensure the file exists and try again.\n";
        return;
    }

    // Example of loading data from the file
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << "Loaded line: " << line << std::endl; // Replace with your parsing logic
    }

    file.close();
    std::cout << "Game loaded successfully from " << fileName << "!\n";
}

void SaveGame::loadFromXML(const std::string &fileName)
{
    std::ifstream loadFile(fileName);
    if (!loadFile)
    {
        std::cout << "Error: Unable to open file " << fileName << std::endl;
        return;
    }

    std::string line, xmlContent;
    while (std::getline(loadFile, line))
    {
        xmlContent += line + "\n";
    }

    // Parse XML manually for simplicity
    if (xmlContent.find("<Name>") != std::string::npos)
    {
        playerName = xmlContent.substr(xmlContent.find("<Name>") + 6, xmlContent.find("</Name>") - (xmlContent.find("<Name>") + 6));
    }
    if (xmlContent.find("<Position>") != std::string::npos)
    {
        playerPosition = std::stoi(xmlContent.substr(xmlContent.find("<Position>") + 10, xmlContent.find("</Position>") - (xmlContent.find("<Position>") + 10)));
    }
    // Add more attributes to parse here

    loadFile.close();
}

void SaveGame::loadFromBinary(const std::string &fileName)
{
    std::ifstream loadFile(fileName, std::ios::binary);
    if (!loadFile)
    {
        std::cout << "Error: Unable to open file " << fileName << std::endl;
        return;
    }

    loadFile.read(reinterpret_cast<char *>(&playerPosition), sizeof(playerPosition));
    // Add binary loading for other attributes here

    loadFile.close();
}

void Game::setPlayerName(std::string& name)
{
    playerName = name;
}

void SaveGame::loadFromJSON(const std::string &fileName)
{
    std::ifstream loadFile(fileName);
    if (!loadFile)
    {
        std::cout << "Error: Unable to open file " << fileName << std::endl;
        return;
    }

    nlohmann::json loadData;
    loadFile >> loadData;

    playerName = loadData["PlayerName"].get<std::string>();
    playerPosition = loadData["PlayerPosition"].get<int>();
    // Add more attributes to load here

    loadFile.close();
}

void SaveGame::clearScreen() const
{
}

void SaveGame::saveAsJSON(const std::string &fileName)
{
    nlohmann::json saveData;
    saveData["PlayerName"] = playerName;
    saveData["PlayerPosition"] = playerPosition;
    saveData["Score"] = 500;

    std::ofstream saveFile(fileName);
    saveFile << saveData.dump(4); // Pretty print JSON
    saveFile.close();
}

void SaveGame::displayMainMenu() const {
    // show the save/load menu
}
