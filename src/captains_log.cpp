#include <iostream>   // For std::cout, std::endl
#include <string>     // For std::string
#include <vector>     // For std::vector (used by captainsLog)
#include <fstream>
#include "captains_log.hpp"
#include "game.hpp"

void CaptainsLog::addToCaptainsLog(const std::string &entry)
{
    captainsLog.push_back(entry);
    std::cout << "Entry added to Captain's Log: " << entry << std::endl;
}

// Initializes the Captain's Log by loading from a file or initializing an empty log
void CaptainsLog::initializeCaptainsLog() {
    std::ifstream logFile(captainsLogFile);
    if (logFile.is_open()) {
        std::string line;
        while (std::getline(logFile, line)) {
            captainsLog.push_back(line); // Load existing log entries
        }
        logFile.close();
    } else {
        std::cout << "No existing Captain's Log found. Starting a new log.\n";
        captainsLog.clear(); // Start with an empty log
    }
}

void Game::initializeStep(const std::string &step)
{
    ::initializeStep(step);
} // Creates a new Captain's Log by clearing the current log (if any)
void CaptainsLog::createCaptainsLog() {
    captainsLog.clear();
    std::cout << "Captain's Log has been cleared and is now empty.\n";
}

// Saves the current Captain's Log to a file
void CaptainsLog::saveCaptainsLog() {
    std::ofstream logFile(captainsLogFile);
    if (logFile.is_open()) {
        for (const auto& entry : captainsLog) {
            logFile << entry << "\n"; // Write each log entry to the file
        }
        logFile.close();
        std::cout << "Captain's Log has been saved.\n";
    } else {
        std::cout << "Error: Could not open file for saving the Captain's Log.\n";
    }
}

// Loads the Captain's Log from a file
void CaptainsLog::loadCaptainsLog() {
    std::ifstream logFile(captainsLogFile);
    if (logFile.is_open()) {
        captainsLog.clear(); // Clear any existing log entries
        std::string line;
        while (std::getline(logFile, line)) {
            captainsLog.push_back(line); // Load log entries from the file
        }
        logFile.close();
        std::cout << "Captain's Log has been loaded.\n";
    } else {
        std::cout << "Error: Could not open file to load the Captain's Log.\n";
    }
}

// Deletes the Captain's Log (removes the log file)
void CaptainsLog::deleteCaptainsLog() {
    if (std::remove(captainsLogFile.c_str()) == 0) {
        std::cout << "Captain's Log has been deleted.\n";
    } else {
        std::cout << "Error: Could not delete the Captain's Log file.\n";
    }
}
