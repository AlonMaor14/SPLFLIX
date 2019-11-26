#include <iostream>
#include "../Assignment1/include/Session.h"
#include "../Assignment1\include\User.h"
#include "../Assignment1\include\Watchable.h"
#include "../Assignment1\include\Action.h"
using namespace std;

int main(int argc, char** argv) {

	Session s = Session("nothing");
	vector<string> tags = vector<string>();
	tags.push_back("action");
	Movie avengers = Movie(1,"avengers",120,tags);
	tags.push_back("fantasy");
	Episode got1 = Episode(1, "got", 60, 1, 1, tags);
	Episode got2 = Episode(2, "got", 60, 1, 2, tags);
	got1.setNextEpisodeId(3);
	vector<Watchable*> content = vector<Watchable*>();
	content.push_back(&avengers);
	content.push_back(&got1);
	content.push_back(&got2);


}