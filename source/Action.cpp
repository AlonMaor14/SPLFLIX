#include "../include/Session.h"
#include "../include/User.h"
#include "../include/Action.h"
#include "../include/Watchable.h"
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
	cout << "Error" + errorMsg << endl;
	status = ActionStatus::ERROR;
}

std::string BaseAction::getErrorMsg() const
{
	return errorMsg;
}

void CreateUser::act(Session& sess)
{
	try {
		
	}
	catch (exception) {
		error("Invalid user name or reccomendation type");
	}
	
}

std::string CreateUser::toString() const
{
	return std::string();
}

void ChangeActiveUser::act(Session& sess)
{
}

std::string ChangeActiveUser::toString() const
{
	return std::string();
}

void DuplicateUser::act(Session& sess)
{
}

std::string DuplicateUser::toString() const
{
	return std::string();
}

void PrintContentList::act(Session& sess)
{
}

std::string PrintContentList::toString() const
{
	return std::string();
}

void PrintWatchHistory::act(Session& sess)
{
}

std::string PrintWatchHistory::toString() const
{
	return std::string();
}

void Watch::act(Session& sess)
{
}

std::string Watch::toString() const
{
	return std::string();
}

