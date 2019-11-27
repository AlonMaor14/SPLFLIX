#include "..\include\Session.h"
#include "..\include\User.h"
#include "..\include\Watchable.h"
#include "..\include\Action.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Session;


Watchable::Watchable(long id, int length, const std::vector<std::string>& tags) : id(id) { //Constructor
	this->length = length;
	this->tags = tags;
};

Watchable::Watchable(Watchable& other) : id(other.id) { //Copy Constructor
	this->length = other.length;
	this->tags = other.tags;
};

long Watchable::getId() const
{
	return id;
}
int Watchable::getLength()
{
	return length;
}

void Watchable::setLength(int newLength)
{
	this->length = newLength;

}

std::vector<std::string> Watchable::getTags()
{
	return tags;
}

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) : Watchable(id, length, tags) {
	this->name = name;
};

std::string Movie::toString() const {
	return name;
};

Watchable* Movie::getNextWatchable(Session&) const {
	return nullptr;
}
void Movie::printMe()
{
	cout << this->getId() << ". " << name << " " << this->getLength() << " minutes [";
	for (int i = 0; i < getTags().size(); i++) {
		if (i == getTags().size() - 1)
			cout << getTags().at(i) << "]";
		else {
			cout << getTags().at(i) << ", ";
		}
	}
}
;

Episode::Episode(long id, const std::string& seriesName, int length, int season, int episode, const std::vector<std::string>& tags) : Watchable(id, length, tags) {
	this->seriesName = seriesName;
	this->season = season;
	this->episode = episode;
	
	this->nextEpisodeId = -1;
};

std::string Episode::toString() const {
	return seriesName + " S" + std::to_string(season) +" E"+ std::to_string(episode);
}
Watchable* Episode::getNextWatchable(Session& s) const
{
	if (nextEpisodeId != -1) {
		return s.getContent().at(nextEpisodeId);
	}
	else
		return nullptr;
}

void Episode::printMe()
{
	cout << this->getId() << ". " << seriesName << " S"<<season<<" E"<<episode<<" " << this->getLength() << " minutes [";
	for (int i = 0; i < getTags().size(); i++) {
		if (i == getTags().size() - 1)
			cout << getTags().at(i) << "]";
		else {
			cout << getTags().at(i) << ", ";
		}
	}
}

void Episode::setNextEpisodeId(int id)
{
	nextEpisodeId = id;

}







