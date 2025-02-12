#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;

class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);
	Watchable(Watchable& other);

    virtual ~Watchable();
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
	long getId() const;
	int getLength();
	void setLength(int newLength);
	std::vector<std::string> getTags();
	virtual void printMe() = 0;

private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
	virtual void printMe();
private:
    std::string name;
};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
	virtual void printMe();
	void setNextEpisodeId(int id);

	//void setNextEpisodeId(Episode *eps);
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
