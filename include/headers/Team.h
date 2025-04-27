#pragma once
#include <string>
#include <json.hpp>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <iostream>

class Team
{
private:
	std::vector <nlohmann::json> allPlayers;
public:
	std::string name;
	std::string id;
	bool checkPlayers(std::vector<nlohmann::json> selectedPlayers)
	{
		std::unordered_set<std::string> checker(allPlayers.begin(), allPlayers.end());
		for (std::string i : selectedPlayers)
		{
			if (checker.find(i) == checker.end()) return false;
		}
		return true;
	}

	Team(std::string teamName) : name(teamName)
	{
		std::ifstream tFile("../data/team_data.json");
		if (!tFile.is_open())
		{
			std::cout << "Error openin team JSON File!\n";
			return;
		}

		nlohmann::json teamDataArray;
		nlohmann::json teamData;
		tFile >> teamDataArray;
		tFile.close();

		std::ifstream pFile("../data/player_data.json");
		if (!pFile.is_open())
		{
			std::cout << "Error openin player JSON File!\n";
			return;
		}
		nlohmann::json playerDataArray;
		pFile >> playerDataArray;
		pFile.close();

		bool found = false;

		for (const auto& i : teamDataArray)
		{
			if (i["name"] == name)
			{
				found = true;
				teamData = i;
				return;
			}
		}

		if (!found)
		{
			std::cout << "Team not found\n";
			return;
		}

		id = teamData["id"];

		for (const auto& i : playerDataArray)
		{
			if (i["team_id"] == id)
			{
				allPlayers.push_back(i);
			}
		}
	}

	operator std::string() const
	{
		return name;
	}
};