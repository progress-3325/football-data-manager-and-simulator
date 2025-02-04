#pragma once
#include "json.hpp"
#include <vector>
void matchSettings();
void getClubMatchTeams(nlohmann::json& team1, nlohmann::json& team2);
void getNationMatchTeams(nlohmann::json& team1, nlohmann::json& team2);
void getClubNationMatchTeams(nlohmann::json& team1, nlohmann::json& team2);
void getClubPlayers(const nlohmann::json& team1, const nlohmann::json& team2, std::vector<nlohmann::json>& homePlayers, std::vector<nlohmann::json>& awayPlayers);