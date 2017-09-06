// FileFragmentation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

bool myfunction(string i, string j) {
	return i.size() < j.size();
}

int main()
{
	string line;
	vector<vector<string>> fragment;
	list<string> newfragment;
	ifstream myfile("./Test.txt");
	int nFile = -1;
	if (myfile.is_open()) {
		getline(myfile, line);
		while (getline(myfile, line)) {
			if (line == "") {
				fragment.push_back(vector<string>());
				nFile++;
				continue;
			}
			fragment[nFile].push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	
	int set = -1;
	for (size_t i = 0; i < fragment.size(); i++)
	{
		string output;
		for (size_t j = 0; j < fragment[i].size(); j++)
		{
			newfragment.push_back(fragment[i][j]);
		}

		newfragment.sort(myfunction);
		vector<string> nfragment(newfragment.begin(),newfragment.end());

		vector<string> finalOutput;
		int size = newfragment.size();
		for (int i = 0; i < size / 2; i++)
		{
			string head;
			string tail;
			output = "";
			head = newfragment.front();
			tail = newfragment.back();
			if (head[0] == '1') {
				output += tail;
				output += head;
			}
			else {
				output += head;
				output += tail;
			}
			newfragment.pop_front();
			newfragment.pop_back();
			finalOutput.push_back(output);
		}
		output = "";
		for (size_t i = 0; i < finalOutput.size(); i++)
		{
			for (size_t j = 0; j < nfragment.size(); j++)
			{
				string a = "^" + nfragment[j] + ".*|.*" + nfragment[j] + "$";
				regex e(a);
				if (!regex_match(finalOutput[i], e)) 
					break;
				if (j == nfragment.size() - 1) {
					output = finalOutput[i];
					i = finalOutput.size();
				}
			}
		}
		cout << output << "\n\n";

	}


    return 0;
}

