#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 
#include <sstream> 
#include <Windows.h>

using namespace std;

struct Endpoint {				// this structure will help us to not be confused in numbers.
	int position;
	bool direction;				//"direction"  means the start or the end of the interval
};

void SortEndpoints(std::vector<Endpoint> &endpoints);

int main()
{
	vector<Endpoint> endpoints;						//The main array
	Endpoint endpoint;									//endpoint and str are just auxiliary parameters
	string str;
	bool direction = true;
	cout << "Please enter the intervals below. Press \"Enter\" again when finished:\n";
	getline(cin, str);
	while (str != "") {							//if we got an empry line, thet means we've reached the end
		istringstream ss(str);
		while (ss >> endpoint.position) {				//read intervals
			endpoint.direction = direction;
			direction = 1 - direction;				//if we've read the start, the next number is definitely the end 
			endpoints.push_back(endpoint);			//push to array
		}
		getline(cin, str);
	}

	SortEndpoints(endpoints);
	cout << "Here are the spaces:\n";
	int x = 1;
	for (unsigned int i = 1; i < endpoints.size() - 1; i++) {		//no need to check the first and the last endpoints because they are always the start and the end
		if (endpoints[i].direction == false)
			x--;
		else
			x++;
		if (x == 0) {			//if x = 0, we found a point that is not inside any interval. That is the beginning of the break.
			if(endpoints[i].position != endpoints[i + 1].position)
			cout << endpoints[i].position << " " << endpoints[i+1].position << endl;
			i++;				//we can say that next point is the end and skip it.
			x++;
		}
	}
	endpoints.clear();
	system("pause");
}

void SortEndpoints(std::vector<Endpoint> &endpoints)
{
	for (unsigned int i = 0; i < endpoints.size() - 1; i++) {		//bubble sorting
		for (unsigned int j = 0; j < endpoints.size() - i - 1; j++)
			if (endpoints[j].position > endpoints[j + 1].position) {
				int x = endpoints[j].position;
				endpoints[j].position = endpoints[j + 1].position;
				endpoints[j + 1].position = x;
				x = endpoints[j].direction;
				endpoints[j].direction = endpoints[j + 1].direction;
				endpoints[j + 1].direction = x;
			}
	}
}

