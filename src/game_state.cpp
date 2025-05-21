#include "game_state.hpp"

using json = nlohmann::json;

json GameState::toJson() const {
    return json{
        {"playerName", playerName},
        {"level", level},
        {"score", score},
        {"crewMembers", crewMembers}
    };
}

GameState GameState::fromJson(const json& j) {
    GameState state;
    state.playerName = j.at("playerName").get<std::string>();
    state.level = j.at("level").get<int>();
    state.score = j.at("score").get<int>();
    state.crewMembers = j.at("crewMembers").get<std::vector<std::string>>();
    return state;
}
