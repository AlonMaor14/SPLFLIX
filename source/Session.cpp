#include "../include/Session.h"
#include "..\include\User.h"
#include "..\include\Watchable.h"
#include "..\include\Action.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using namespace std;
using json = json;


void Session::jsonScanner(const std::string& configFilePath)
{
	std::ifstream fileReader(configFilePath);
	json j;
	fileReader >> j;
	string convertionFromJson = j.dump(); //// explicit conversion to string
	fileReader.close();
	int id = 1;
	for (auto& movie : j["movies"].items()) {//iterator on movies
		string nameOfMovie = movie.value()["name"];
		int lengthOfMovie = movie.value()["length"];
		vector<string> tagsVectorOfMovie;
		for (auto tag:movie.value()["tags"]){
			tagsVectorOfMovie.push_back(tag.value());
		}
		Watchable* newMovie = new Movie(id, nameOfMovie, lengthOfMovie, tagsVectorOfMovie);
		this->getContent().push_back(newMovie);
		id++;
	}
	for (auto& tvShow : j["tv_series"].items()) {//iterator on tv shows
		string nameOfTvShow = tvShow.value()["name"];
		int lengthOfTvShow = tvShow.value()["length"];
		int numOfSeason = 1;
		vector<string> tagsVectorOfTvShow;
		for (auto tag : tvShow.value()["tags"]) {//iterator on tags of tv show
			tagsVectorOfTvShow.push_back(tag.value());
		}
		int totalNumOfSeasons = j["seasons"].size();
		int numberOfEpisodes;
		for (auto& seasonNumber : tvShow.value()["seasons"].items()) {
			numberOfEpisodes = seasonNumber.value();
			for (int currEpisode = 1; currEpisode <= numberOfEpisodes; currEpisode++) {//goes throw the episodes
				Episode* newTvShow = new Episode(id, nameOfTvShow, numOfSeason, currEpisode, lengthOfTvShow, tagsVectorOfTvShow);//Check Why Episode Declaration only works
				if (currEpisode==numberOfEpisodes && numOfSeason < totalNumOfSeasons) {//if last episode of the season
					numOfSeason++;
				}
				newTvShow->setNextEpisodeId(id + 1);	
				this->getContent().push_back(newTvShow);
				id++;//if number of episodes is 0 than problem(id never changes)
			}
		}
		
	}
}

Session::Session(const std::string& configFilePath) {
	jsonScanner(configFilePath);
	
	
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
