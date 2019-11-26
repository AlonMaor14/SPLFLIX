#include "include/Action.h"
#include "include/Session.h"
#include "include/User.h"
#include "include/Watchable.h"
#include "include/json.hpp"
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include "jser.h"

using namespace std;
using json = json;

void jser::useJson()
{
	ifstream i("../inclide/config1.json");
	json j ;
	
	i >> j;
	int g = 1;
	string s = j.dump(1);
	i.close();
	for (auto& x : j["movies"].items()) {
		cout << g << "Movie" << endl;
		string name = x.value()["name"];
		int k = x.value()["length"];
		cout << name << endl;
		cout << k << endl;
		vector<string> tags;
		for (auto tag : x.value()["tags"].items()) {
			tags.push_back(tag.value());
		}
		for (int u = 0; u < tags.size(); u++) {
			cout << tags.at(u) << endl;
		}
		g++;
	}

}
