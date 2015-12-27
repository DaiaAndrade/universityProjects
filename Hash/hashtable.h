#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include <vector>
#include <list>
#include <string.h>
#include <sys/time.h>
#include <stdio.h>

using namespace std;
using std::vector;
using std::list;
using std::string;

class Pair
{
	string key;
	int data;

	public:
		Pair();
		~Pair();
		void setKey(string key);
		void setData(int data);
		string getKey();
		int getData();
};

class Hash
{
	vector<Pair> hashTable;
	list<Pair> listaEncadeada;
	vector<float> timeVector;
	int tableSize;
	int insertionNumber;
	int insertionControl;
	float totalTime;
	struct timeval startTime, finalTime;
	float localTime;
	vector<int> insertions;

	public:
		Hash();
		~Hash();
		void setDatas(string key, int data, int index);
		Pair getTableData(int index);
		int getTableSize();
		int setTableSize(int newSize);
		void setInsertionNumber();
		int getInsertionNumber();
		int saveInsertions(int insertion);
		void clearInsertions();
		int getInsertionControl();
		void setInsertionControl();
		void setTime();
		float getTime();
		void setTimeVector(float timeVector);
		void getTimeVector();
		void printTable();
		void insertListValue(string key, int data);
		void clearList();
		void clearTable();
		Pair* getValueList(string Key);
		list<Pair> getList();
		vector<Pair> getHashTable();
		int hashFunction(string key);
		int hashFunction2(string key);
		void insertFunction(string key, int data);
		int searchFunction(string key);
		void resizeHash();
};

#endif
