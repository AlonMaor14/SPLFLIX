#include "../Include/User.h"
#include "../Include/Watchable.h"
#include "../include/Session.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Movie;
class Episode;
class Session;
using namespace std;

User::User(const std::string& name) :name(name) {
}; //constructor

User::User(User& other) :name(other.name) {
}; //copy constructor



std::string User::getName() const {
	return name;
}

std::vector<Watchable*> User::get_history() const {
	return history;
}

bool User::isInHistory(Watchable& content) {
	return find(history.begin(), history.end(), content) != history.end();
}

int User::calculateAverageLength(std::vector<Watchable*> history) {
	int sum = 0;
	int counter = 0;
	for ( int i = 0; i != history.size(); i++) {
		sum = sum + history.at(i)->getLength();
		counter++;
	}
	return sum / counter;
}

LengthRecommenderUser::LengthRecommenderUser(const std::string& name) : User(name) {

}

Watchable* LengthRecommenderUser::getRecommendation(Session& s) {
	Watchable* toRecommend = history.back()->getNextWatchable(s);
	
	if (toRecommend != nullptr)
		return toRecommend;
	else {
		int averageLength = calculateAverageLength(history);
		int indexPosition = 0;

		int minAbsLength = abs(s.getContent().at(indexPosition)->getLength() - averageLength);
		for (int i = 1; i != s.getContent().size(); i++) {
			if (!isInHistory(*s.getContent()[i]) && minAbsLength > abs(s.getContent()[i]->getLength() - averageLength)){ 
				indexPosition = i;
				minAbsLength = abs(s.getContent()[i]->getLength() - averageLength);
			}
		}
		return s.getContent()[indexPosition];
	}
};

RerunRecommenderUser::RerunRecommenderUser(const std::string& name) : User(name) {
	i=0;
}

Watchable* RerunRecommenderUser::getRecommendation(Session& s) {
	Watchable * toRecommend = history.back()->getNextWatchable(s);
	if (toRecommend != nullptr)
		return toRecommend;
	else {
		toRecommend = history[i];
		if (i < history.size())
			i++;
		else
			i = 0;
		return toRecommend;
	}
}

GenreRecommenderUser::GenreRecommenderUser(const std::string& name) : User(name) {

}

Watchable* GenreRecommenderUser::getRecommendation(Session& s) {
	Watchable* last = history.back();
	std::vector<string> tags = last->getTags();
	for (int j = 0; j < tags.size(); j++) {//find last movie's tags and add
		if (find(historyTags.begin(), historyTags.end(), tags[j]) != historyTags.end()) {
			for (int i = 0; i != historyTags.size(); i++) {
				if (tags[j].compare(historyTags[i]) == 0)
					count[i]++;
			}
		}
		else {
			historyTags.push_back(tags[j]);
			count.push_back(1);
		}
	}

	Watchable* toRecommend = history.back()->getNextWatchable(s);
	if (toRecommend != nullptr)
		return toRecommend;
	else {
		int index = 0;
		for (int j = 1; j < historyTags.size(); j++) {//find tag to recommend
			if (count[index] = count[j]) {
				if (historyTags[index].compare(historyTags[j]) > 0) {
					index = j;
				}
			}
			else if (count[index] < count[j]) {
				index = j;
			}

		}
		std::vector<Watchable*> allOptions = s.getContent();
		for (int i = 0; i < allOptions.size(); i++) {//find content by genre
			if (!isInHistory(*allOptions.at(i)) && find(allOptions.at(i)->getTags().begin(), allOptions.at(i)->getTags().end(), historyTags[index]) != allOptions.at(i)->getTags().end()) {
				toRecommend = allOptions[i];
			}
		}
		return toRecommend;
	}

}
