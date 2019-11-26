#include "../include/Session.h"
#include "../include/User.h"
#include "../include/Action.h"
#include "../include/Watchable.h"
#include <iterator>;
using namespace std;



BaseAction::BaseAction() : status(ActionStatus::PENDING) {}

ActionStatus BaseAction::getStatus() const
{
	return status;
}

void BaseAction::complete()
{
	status = ActionStatus::COMPLETED;
}

void BaseAction::error(const std::string& errorMsg)
{
	status = ActionStatus::ERROR;
	cout << "Error" + errorMsg << endl;
	
}

std::string BaseAction::getErrorMsg() const
{
	return errorMsg;
}

void BaseAction::setErrorMsg(std::string error)
{
	errorMsg = error;
}

void CreateUser::act(Session& sess)
{
	try {
		string input = sess.getCommand().substr(sess.getCommand().find(" ") + 1, sess.getCommand().length() - 1);
		string secondWord = input.substr(0, sess.getCommand().find(" "));
		string thirdWord = input.substr(sess.getCommand().find(" ") + 1, input.length() - 1);
		if (sess.getUserMap().find(secondWord) != sess.getUserMap().end()) {
			setErrorMsg( "username is already taken");
			error(getErrorMsg());
			sess.getActionsLog().push_back(this);
		}
		else if (thirdWord.find("len") == 0) {
			LengthRecommenderUser newUser = LengthRecommenderUser(secondWord);
			sess.getUserMap().insert({ secondWord,&newUser });
			complete();
			sess.getActionsLog().push_back(this);
		}
		else if (thirdWord.find("rer") == 0) {
			RerunRecommenderUser newUser = RerunRecommenderUser(secondWord);
			sess.getUserMap().insert({ secondWord,&newUser });
			complete();
			sess.getActionsLog().push_back(this);
		}
		else if (thirdWord.find("gen") == 0) {
			GenreRecommenderUser newUser = GenreRecommenderUser(secondWord);
			sess.getUserMap().insert({ secondWord,&newUser });
			complete();
			sess.getActionsLog().push_back(this);
		}
		else {
			setErrorMsg( "recomandation algorithem enterd is not valid");
			error(getErrorMsg());
			sess.getActionsLog().push_back(this);
		}

	}
	catch (...) {
		setErrorMsg("invalid input");
		error(getErrorMsg());
		sess.getActionsLog().push_back(this);
	}
}
	
	


std::string CreateUser::toString() const
{
	if (getStatus() == COMPLETED)
		return "CreateUser COMPLETED";
	else if (getStatus() == ERROR)
		return "CreateUser ERROR: "+ getErrorMsg();
}

void ChangeActiveUser::act(Session& sess)
{
	try {
		string input = sess.getCommand().substr(sess.getCommand().find(" ") + 1, sess.getCommand().length() - 1);
		string secondWord = input.substr(0, sess.getCommand().find(" "));
		std::unordered_map<std::string, User*>::const_iterator got = sess.getUserMap().find(secondWord);
		if (got != sess.getUserMap().end()) {
			sess.setActiveUser(got->second);
			complete();
			sess.getActionsLog().push_back(this);
		}
		else {
			setErrorMsg("user doesn't exist");
			error(getErrorMsg());
			sess.getActionsLog().push_back(this);
		}
	}
	catch (...) {
		setErrorMsg("invalid input");
		error(getErrorMsg());
		sess.getActionsLog().push_back(this);
	}
}

std::string ChangeActiveUser::toString() const
{
	if (getStatus() == COMPLETED)
		return "ChangeActiveUser COMPLETED";
	else if (getStatus() == ERROR)
		return "ChangeActiveUser ERROR: " + getErrorMsg();
}

void DuplicateUser::act(Session& sess)
{
	try {
		string input = sess.getCommand().substr(sess.getCommand().find(" ") + 1, sess.getCommand().length() - 1);
		string secondWord = input.substr(0, sess.getCommand().find(" "));
		string thirdWord = input.substr(sess.getCommand().find(" ") + 1, input.length() - 1);
		std::unordered_map<std::string, User*>::const_iterator gotOriginalUserName = sess.getUserMap().find(secondWord);
		std::unordered_map<std::string, User*>::const_iterator gotDuplicateName = sess.getUserMap().find(thirdWord);

		if (gotOriginalUserName == sess.getUserMap().end()) {
			setErrorMsg("original user doesn't exist");
			error(getErrorMsg());
			sess.getActionsLog().push_back(this);
		}
		else if (gotDuplicateName != sess.getUserMap().end()) {
			setErrorMsg("username is already taken");
			error(getErrorMsg());
			sess.getActionsLog().push_back(this);
		}
		else{
			gotOriginalUserName->second->duplicatMe(sess, thirdWord);
			complete();
			sess.getActionsLog().push_back(this);
		}
	}
	catch (...) {
		setErrorMsg("invalid input");
		error(getErrorMsg());
		sess.getActionsLog().push_back(this);
		}

}

std::string DuplicateUser::toString() const
{
	if (getStatus() == COMPLETED)
		return "DuplicateUser COMPLETED";
	else if (getStatus() == ERROR)
		return "DuplicateUser ERROR: " + getErrorMsg();
}

void PrintContentList::act(Session& sess)
{	
	for (int i = 0; i < sess.getContent().size(); i++) {
		sess.getContent().at(i)->printMe();

	}
	complete();
	sess.getActionsLog().push_back(this);
}

std::string PrintContentList::toString() const
{
	if (getStatus() == COMPLETED)
		return "PrintContentList COMPLETED";
	else if (getStatus() == ERROR)
		return "PrintContentList ERROR: " + getErrorMsg();
}

void PrintWatchHistory::act(Session& sess)
{
	cout << "Watch history for " << sess.getActiveUser()->getName()<<"\n";
	for(int i = 0 ; i<sess.getActiveUser()->get_history().size() ; i++){
		cout << i + 1 << ". " << sess.getActiveUser()->get_history().at(i)->toString() << "\n";
	}
	complete();
	sess.getActionsLog().push_back(this);
}

std::string PrintWatchHistory::toString() const
{
	if (getStatus() == COMPLETED)
		return "PrintWatchHistory COMPLETED";
	else if (getStatus() == ERROR)
		return "PrintWatchHistory ERROR: " + getErrorMsg();
}

void Watch::act(Session& sess)
{	
	try {
		long id = std::stoi(sess.getCommand().substr(sess.getCommand().find(" ") + 1, sess.getCommand().length() - 1));
		cout << "Watching " << sess.getContent().at(id)->toString() << "\n";
		sess.getActiveUser()->get_history().push_back(sess.getContent().at(id));
		Watchable* toRecommend = sess.getActiveUser()->getRecommendation(sess);
		Watch watch = Watch();
		watch.complete();
		sess.getActionsLog().push_back(&watch);
		cout << "We recommend watching " << toRecommend->toString() << " continue watching? [y/n] ";
		string input;
		cin >> input;
		while (input._Equal("y")) {
			cout << "Watching " << toRecommend->toString() << "\n";
			sess.getActiveUser()->get_history().push_back(toRecommend);
			Watch w = Watch();
			w.complete();
			sess.getActionsLog().push_back(&w);
			toRecommend = sess.getActiveUser()->getRecommendation(sess);
			cout << "We recommend watching " << toRecommend->toString() << " continue watching? [y/n] ";
			cin >> input;
		}
	}
	catch (...) {
		setErrorMsg("invalid input");
		error(getErrorMsg());
		sess.getActionsLog().push_back(this);
	}
}

std::string Watch::toString() const
{
	if (getStatus() == COMPLETED)
		return "Watch COMPLETED";
	else if (getStatus() == ERROR)
		return "Watch ERROR: " + getErrorMsg();
}

void DeleteUser::act(Session& sess)
{
	try {
		string input = sess.getCommand().substr(sess.getCommand().find(" ") + 1, sess.getCommand().length() - 1);
		string secondWord = input.substr(0, sess.getCommand().find(" "));
		std::unordered_map<std::string, User*>::const_iterator toDelete = sess.getUserMap().find(secondWord);
		if (toDelete == sess.getUserMap().end()) {
			setErrorMsg("user does not exists");
			error(getErrorMsg());
			sess.getActionsLog().push_back(this);

		}
		else {
			sess.getUserMap().erase(secondWord);
			complete();
			sess.getActionsLog().push_back(this);
		}

	}
	catch(...){
		setErrorMsg("ivalid input");
		error(getErrorMsg());
		sess.getActionsLog().push_back(this);

	}
}

std::string DeleteUser::toString() const
{
	if (getStatus() == COMPLETED)
		return "DeleteUser COMPLETED";
	else if (getStatus() == ERROR)
		return "DeleteUser ERROR: " + getErrorMsg();
}

void PrintActionsLog::act(Session& sess)
{
	for (int i = 0; i < sess.getActionsLog().size(); i++) {
		cout<<sess.getActionsLog().at(i)->toString()<<"\n";
	}
}

std::string PrintActionsLog::toString() const
{
	if (getStatus() == COMPLETED)
		return "PrintActionsLog COMPLETED";
	else if (getStatus() == ERROR)
		return "PrintActionsLog ERROR: " + getErrorMsg();
}

void Exit::act(Session& sess)
{
	complete();
	sess.getActionsLog().push_back(this);
}

std::string Exit::toString() const
{
	if (getStatus() == COMPLETED)
		return "Exit COMPLETED";
	else if (getStatus() == ERROR)
		return "Exit ERROR: " + getErrorMsg();
}
