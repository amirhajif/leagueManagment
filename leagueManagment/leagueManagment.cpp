#include <iostream>
#include <fstream>
#include <vector>
#include "Classes.h"

//global binary file names
string leagueManagerFile = "leagueManager.dat";
string teamManagerFile = "teamManager.dat";
string coachFile = "coach.dat";
string playerFile = "player.dat";
string teamFile = "team.dat";
string requestFile = "request.dat";



using namespace std;
//function for initialize files of each class
void initFiles(vector <LeagueManager>&, vector <TeamManager>&, vector<Coach>&,
	vector<Player>&, vector<Team>&, vector<Request>&);

int main()
{
	//vectors
	vector <LeagueManager> leagueManagers;
	vector <TeamManager>teamManagers;
	vector<Coach> coaches;
	vector<Player> players;
	vector<Team> teams;
	vector<Request>requestes;

	initFiles(leagueManagers, teamManagers, coaches, players, teams, requestes);

	/*while (true)
	{


	}*/
}
void initFiles(vector <LeagueManager>& leagueManagers, vector <TeamManager>& teamManagers , vector<Coach>& coaches,
	vector<Player>& players, vector<Team>& teams, vector<Request>& requestes)
{
	//league manager file initialize
	ifstream leagueManager(leagueManagerFile,ios::binary);
	if(leagueManager)
	{
		LeagueManager lm;
		while (!leagueManager.eof())
		{
			leagueManager.read(reinterpret_cast<char*>(&lm), sizeof(LeagueManager));
			leagueManagers.push_back(lm);
		}
		leagueManager.close();
	}
	else
	{
		leagueManager.close();
		ofstream newFile(leagueManagerFile, ios::binary);
		newFile.close();
	}

	//team manager file initialize
	ifstream teamManager(teamManagerFile, ios::binary);
	if (teamManager)
	{
		TeamManager tm;
		while (!teamManager.eof())
		{
			teamManager.read(reinterpret_cast<char*>(&tm), sizeof(TeamManager));
			teamManagers.push_back(tm);
		}
		teamManager.close();
	}
	else
	{
		teamManager.close();
		ofstream newFile(teamManagerFile, ios::binary);
		newFile.close();
	}

	//coach file initialize
	ifstream coach(coachFile, ios::binary);
	if (coach)
	{
		Coach co;
		while (!coach.eof())
		{
			coach.read(reinterpret_cast<char*>(&co), sizeof(Coach));
			coaches.push_back(co);
		}
		coach.close();
	}
	else
	{
		coach.close();
		ofstream newFile(coachFile, ios::binary);
		newFile.close();
	}

	//player file initialize
	ifstream player(playerFile, ios::binary);
	if (player)
	{
		Player pl;
		while (!player.eof())
		{
			player.read(reinterpret_cast<char*>(&pl), sizeof(Player));
			players.push_back(pl);
		}
		player.close();
	}
	else
	{
		player.close();
		ofstream newFile(playerFile, ios::binary);
		newFile.close();
	}

	//teams file initialize
	ifstream team(teamFile, ios::binary);
	if (team)
	{
		Team tm;
		while (!team.eof())
		{
			player.read(reinterpret_cast<char*>(&tm), sizeof(Team));
			teams.push_back(tm);
		}
		team.close();
	}
	else
	{
		team.close();
		ofstream newFile(teamFile, ios::binary);
		newFile.close();
	}

	//request file initialize
	ifstream request(requestFile, ios::binary);
	if (request)
	{
		Request re;
		while (!request.eof())
		{
			request.read(reinterpret_cast<char*>(&re), sizeof(Request));
			requestes.push_back(re);
		}
		request.close();
	}
	else
	{
		request.close();
		ofstream newFile(requestFile, ios::binary);
		newFile.close();
	}

}