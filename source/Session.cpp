#include "..\include\Session.h"
#include "..\include\User.h"
#include "..\include\Watchable.h"
#include "..\include\Action.h"
#include <fstream>
using namespace std;


Session::Session(const std::string& configFilePath) {
	
}

Session::~Session() {

}
string Session::getCommand() {
	return command;
}

void Session::start() {
	cout << "SPLFLIX is now on!\n";
	activeUser = new LengthRecommenderUser("default");
	CreateUser createUser = CreateUser();
	ChangeActiveUser changeActiveUser = ChangeActiveUser();
	DeleteUser deleteUser = DeleteUser();
	DuplicateUser duplicateUser = DuplicateUser();
	PrintContentList printContentList = PrintContentList();
	PrintWatchHistory printWatchHistory = PrintWatchHistory();
	Watch watch = Watch();
	PrintActionsLog printsActionLog=PrintActionsLog()

	cin >> command;
	
	while (!command._Equal("exit")) {
		string firstWord = command.substr(0, command.find(" "));
		if (firstWord._Equal("createuser")) {
			createUser.act(*this);
		}
		else if (firstWord._Equal("changeuser")) {
			changeActiveUser.act(*this);
		}
		else if (firstWord._Equal("deleteuser")) {
			deleteUser.act(*this);
		}
		else if (firstWord._Equal("dupuser")) {
			duplicateUser.act(*this);
		}
		else if (firstWord._Equal("content")) {
			printContentList.act(*this);
		}
		else if (firstWord._Equal("watchhist")) {
			printWatchHistory.act(*this);
		}
		else if (firstWord._Equal("watch")) {
			watch.act(*this);
		}
		else if (firstWord._Equal("log")) {
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
