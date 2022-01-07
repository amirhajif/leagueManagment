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

//function for find coach with team name
int findCoachByTeamName(vector<Coach>&coaches, string teamName)
{
	int size = coaches.size();
	for (int i = 0; i < size; i++)
	{
		if (coaches[i].getTeam().getTeamName() == teamName)
			return i;
	}

	return -1;
}

//function for update team file
void updateTeamFile(vector<Team> teams)
{
	ofstream file(teamFile, ios::binary);
	file.clear();
	for (int i = 0; i < teams.size(); i++)
	{
		Team team = teams[i];
		file.write(reinterpret_cast<char*>(&team), sizeof(Team));
	}
	file.close();
}

//function for delete team manage file
void updateTeamManagerFile(vector<TeamManager>& teamManagers)
{
	ofstream file(teamManagerFile, ios::binary);
	file.clear();
	for (int i = 0; i < teamManagers.size(); i++)
	{
		TeamManager teamManager = teamManagers[i];
		file.write(reinterpret_cast<char*>(&teamManager), sizeof(TeamManager));
	}
	file.close();
}

//function for find team by team manager
int findTeamByTeamManager(vector<Team>& const teams, string name)
{
	int size = teams.size();
	for (int i = 0; i < size; i++)
	{
		if (teams[i].getManagerName() == name)
			return i;
	}
	return -1;
}

//function for check the file is empty or not
bool isFileEmpty(string);

//function for initialize files of each class
void initFiles(vector <LeagueManager>&, vector <TeamManager>&,
	vector<Coach>&, vector<Player>&, vector<Team>&, vector<Request>&);

//function for  check username of teammanager before submit not be duplicated
bool isTmUserNameExist(string,vector<TeamManager>&const);

//function for  check username of coach before submit not be duplicated
bool isCoachUserNameExist(string userName,vector<Coach>&const coaches)
{
	for (int i = 0; i < coaches.size(); i++)
		if (coaches[i].getUsername() == userName)
			return true;

	return false;
}

//function for edit coach file base on vector
void updateCoachFile(vector<Coach>& coaches)
{
	ofstream file(coachFile, ios::binary);
	file.clear();
	for (int i = 0; i < coaches.size(); i++)
	{
		Coach coach = coaches[i];
		file.write(reinterpret_cast<char*>(&coach), sizeof(Coach));
	}
	file.close();
}

//function for check player username not be duplicate
bool isPluserNameExist(string userName, vector<Player>&const players)
{
	for (int i = 0; i < players.size(); i++)
		if (players[i].getUsername() == userName)
			return true;
	return false;
}

//function for check the team is exist or not
int isTeamNameExist(string name,vector<Team>&const teams) 
{
	int size = teams.size();
	
	for (int i = 0; i < size; i++)
	{
		if (teams[i].getTeamName() == name)
			return i;
	}

	return -1;
}

TeamManager inputTeamManager(vector<TeamManager>teamManagers)
{
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
		if (!isTmUserNameExist(userName, teamManagers))
			break;
		else
			cout << "plz select another one it`s exist!!\n";
	}
	cout << "plz enter password:\t";
	getline(cin, password);

	TeamManager tm(userName, password, firstName, lastName);

	return tm;
}

Coach inputCoach(vector<Coach>&const coaches)
{
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

	Coach coach(userName, password, firstName, lastName);

	return coach;
}

Team inputTeam(vector<Team>& teams, vector<Coach>& coaches)
{
	string teamName;
	cout << "enter team name:\t";
	getline(cin, teamName);

	while (true)
	{
		if (isTeamNameExist(teamName, teams) == -1)
			break;
		else
			cout << "team is already exist!\n";

		getline(cin, teamName);

	}

	cout << "enter team budget:\t";
	int budget;
	cin >> budget;

	Coach coach = inputCoach(coaches);

	Team team;
	team.setCoachName(coach.getFirstName() + coach.getLastName());
	team.setTeamName(teamName);
	team.setBudget(budget);

	coach.setTeam(team);
	coaches.push_back(coach);
	updateCoachFile(coaches);

	return team;
}

//function for sign up team manager
void signUpTeamManager(vector<TeamManager>& teamManagers , vector<Team>&teams , vector<Coach>&coaches)
{
	cin.clear();
	cin.ignore();

	//get the team manager info

	TeamManager teamManager=inputTeamManager(teamManagers);
	teamManagers.push_back(teamManager);
	ofstream file(teamManagerFile, ios::binary | ios::app);
	file.write(reinterpret_cast<const char*>(&teamManager), sizeof(TeamManager));
	file.close();

	//get the team info
	Team team = inputTeam(teams, coaches);
	team.setManagerName(teamManager.getFirstName() + teamManager.getLastName());
	teams.push_back(team);
	updateTeamFile(teams);

	cout << "team and team manager sucessfully added!\n";
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
	Team team;
	
	//show list of team for submit
	cout << "\nlist of teams available:\n";
	for (int i = 0; i < teams.size(); i++)
	{
		cout << i + 1 << "- " << teams[i].getTeamName() << endl;
	}
	int opt;
	cout << "plz enter team number:\t";
	cin >> opt;
	team = teams[opt - 1];

	Coach coach(userName,password,firstName,lastName,team);
	coaches.push_back(coach);
	ofstream file(coachFile, ios::app | ios::binary);
	file.write(reinterpret_cast<char*>(&coach), sizeof(Coach));
	file.close();
}

//function for delete coach
void deleteCoach(vector<Coach>& coaches)
{
	if (coaches.size() == 0)
	{
		cout << "no coach submited!!\n";
		return;
	}
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

//function for add new player
void addPlayer(vector<Player>& players)
{
	string firstName, lastName, userName, password,role;
	double salary, stock;

	cin.clear();
	cin.ignore();

	cout << "enter first name:\t";
	getline(cin, firstName);

	cout << "enter last name:\t";
	getline(cin, lastName);
	//check user name not be duplicated
	while (true)
	{
		cout << "enter user name:\t";
		getline(cin, userName);
		if (!isPluserNameExist(userName, players))
			break;
		else
			cout << "plz select another one it`s exist!!\n";
	}
	cout << "plz enter password:\t";
	getline(cin, password);

	cout << "plz enter player role:\t";
	getline(cin, role);

	cout << "plz enter player salary:\t";
	cin >> salary;

	cout << "plz enter player stock:\t";
	cin >> stock;

	Player player(userName, password, firstName, lastName,role, salary, stock, 0);
	players.push_back(player);
	ofstream file(playerFile,ios::binary | ios::app);
	file.write(reinterpret_cast<char*>(&player), sizeof(Player));
	file.close();

}

//function for update players file
void updatePlayerFile(vector<Player>& players)
{
	ofstream file(playerFile, ios::binary);
	file.clear();
	for (int i = 0; i < players.size(); i++)
	{
		Player player = players[i];
		file.write(reinterpret_cast<char*>(&player), sizeof(Player));
	}
	file.close();
}

//function for delete player
void deletePlayer(vector<Player>& players)
{
	if (players.size() == 0)
	{
		cout << "no player exist!!!!\n";
		return;
	}
	cout << "players list select player want to delete\n";
	for (int i = 0; i < players.size(); i++)
	{
		cout << i + 1 << "-  " << players[i].getUsername() << endl;
	}
	cout << "enter number:\t";
	int opt;
	cin >> opt;
	players.erase(players.begin() + (opt-1));
	updatePlayerFile(players);
	cout << "player deleted\n";
}

//function for delete team
void deleteTeam(vector<Team>& teams)
{
	if (teams.size() == 0)
	{
		cout << "no team exist!!!!\n";
		return;
	}
	cout << "teams list select team want to delete\n";
	for (int i = 0; i < teams.size(); i++)
	{
		cout << i + 1 << "-  " << teams[i].getTeamName() << endl;
	}
	cout << "enter number:\t";
	int opt;
	cin >> opt;
	teams.erase(teams.begin() + (opt - 1));
	updateTeamFile(teams);
	cout << "team deleted\n";
}

//function for edit coach first name
void editCoachFirstName(vector<Coach>& coaches,int index)
{
	string name;
	cout << "plz enter new name:\t";
	cin.clear();
	cin.ignore();
	getline(cin, name);
	coaches[index].setFirstName(name);
}

//function for edit coach last name
void editCoachLastName(vector<Coach>& coaches, int index) 
{
	string name;
	cout << "plz enter new name:\t";
	cin.clear();
	cin.ignore();
	getline(cin, name);
	coaches[index].setLastName(name);
}

//function for edit coah team
void editCoachTeam(vector<Coach>& coaches, vector<Team>& teams, int index)
{

	cout << "teams list\t select new team of coach\n";
	for (int i = 0; i < teams.size(); i++)
	{
		cout << i + 1 << "-  " << teams[i].getTeamName() << endl;
	}
	cout << "enter number:\t";
	int opt;
	cin >> opt;
	coaches[index].setTeam(teams[opt - 1]);
}

//function for edit coach
void editCoach(vector<Coach>& coaches, vector<Team>& teams)
{
	if (coaches.size() == 0)
	{
		cout << "no coach exist for edit!!\n";
		return;
	}
	cout << "list of coaches userName:\n";
	for (int i = 0; i < coaches.size(); i++)
	{
		cout << i + 1 << "- " << coaches[i].getUsername() << endl;
	}
	cout << "enter coach number:\t";
	
	int index;
	cin >> index;
	cout << "userName and password cant be changed\n1-firstName\n2-lastName\n3-team\nselect item for edit:\t";
	int opt;
	cin >> opt;
	switch (opt)
	{
	case 1:
		editCoachFirstName(coaches, index-1);
		break;
	case 2:
		editCoachLastName(coaches, index-1);
		break;
	case 3:
		editCoachTeam(coaches, teams,index-1);
		break;
	default:
		break;
	}
	updateCoachFile(coaches);


}

//function for  login and do activity team manager
void logInTeamManager(vector<TeamManager>& teamManagers, vector<Team>& teams, vector<Coach>& coaches, vector<Player>& players)
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
		cout << "1-add coach\n2-delete coach\n3-edit coach\n4-delete team\n5-add player\n6-delete player\nselect option:\t";
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
				editCoach(coaches,teams);
				break;
			case 4:
				deleteTeam(teams);
				break;
			case 5:
				addPlayer(players);
				break;
			case 6:
				deletePlayer(players);
				break;
			default:
				cout << "invalid option!\n";
				break;
		}
	}

}

//function for show team manager menu
void teamManagerMenu(vector<TeamManager>& teamManagers, vector<Team>& teams, vector<Coach>& coaches, vector<Player>& players)
{
	cout << "1-logIn\n2-i`m new(sign up)\n3-exit\nenter option:\t";
	int opt;
	cin >> opt;
	switch (opt)
	{
		case 1:
			logInTeamManager(teamManagers,teams,coaches,players);
			break;
		case 2:
			signUpTeamManager(teamManagers,teams,coaches);
			break;
		default:
			cout << "\ninvalid option!\n\n";
			break;
	}

}

//fuction for check coach with user and pass exist or not
int isCoachExist(string userName, string password, vector<Coach>& coaches)
{
	for (int i = 0; i < coaches.size(); i++)
		if (coaches[i].getUsername() == userName && coaches[i].getPassword() == password)
			return i;
	return -1;
}

//function for sign in coach and do activity
void logInCoach(vector<Team>& teams, vector<Coach>& coaches, vector<Player>& players)
{
	cin.clear();
	cin.ignore();
	string userName,password;
	cout << "plz enter username:\t";
	getline(cin, userName);

	cout << "plz enter password:\t";
	getline(cin, password);

	int coachIndex = isCoachExist(userName, password, coaches);

	if (coachIndex !=-1)
	{
		if (players.size() == 0)
		{
			cout << "we dont have player\n";
			return;
		}

		//check team free space
		for (int i = 0; i < teams.size(); i++)
		{
			if (teams[i].getTeamName() == coaches[coachIndex].getTeam().getTeamName())
			{
				cout << "count of player in team(maximum:22)-->\t" << teams[i].getPlayerCount()<<endl;
			}
		}

		cout << "list of players(select free agent player)\n";
		for (int i = 0; i < players.size(); i++)
		{
			cout << i + 1 << "- " << players[i].getFirstName() << "  " << players[i].getLastName() << "\t" << players[i].getTeamName() << endl;
		}
		int index;
		cout << "plz enter player number:\t";
		cin >> index;
		players[index - 1].setTeamName(coaches[coachIndex].getTeam().getTeamName());
		updatePlayerFile(players);
	}
	else
	{
		cout << "user/pass input invalid\n";
	}

}

//function for show coach menu
void coachMenu(vector<Team>& teams, vector<Coach>& coaches, vector<Player>& players)
{
	cout << "1-logIn\n2-i`m new(sign up)\nenter option:\t";
	int opt;
	cin >> opt;
	switch (opt)
	{
	case 1:
		logInCoach(teams, coaches, players);
		break;
	case 2:
		signUpCoach(coaches,teams);
		break;
	default:
		break;
	}
}

//function for delete team manager
void deleteTeamManager(vector<TeamManager>& teamManagers , 
	vector<Team>&teams , vector<Coach>&coaches)
{
	if (teamManagers.size() == 0)
	{
		cout << "no team manager submited\n";
		return;
	}
	cout << "team manager list select manager want to delete\n";
	for (int i = 0; i < teamManagers.size(); i++)
	{
		cout << i + 1 << "-  " << teamManagers[i].getUsername() << endl;
	}
	cout << "enter number:\t";
	int opt;
	cin >> opt;
	string teamManagerName = teamManagers[opt - 1].getFirstName() +
		teamManagers[opt - 1].getLastName();
	int teamIndex = findTeamByTeamManager(teams,teamManagerName);
	int coachIndex = findCoachByTeamName(coaches, teams[teamIndex].getTeamName());
	
	teams.erase(teams.begin() + teamIndex);
	coaches.erase(coaches.begin() + coachIndex);
	teamManagers.erase(teamManagers.begin() + (opt - 1));
	updateTeamManagerFile(teamManagers);
	updateTeamFile(teams);
	updateCoachFile(coaches);

	cout << "team manager deleted\n";

}

//functio for edit team manager first name
void editTeamManagerFirstName(vector<TeamManager>& teamManagers, int index)
{
	string name;
	cout << "plz enter new name:\t";
	cin.clear();
	cin.ignore();
	getline(cin, name);
	teamManagers[index].setFirstName(name);
}

//function for edit team manager last name
void editTeamManagerLastName(vector<TeamManager>& teamManagers, int index)
{
	string name;
	cout << "plz enter new name:\t";
	cin.clear();
	cin.ignore();
	getline(cin, name);
	teamManagers[index].setLastName(name);
}

//function for edit team manager info
void editTeamManager(vector<TeamManager>& teamManagers)
{

	if (teamManagers.size() == 0)
	{
		cout << "no team manager exist for edit!!\n";
		return;
	}

	cout << "list of team managers userName:\n";
	for (int i = 0; i < teamManagers.size(); i++)
	{
		cout << i + 1 << "- " << teamManagers[i].getUsername() << endl;
	}

	cout << "enter team manager number:\t";

	int index;
	cin >> index;
	cout << "userName and password cant be changed\n1-firstName\n2-lastName\nselect item for edit:\t";
	int opt;
	cin >> opt;
	switch (opt)
	{
	case 1:
		editTeamManagerFirstName(teamManagers, index-1);
		break;
	case 2:
		editTeamManagerLastName(teamManagers, index);
		break;
	default:
		cout << "invalid option!\n";
		break;
	}
	updateTeamManagerFile(teamManagers);

}

//function for set team play random
void buildTeamIndexRandom(int& indexTeamOne,int& indexTeamTwo,int size)
{
	srand(time(0));
	while (true)
	{
		indexTeamOne = rand() % size;
		indexTeamTwo = rand() % size;
		if (indexTeamOne != indexTeamTwo)
			break;
	}
}

//function for set teams goal and player goal
void setTeamsAndPlayersGoal(int& goalTeamOne, int& goalTeamTwo,Player playerTeam1,Player playerTeam2, vector<Player>& players)
{
	srand(time(0));
	goalTeamOne = rand() % 5;
	goalTeamTwo = rand() % 5;

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].getUsername() == playerTeam1.getUsername())
			players[i].increaseGoal(goalTeamOne);
		if (players[i].getUsername() == playerTeam2.getUsername())
			players[i].increaseGoal(goalTeamTwo);
	}

}

//function for start match 
void startGame(vector<Team>& teams, vector<Player>& players)
{
	//check each team have 5 player atleast
	for (int i = 0; i < teams.size(); i++)
	{
		if (teams[i].getPlayerCount() < 5)
		{
			cout << "sorry team " << teams[i].getTeamName() << " dosn`t have minimum of player\n";
			return;
		}
	}
	//tedad hafte haye ma yeki kamtar az tedad team hast
	for (int i = 0; i < teams.size() - 1; i++)
	{
		cout << "\n                  WEEK " << i + 1 << " Game\n";
		int indexTeamOne, indexTeamTwo,goalTeamOne,goalTeamTwo;
		buildTeamIndexRandom(indexTeamOne, indexTeamTwo, teams.size());
		setTeamsAndPlayersGoal(goalTeamOne, goalTeamTwo,teams[indexTeamOne].getPlayer(2),teams[indexTeamTwo].getPlayer(3),players);
		
		cout << "MATCH:\t" << teams[indexTeamOne].getTeamName() << " " << goalTeamOne;
		cout << "  -  " << goalTeamTwo << " " << teams[indexTeamTwo].getTeamName() << endl;
		
		if (goalTeamOne > goalTeamTwo)
			teams[indexTeamOne].increaseScore(3);
		else if(goalTeamOne < goalTeamTwo)
			teams[indexTeamTwo].increaseScore(3);
		else
		{
			teams[indexTeamOne].increaseScore(1);
			teams[indexTeamTwo].increaseScore(1);
		}
		updatePlayerFile(players);
		updateTeamFile(teams);
	}

}


//function for show league manager menu
void leagueManagarMenu(vector<TeamManager>& teamManagers, vector<Team>& teams, vector<Coach>& coaches, vector<Player>& players)
{
	string userName, password;
	cout << "plz enter user name:\t";
	cin.clear();
	cin.ignore();
	getline(cin, userName);
	cout << "plz enter password:\t";
	getline(cin, password);

	if (userName == "azizikhadem" && password == "1234")
	{
		cout << "1-start Game\n2-add team & team manager\n3-delete team & team manager\n4-edit team & team manager\nenter option:\t";
		int opt;
		cin >> opt;
		switch (opt)
		{
			case 1:
				startGame(teams, players);
				break;
			case 2:
				signUpTeamManager(teamManagers,teams,coaches);
				break;
			case 3:
				deleteTeamManager(teamManagers, teams, coaches);
				break;
			case 4:
				editTeamManager(teamManagers);
				break;
			default:
				cout << "\ninvalid option!\n\n";
				break;
		}
	}
	else
		cout << "usernam/password input invalid\n";

}

// A function to implement bubble sort 
void playerSortBaseGoal(vector<Player>& players)
{
	int i, j;
	for (i = 0; i < players.size() - 1; i++)
	{
		for (j = 0; j < players.size() - i - 1; j++)
		{
			if (players[j].getGoals() < players[j + 1].getGoals())
			{
				Player test = players[j];
				players[j] = players[j + 1];
				players[j + 1] = test;

			}
		}
	}

	//update binary file after sort
	updatePlayerFile(players);
}

//function for show top player at league
void topPlayersList(vector<Player>& players)
{

	if (players.size() == 0)
	{
		cout << "no player submited!!\n";
		return;
	}
	//before show should be sorted
	playerSortBaseGoal(players);

	cout << "----------top player list--------\n";
	for (int i = 0; i < players.size(); i++)
	{
		cout <<i+1<<"- " << players[i].getFirstName() << "\t" << players[i].getLastName() << "\t" << players[i].getGoals() << endl;
	}
}

//function for sort teams of league base goals
void teamsSortBaseScore(vector<Team>& teams)
{
	int i, j;
	for (i = 0; i < teams.size() - 1; i++)
	{
		for (j = 0; j < teams.size() - i - 1; j++)
		{
			if (teams[j].getScore() < teams[j + 1].getScore())
			{
				Team test = teams[j];
				teams[j] = teams[j + 1];
				teams[j + 1] = test;

			}
		}
	}

	//update binary file after sort
	updateTeamFile(teams);
}

//function for show leagueTable base score
void showLeagueTable(vector<Team>& teams)
{
	if (teams.size() == 0)
	{
		cout << "no team submited!!\n";
		return;
	}
	//sort teames in table
	teamsSortBaseScore(teams);

	//show teams
	for (int i = 0; i < teams.size(); i++)
	{
		cout << i + 1 << "- " << teams[i].getTeamName() << "\t" << teams[i].getScore() << endl;
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
		cout << "1-teamManager menu\n2-Coach menu\n3-leagueManager\n4-top player\n5-league table\n" <<
			"6-exit\nenter option:\t";

		int opt;
		cin >> opt;
		switch (opt)
		{
			case 1:
				teamManagerMenu(teamManagers,teams,coaches,players);
				break;
			case 2:
				coachMenu(teams,coaches,players);
				break;
			case 3:
				leagueManagarMenu(teamManagers, teams, coaches, players);
				break;
			case 4:
				topPlayersList(players);
				break;
			case 5:
				showLeagueTable(teams);
				break;
			case 6:
				exit(0);
			default:
				cout << "\ninvalid choose!\n\n";
				break;
		}

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

bool isTmUserNameExist(string userName, vector<TeamManager>&const teamManagers)
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