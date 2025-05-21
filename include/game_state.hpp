#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class GameState {
public:
    std::string playerName;
    int level;
    int score;
    std::vector<std::string> crewMembers;

    // Serialize to JSON
    nlohmann::json toJson() const;

    // Deserialize from JSON
    static GameState fromJson(const nlohmann::json& j);
};

#endif
