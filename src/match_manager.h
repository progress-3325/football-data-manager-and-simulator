#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Player {
	std::string name, position, nationality, DoB, CED, workRate, prefferedRole;
	int rating, number, pace, dribbling, passing, shooting, defending, physicality, value, wage, composure, vision, positioning, longShots, defWorkRate, offWorkRate, teamID, aggression, penaltyShoot, setPiece, ballControl, stamina, injuryProne, matchesPlayed, goalsScored, assists, cleanSheets, tacklesWon, passingAccuracy, shotsOnTarget, potentialRating, trainingWorkRate, clutchFactor;
	std::vector<std::string> positions = { "Goalkeeper", "Center Back", "Left Back", "Right Back", "Left Wing-Back", "Right Wing-Back", "Sweeper", "Central Midfielder", "Left Midfielder", "Right Midfielder", "Central Attacking Midfielder", "Attacking Midfielder", "Wide Midfielder", "Defensive Midfielder", "Central Defensive Midfielder", "Center Forward", "Left Winger", "Right Winger", "Striker", "Second Striker" };
	int versatilityScore;
	std::vector<std::string> specialTraits;
};

struct Team {
	bool nationalTeam;
	std::string name, headCoach, fansName, stadiumName, Owner;
	std::vector<Player> players;
	int teamID, yearFounded, leagueTitles, cupsWon, stadiumCapacity, squadSize, trainingFacilities, youthClubSquadMembers, youthClubRating, popularity;
	std::vector<int> rivalTeams;
	std::vector<std::string> colors;
};

class MatchManager {
public:
	MatchManager(const std::map<int, Team>& teams);
	void selectTeams(int& team1ID, int& team2ID);
	void simulateMatch(int team1ID, int team2ID);

private:
	std::map<int, Team> teams;
};
