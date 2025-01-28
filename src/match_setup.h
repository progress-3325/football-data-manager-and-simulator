#pragma once
#include "json.hpp"
void matchSettings();
void getClubMatchTeams(nlohmann::json team1, nlohmann::json team2);
void getNationMatchTeams(nlohmann::json team1, nlohmann::json team2);
void getClubNationMatchTeams(nlohmann::json team1, nlohmann::json team2);