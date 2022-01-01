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

//function for check the file is empty or not
bool isFileEmpty(string);

//function for initialize files of each class
void initFiles(vector <LeagueManager>&, vector <TeamManager>&,
	vector<Coach>&, vector<Player>&, vector<Team>&, vector<Request>&);

//check username before submit not be duplicated
bool isUserNameExist(string,vector<TeamManager>&);

//sign up team manager
void signUpTeamManager(vector<TeamManager>& teamManagers)
{
	cin.clear();
	cin.ignore();

	string firstName,lastName,userName,password;

	cout << "enter first name:\t";
	getline(cin, firstName);

	cout << "enter last name:\t";
	getline(cin, lastName);
	//check user name not be duplicated
	while (true)
	{
		cout << "enter user name:\t";
		getline(cin, userName);
		if (!isUserNameExist(userName, teamManagers))
			break;
		else
			cout << "plz select another one it`s exist!!\n";
	}
	cout << "plz enter password:\t";
	getline(cin,password);

	TeamManager tm(userName, password, firstName, lastName);
	teamManagers.push_back(tm);
	ofstream file(teamManagerFile, ios::binary | ios::app);
	file.write(reinterpret_cast<const char*>(&tm), sizeof(TeamManager));
	file.close();
}

//function for show team manager menu
void teamManagerMenu(vector<TeamManager>& teamManagers)
{
	cout << "1-logIn\n2-i`m new(sign up)\nenter option:\t";
	int opt;
	cin >> opt;
	switch (opt)
	{
	case 1:
		//login and do activity
		break;
	case 2:
		signUpTeamManager(teamManagers);
		break;
	default:
		break;
	}

}

int main()
{
	TeamManager* tm = new TeamManager();

	//moshkel aval ke bod:
	//2 field of request class should be pointer
	//if want to change this two fiedl use new operator

	//moshkel dovom:
	//vaghti file binary ro misakhti va mikhasti baraye bare dovom run begiri
	//on file khali bod va khataye memory access violation midad

	Team* team = new Team("manager1", "coach1");
	Player* player = new Player
		(
		"username", "password", "firstname",
		"lastname", "goalie", 120, 450, 0
		);

	Request r(team, "some thing", player, "agrumentring");
	//cout << r.getRequstedPlayer().getFirstName();

	
	//vectors
	vector <LeagueManager> leagueManagers;
	vector <TeamManager>teamManagers;
	vector<Coach> coaches;
	vector<Player> players;
	vector<Team> teams;
	vector<Request>requestes;

	initFiles
	(
		leagueManagers, teamManagers, coaches,
		players, teams, requestes
	);

	while (true)
	{
		cout << "1-teamManager menu\n2-player menu\n3-Coach menu\n4-leagueManager\n5-exit\nenter option:\t";
		int opt;
		cin >> opt;
		switch (opt)
		{
			case 1:
				teamManagerMenu(teamManagers);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				break;
		}
		if (opt == 5)
			break;
	}
	
}
void initFiles(vector <LeagueManager>& leagueManagers, 
	vector <TeamManager>& teamManagers , vector<Coach>& coaches,
	vector<Player>& players, vector<Team>& teams, 
	vector<Request>& requestes)
{
	//league manager file initialize
	ifstream leagueManager(leagueManagerFile,ios::binary);
	if(leagueManager)
	{
		if (!isFileEmpty(leagueManagerFile))
		{
			LeagueManager lm;
			while (!leagueManager.eof())
			{
				leagueManager.read(reinterpret_cast<char*>(&lm), sizeof(LeagueManager));
				leagueManagers.push_back(lm);
			}
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
		if (!isFileEmpty(teamManagerFile))
		{
			TeamManager tm;

			while (!teamManager.eof())
			{
				teamManager.read(reinterpret_cast<char*>(&tm), sizeof(TeamManager));
				teamManagers.push_back(tm);
			}

			teamManager.close();
		}
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
		if (!isFileEmpty(coachFile))
		{
			Coach co;
			while (!coach.eof())
			{
				coach.read(reinterpret_cast<char*>(&co), sizeof(Coach));
				coaches.push_back(co);
			}
			coach.close();
		}

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
		if (!isFileEmpty(playerFile))
		{
			Player pl;
			while (!player.eof())
			{
				player.read(reinterpret_cast<char*>(&pl), sizeof(Player));

				players.push_back(pl);
			}
			player.close();
		}
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
		if (!isFileEmpty(teamFile))
		{
			Team tm;
			while (!team.eof())
			{
				player.read(reinterpret_cast<char*>(&tm), sizeof(Team));
				teams.push_back(tm);
			}
			team.close();
		}
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
		if (!isFileEmpty(requestFile))
		{
			Request re;
			while (!request.eof())
			{
				request.read(reinterpret_cast<char*>(&re), sizeof(Request));
				requestes.push_back(re);
			}
			request.close();
		}
	}
	else
	{
		request.close();
		ofstream newFile(requestFile, ios::binary);
		newFile.close();
	}

}

bool isUserNameExist(string userName, vector<TeamManager>& teamManagers)
{
	for (int i = 0; i < teamManagers.size(); i++)
		if (teamManagers[i].getUsername() == userName)
			return true;
	return false;
}

bool isFileEmpty(string fileAddress)
{
	ifstream file(fileAddress);

	file.seekg(0, ios::end);
	if (file.tellg() == 0)
		return true;
	else
		return false;
}