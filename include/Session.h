#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include "json.hpp";

class User;
class Watchable;

class Session{
public:
	void Session::jsonScanner(const std::string& configFilePath);
    Session(const std::string &configFilePath);
    ~Session();
    void start();
	std::vector<Watchable*> getContent();
	User* getActiveUser();
	std::vector<BaseAction*> getActionsLog();
	std::unordered_map<std::string, User*> getUserMap();
	void setActiveUser(User* u);
	std::string getCommand();



private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
	string command;
};
#endif