#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include <map>
#include <utility>

using nlohmann::json;

 // General
void setColor(int textColor, int backgroundColor);

 // ID generation
std::string generateClubID();
std::string generateNationID();
std::string generatePlayerID();

 // Simulation
void selectPosition(const std::string pos, std::vector<std::string>& ids, int tries);
void formation(std::string home, std::string away, std::vector<json> homePL, std::vector<json> awayPL, std::map<std::string, std::string>& homePositionMappings, std::map<std::string, std::string>& awayPositionMappings);
void simulate(int option1, int option2);
std::map<json, std::pair<int, int>> returnWeights(std::map<json, int>& players);