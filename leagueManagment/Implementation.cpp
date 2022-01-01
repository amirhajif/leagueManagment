#include "Classes.h"
#include <iostream>
////// User class functions //////

User::User(string username, string password, string firstname, string lastname)
{
	this->setFirstName(firstname);
	this->setLastName(lastname);
	this->setPassword(password);
	this->setUsername(username);
}

void User::setUsername(string data)
{
	memcpy(this->username, data.c_str(), 30);
}

string User::getUsername()
{
	string value(username);

	return value;
}

void User::setPassword(string data)
{
	memcpy(this->password, data.c_str(), 30);
}

string User::getPassword()
{
	string value(password);

	return value;
}

void User::setFirstName(string data)
{
	memcpy(this->firstName, data.c_str(), 30);
}

string User::getFirstName()
{
	string value(firstName);

	return value;
}

void User::setLastName(string data)
{
	memcpy(this->lastName, data.c_str(), 30);
}

string User::getLastName()
{
	string value(lastName);

	return value;
}

////// User class functions end //////

////// Role class functions //////

void Role::setRole(string data)
{
	memcpy(this->role, data.c_str(), 30);
}

string Role::getRole()
{
	string value(role);

	return value;
}

////// Role class functions end //////

////// Player class functions //////

Player::Player()
{
	requestBox = new Request[30];
	requestCounter = 0;
}

Player::Player(string username, string password, string firstname, string lastname,
	string role, double salary, double stock, int goals)
	:User(username, password, firstname, lastname)
{
	requestBox = new Request[30];

	requestCounter = 0;

	this->setRole(role);
	this->setGoals(goals);
	this->setSalary(salary);
	this->setStock(stock);

}

void Player::setRole(string data)
{
	role.setRole(data);
}

Role Player::getRole()
{
	return role;
}

void Player::setSalary(double data)
{
	salary = data;
}

double Player::getSalary()
{
	return salary;
}

void Player::setStock(double data)
{
	stock = data;
}

double Player::getStock()
{
	return stock;
}

void Player::setGoals(int data)
{
	goals = data;
}

int Player::getGoals()
{
	return goals;
}

void Player::addRequst(Request request)
{
	if (requestCounter < 30)
	{
		requestBox[requestCounter] = request;
		requestCounter++;
	}
	else
		return;
}

Request Player::getRequest(int index)
{
	return requestBox[index];
}

////// Player class functions end //////

////// Team  class functions //////

Team::Team()
{
	playersCounter = 0;
}

Team::Team(string managerName, string coachName)
{
	this->setCoachName(coachName);
	this->setManagerName(managerName);
}

bool Team::haveCapacity()
{
	return playersCounter < 22;
}

void Team::setManagerName(string data)
{
	memcpy(this->managerTeamName, data.c_str(), 30);
}

string Team::getManagerName()
{
	string value(managerTeamName);

	return value;
}

void Team::setCoachName(string data)
{
	memcpy(this->coachName, data.c_str(), 30);
}

string Team::getCoachName()
{
	string value(coachName);

	return value;
}

void Team::addPlayer(Player data)
{
	if (haveCapacity())
	{
		players[playersCounter] = data;

		playersCounter++;
	}
}

Player Team::getPlayer(int index)
{
	return players[index];
}

void Team::setScore(int data)
{
	score = data;
}

int Team::getScore()
{
	return score;
}

void Team::setBudget(double data)
{
	budget = data;
}

double Team::getBudget()
{
	return budget;
}

////// Team class functions end //////

////// Coach class functions //////

Coach::Coach(string username, string password, string firstname,
	string lastname, Team team)
	:User(username, password, firstname, lastname)
{
	this->setTeam(team);
}

void Coach::setTeam(Team team)
{
	this->team = team;
}

Team Coach::getTeam()
{
	return team;
}

////// Coach class functions end //////

////// Request class functions //////

Request::Request(Team* sender, string text, Player* player, string status)
{
	this->setRequstedPlayer(player);
	this->setSatus(status);
	this->setSender(sender);
	this->setText(text);
}

void Request::setRequstedPlayer(Player* data)
{
	this->requestedPlayer = data;
}

Player Request::getRequstedPlayer()
{
	return *requestedPlayer;
}

void Request::setText(string data)
{
	memcpy(this->text, data.c_str(), 100);
}

string Request::getText()
{
	string value(text);

	return value;
}

void Request::setSatus(string data)
{
	memcpy(this->status, data.c_str(), 100);
}

string Request::getStatus()
{
	string value(status);

	return value;
}

void Request::setSender(Team* team)
{
	this->sender = team;
}
Team Request::getSender()
{
	return *sender;
}

////// Request class functions end //////

////// Game class functions //////

Game::Game(Team team1, Team team2, int scoreTeam1, int scoreTeam2, int winner)
{
	this->setTeams(team1, team2);
	this->setScores(scoreTeam1, scoreTeam2);
	this->setWinner(winner);
}

void Game::setTeams(Team team1, Team team2)
{
	this->team1 = team1;
	this->team2 = team2;
}
Team Game::getTeamOne()
{
	return team1;
}
Team Game::getTeamTwo()
{
	return team2;
}

void Game::setScores(int score1, int score2)
{
	this->scoreTeam1 = score1;
	this->scoreTeam2 = score2;
}
int Game::getScoreTeamOne()
{
	return scoreTeam1;
}
int Game::getScoreTeamTwo()
{
	return scoreTeam2;
}

void Game::setWinner(int data)
{
	this->winner = data;
}
int Game::getWinner()
{
	return winner;
}

////// Game class functions end //////

////// TeamManager class functions //////

TeamManager::TeamManager()
{
	role.setRole("team manager");
	sendedRequestCounter = 0;
	deliveredRequestCounter = 0;
}

TeamManager::TeamManager(string username, string password,
	string firstname, string lastname)
{
	sendedRequestCounter = 0;
	deliveredRequestCounter = 0;

	this->setFirstName(firstname);
	this->setLastName(lastname);
	this->setPassword(password);
	this->setUsername(username);

	role.setRole("team manager");
}

Role TeamManager::getRole()
{
	return role;
}

void TeamManager::sendRequest(Request request)
{
	if (sendedRequestCounter < 30)
	{
		sendedRequests[sendedRequestCounter] = request;
		sendedRequestCounter++;
	}
	else
		return;
}

Request TeamManager::getSendedRequest(int index)
{
	return sendedRequests[index];
}

void TeamManager::deliverRequest(Request request)
{
	if (deliveredRequestCounter < 30)
	{
		deliveredRequests[sendedRequestCounter] = request;
		deliveredRequestCounter++;
	}
	else
		return;
}

Request TeamManager::getDeliveredRequest(int index)
{
	return deliveredRequests[index];
}

////// TeamManager class functions end //////