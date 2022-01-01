#pragma once
#include <string>
using namespace std;

//////////// User class ////////////

class User
{
protected:
	char username[30];
	char password[30];
	char firstName[30];
	char lastName[30];
public:
	User() {}
	User(string, string, string, string);

	void setUsername(string);
	string getUsername();

	void setPassword(string);
	string getPassword();

	void setFirstName(string);
	string getFirstName();

	void setLastName(string);
	string getLastName();
};

//////////// User class end ////////////

//////////// LeagueManager class end ////////////

class LeagueManager :public User
{
	//empty class
};

//////////// LeagueManager class end ////////////

//////////// Role class ////////////

class Role
{
private:
	char role[30];
public:
	void setRole(string);
	string getRole();
};

//////////// Role class end ////////////

//////////// Player class ////////////

class Request;

class Player :public User
{
private:
	Role role;
	double salary;
	double stock;
	int goals;
	Request requestBox[30];
	int requestCounter;
public:
	Player();
	Player(string, string, string, string, string, double, double, int);
	void setRole(string);
	Role getRole();

	void setSalary(double);
	double getSalary();

	void setStock(double);
	double getStock();

	void setGoals(int);
	int getGoals();

	void addRequst(Request);
	Request getRequest(int);
};

//////////// Player class end ////////////

//////////// Team class ////////////

class Team
{
private:
	char managerTeamName[30];
	char coachName[30];
	Player players[22];
	int playersCounter;

	int score;
	double budget;
public:
	Team();
	Team(string, string);
	bool haveCapacity();

	void setManagerName(string);
	string getManagerName();

	void setCoachName(string);
	string getCoachName();

	void addPlayer(Player);
	Player getPlayer(int);

	void setScore(int);
	int getScore();

	void setBudget(double);
	double getBudget();
};

//////////// Team class end ////////////

//////////// Coach class ////////////

class Coach :public User
{
private:
	Team team;
public:
	Coach() {}
	Coach(string, string, string, string, Team);

	void setTeam(Team);
	Team getTeam();
};

//////////// Coach class end ////////////

//////////// Request class ////////////

class Request
{
private:
	Player requestedPlayer;
	char text[100];
	Team sender;
	char status[100];
public:
	Request() {}
	Request(Team, string, Player, string);

	void setRequstedPlayer(Player);
	Player getRequstedPlayer();

	void setText(string);
	string getText();

	void setSatus(string);
	string getStatus();

	void setSender(Team);
	Team getSender();
};

//////////// Request class end ////////////

//////////// Game class ////////////

class Game
{
private:
	Team team1, team2;
	int scoreTeam1, scoreTeam2;
	int winner; //1 or 2
public:
	Game() {}
	Game(Team, Team, int, int, int);

	void setTeams(Team, Team);
	Team getTeamOne();
	Team getTeamTwo();

	void setScores(int, int);
	int getScoreTeamOne();
	int getScoreTeamTwo();

	void setWinner(int);
	int getWinner();
};

//////////// Game class end ////////////

//////////// TeamManager class end ////////////

class TeamManager :public User
{
private:
	Role role;
	Request sendedRequests[30];
	int sendedRequestCounter;
	Request deliveredRequests[30];
	int deliveredRequestCounter;

public:
	TeamManager();
	TeamManager(string, string, string, string);

	Role getRole();

	void sendRequest(Request);
	Request getSendedRequest(int);

	void deliverRequest(Request);
	Request getDeliveredRequest(int);
};

//////////// TeamManager class end ////////////