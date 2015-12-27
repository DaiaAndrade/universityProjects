#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"

using namespace std;
using std::vector;

int main(int argc, char **argv)
{
	Hash novo = Hash();
	int data;
	string line,key;
	while (getline( cin, line ) && !line.empty())
	{
		istringstream ss(line);
		ss >> key >> data;
		if (std::string::npos == line.find_first_of("0123456789"))
		{
		 	cout << novo.searchFunction(key) << endl;
		}
		else
		{
			novo.insertFunction(key,data);
		}
	}
	return 0;
}
