#include "../include/Session.h"
#include "..\include\User.h"
#include "..\include\Watchable.h"
#include "..\include\Action.h"
#include "../include/jser.h"
#include <iostream>
#include <fstream>
using namespace std;
using json = json;


Session::Session(const std::string& configFilePath) {

	std::ifstream i(configFilePath);
	json j;
	i >> j;
	
}

Session::~Session() {

}
string Session::getCommand() {
	return command;
}

void Session::start() {
	cout << "SPLFLIX is now on!\n";
	activeUser = new LengthRecommenderUser("default");
	
	cin >> command;
	
	while (!command._Equal("exit")) {
		string firstWord = command.substr(0, command.find(" "));
		if (firstWord._Equal("createuser")) {
			CreateUser createUser = CreateUser();
			createUser.act(*this);
		}
		else if (firstWord._Equal("changeuser")) {
			ChangeActiveUser changeActiveUser = ChangeActiveUser();
			changeActiveUser.act(*this);
		}
		else if (firstWord._Equal("deleteuser")) {
			DeleteUser deleteUser = DeleteUser();
			deleteUser.act(*this);
		}
		else if (firstWord._Equal("dupuser")) {
			DuplicateUser duplicateUser = DuplicateUser();
			duplicateUser.act(*this);
		}
		else if (firstWord._Equal("content")) {
			PrintContentList printContentList = PrintContentList();
			printContentList.act(*this);
		}
		else if (firstWord._Equal("watchhist")) {
			PrintWatchHistory printWatchHistory = PrintWatchHistory();
			printWatchHistory.act(*this);
		}
		else if (firstWord._Equal("watch")) {
			Watch watch = Watch();
			watch.act(*this);
		}
		else if (firstWord._Equal("log")) {
			PrintActionsLog printsActionLog = PrintActionsLog();
			printsActionLog.act(*this);
		}
	}
	
	
}

std::vector<Watchable*> Session::getContent() {
	return content;
}

User* Session::getActiveUser()
{
	return activeUser;
}

std::vector<BaseAction*> Session::getActionsLog()
{
	return actionsLog;
}

std::unordered_map<std::string, User*> Session::getUserMap()
{
	return userMap;
}

void Session::setActiveUser(User* u) {
	activeUser = u;
}
