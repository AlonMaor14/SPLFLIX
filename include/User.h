#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{
public:
    User(const std::string& name);
	User(User& other);
	virtual ~User();

	bool isInHistory(Watchable& content);

	int calculateAverageLength(std::vector<Watchable*> history);

    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
	
	virtual void duplicatMe(Session s, std::string name) = 0;

protected:
    std::vector<Watchable*> history;
	void setHistory(std::vector<Watchable*> his);
private:
    std::string name;
	
};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
	virtual void duplicatMe(Session s, string name);
private:
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
	virtual void duplicatMe(Session s, string name);
private:
	int i;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
	virtual void duplicatMe(Session s, string name);
private:
	std::vector<std::string> historyTags;
	std::vector<int>count;
};

#endif
