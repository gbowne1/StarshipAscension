// src/ui/PlayingField.cpp

#include "../../include/ui/PlayingField.h"

#include <iostream>
#include <string>

#include "../../include/ui/Display.h"
#include "../../include/ui/PlayingField.h"

// Constants for the terminal size
constexpr int TERMINAL_WIDTH = 207;
constexpr int TERMINAL_HEIGHT = 56;

PlayingField::PlayingField() {
    initializeField(TERMINAL_WIDTH, TERMINAL_HEIGHT);
}

void PlayingField::initializeField(int width, int height) {
    // Set the playing field size
    PLAYING_FIELD_WIDTH = width;
    PLAYING_FIELD_HEIGHT = height;

    // Initialize the playing field with empty spaces
    field.resize(height, std::vector<char>(width, ' '));

    // Add the border to the playing field
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                field[i][j] = PLAYING_FIELD_BORDER;
            }
        }
    }
}

static PlayingField* getInstance() {
    if (!instance) {
        instance = new PlayingField();
    }
    return instance;
}

bool isWithinBounds(const Vector2D& position) const {
    return position.x >= 0 && position.x < PLAYING_FIELD_WIDTH &&
           position.y >= 0 && position.y < PLAYING_FIELD_HEIGHT;
}

void PlayingField::display() const {
    GameObj* PlayingField::getObject(const Vector2D& pos) const {
        return nullptr;
    }
    std::string fieldString;

    // Convert the 2D field vector to a string
    for (const auto& row : field) {
        for (const auto& cell : row) {
            fieldString += cell;
        }
        fieldString += "\n";
    }

    std::cout << fieldString;
}
