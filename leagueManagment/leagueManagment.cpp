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

//function for  check username of teammanager before submit not be duplicated
bool isTmUserNameExist(string,vector<TeamManager>&);

//function for  check username of coach before submit not be duplicated
bool isCoachUserNameExist(string userName,vector<Coach>& coaches)
{
	for (int i = 0; i < coaches.size(); i++)
		if (coaches[i].getUsername() == userName)
			return true;
	return false;
}

//function for sign up team manager
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
		if (!isTmUserNameExist(userName, teamManagers))
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

//function for add coach to coach vector
void signUpCoach(vector<Coach>& coaches, vector<Team>& teams)
{
	//check be team available
	if (teams.size() == 0)
	{
		cout << "sorry we dont have team and cant sumbit coach!!\n";
		return;
	}
	cin.clear();
	cin.ignore();

	string firstName, lastName, userName, password;

	cout << "enter first name:\t";
	getline(cin, firstName);

	cout << "enter last name:\t";
	getline(cin, lastName);
	//check user name not be duplicated
	while (true)
	{
		cout << "enter user name:\t";
		getline(cin, userName);
		if (!isCoachUserNameExist(userName, coaches))
			break;
		else
			cout << "plz select another one it`s exist!!\n";
	}
	cout << "plz enter password:\t";
	getline(cin, password);
	Team t;
	//show list of team for submit

	/*cout << "\nlist of teams available:\n";*/
	//while (true)
	//{
	//	cout << "plz enter team name:\t";
	//	int opt;
	//	for (int i = 0; i < teams.size(); i++)
	//	{
	//		//should be completed........

	//	}

	//}

	Coach coach(userName,password,firstName,lastName,t);
	coaches.push_back(coach);
	ofstream file(coachFile, ios::app | ios::binary);
	file.write(reinterpret_cast<char*>(&coach), sizeof(Coach));
	file.close();
}

//function for edit coach file base on vector
void updateCoachFile(vector<Coach>& coaches)
{
	ofstream file(coachFile,ios::binary);
	file.clear();
	for (int i = 0; i < coaches.size(); i++)
	{
		Coach coach = coaches[i];
		file.write(reinterpret_cast<char*>(&coach), sizeof(Coach));
	}
	file.close();
}

//function for delete coach
void deleteCoach(vector<Coach>& coaches)
{
	cout << "plz enter username of coach:\t";
	string userName;
	getline(cin, userName);
	fstream file(coachFile, ios::binary);
	bool isExist = false;
	int index = 0;
	Coach coach;
	while (!file.eof())
	{
		file.read(reinterpret_cast<char*>(&coach), sizeof(Coach));
		if (coach.getUsername() == userName)
		{
			coaches.erase(coaches.begin() + index);
			updateCoachFile(coaches);
			isExist = true;
			return;
		}
		index++;
	}
	if (!isExist)
		cout << "sorry not found this Coach\n";
	
}

//function for  login and do activity team manager
void logInTeamManager(vector<TeamManager>& teamManagers, vector<Team>& teams, vector<Coach>& coaches)
{
	cin.clear();
	cin.ignore();
	cout << "plz enter username:\t";
	string userName;
	getline(cin, userName);
	int index = -1;
	//check username is exist and pass is correct or not
	//if each one be invalid index equal -1
	for (int i = 0; i < teamManagers.size(); i++)
	{
		if (teamManagers[i].getUsername() == userName)
		{
			string password;
			cout << "plz enter password:\t";
			getline(cin, password);
			if (teamManagers[i].getPassword() == password)
			{
				index = i;
				break;
			}

		}
	}
	//check index
	if (index == -1)
	{
		cout << "you input invalid user/password\n";
		return;
	}
	else
	{
		cout << "1-add coach\n2-delete coach\n3-edit coach\n4-request player\n5-delete team\n6-add player\n7-delete player\nselect option:\t";
		int opt;
		cin >> opt;
		switch (opt)
		{
		case 1:
			signUpCoach(coaches,teams);
			break;
		case 2:
			deleteCoach(coaches);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			break;
		}
	}

}

//function for show team manager menu
void teamManagerMenu(vector<TeamManager>& teamManagers, vector<Team>& teams, vector<Coach>& coaches)
{
	cout << "1-logIn\n2-i`m new(sign up)\n3-exit\nenter option:\t";
	int opt;
	cin >> opt;
	switch (opt)
	{
	case 1:
		logInTeamManager(teamManagers,teams,coaches);
		break;
	case 2:
		signUpTeamManager(teamManagers);
		break;
	case 3:
		break;
	default:
		break;
	}

}


//function for show coach menu
void coachMenu(vector<Team>& teams, vector<Coach>& coaches, vector<Player>& players)
{
	cout << "1-logIn\n2-i`m new(sign up)\n3-exit\nenter option:\t";
	int opt;
	cin >> opt;
	switch (opt)
	{
	case 1:
		
		break;
	case 2:
		signUpCoach(coaches,teams);
		break;
	case 3:
		break;
	default:
		break;
	}
}
int main()
{
	/*TeamManager* tm = new TeamManager();*/

	//moshkel aval ke bod:
	//2 field of request class should be pointer
	//if want to change this two fiedl use new operator

	//moshkel dovom:
	//vaghti file binary ro misakhti va mikhasti baraye bare dovom run begiri
	//on file khali bod va khataye memory access violation midad

	/*Team* team = new Team("manager1", "coach1");
	Player* player = new Player
		(
		"username", "password", "firstname",
		"lastname", "goalie", 120, 450, 0
		);

	Request r(team, "some thing", player, "agrumentring");*/
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
		cout << "1-teamManager menu\n2-Coach menu\n3-leagueManager\n4-exit\nenter option:\t";
		int opt;
		cin >> opt;
		switch (opt)
		{
			case 1:
				teamManagerMenu(teamManagers,teams,coaches);
				break;
			case 2:
				coachMenu(teams,coaches,players);
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

bool isTmUserNameExist(string userName, vector<TeamManager>& teamManagers)
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