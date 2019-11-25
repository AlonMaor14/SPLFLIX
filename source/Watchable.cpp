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
};

Episode::Episode(long id, const std::string& seriesName, int length, int season, int episode, const std::vector<std::string>& tags) : Watchable(id, length, tags) {
	this->seriesName = seriesName;
	this->season = season;
	this->episode = episode;
};

std::string Episode::toString() const {
	return seriesName;
}
Watchable* Episode::getNextWatchable(Session& s) const
{
	return s.getContent().at(nextEpisodeId);
}

void Episode::setNextEpisodeId(int id) {
	nextEpisodeId = id;
}





//void Episode::setNextEpisodeId(Episode *eps){)