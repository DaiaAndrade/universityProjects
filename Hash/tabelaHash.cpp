#include <iostream>
#include <vector>
#include <list>
#include <string.h>
#include <sys/time.h>
#include "hashtable.h"
#include <stdio.h>

using namespace std;
using std::vector;
using std::list;

Pair::Pair()
{

}

Pair::~Pair()
{

}

void Pair::setKey(string key)
{
	this->key = key;
}

void Pair::setData(int data)
{
	this->data = data;
}

string Pair::getKey()
{
	return this->key;
}

int Pair::getData()
{
	return this->data;
}

Hash::Hash()
{
	this->tableSize = 100;
	this->insertionNumber = 0;
	gettimeofday(&this->startTime,NULL);
	this->hashTable.resize(100, Pair());
	this->insertionControl = 5000;
	this->listaEncadeada.clear();
	this->totalTime = 0;
}

Hash::~Hash()
{

}

//Início funções de set e get

//Armazena os valores <chave,dado>
void Hash::setDatas(string key, int data, int index)
{
	this->hashTable[index].setData(data);
	this->hashTable[index].setKey(key);
}

//Função que retorna o par armazenado na tabela
Pair Hash::getTableData(int index)
{
	return this->hashTable[index];
}

//Retorna o tamanho da tabela
int Hash::getTableSize()
{
	return this->tableSize;
}

int Hash::setTableSize(int newSize)
{
	this->tableSize = newSize;
}


//Incrementa o número de inserções feitas
void Hash::setInsertionNumber()
{
	this->insertionNumber = this->insertionNumber + 1;
}

//Retorna a número de inserções feitas
int Hash::getInsertionNumber()
{
	return this->insertionNumber;
}

int Hash::saveInsertions(int insertion)
{
	this->insertions.push_back(insertion);
}

//Limpa o número de inserções
void Hash::clearInsertions()
{
	this->insertionNumber = 0;
}

//Retorna o controle de inserções

int Hash::getInsertionControl()
{
	return this->insertionControl;
}

//Seta controle de inserções
void Hash::setInsertionControl()
{
	this->insertionControl += 5000;
}

//Função que atualiza o tempo inicial
void Hash::setTime()
{
	gettimeofday(&this->startTime, NULL);
}

//Função que retorna o tempo decorrido desde o início
float Hash::getTime()
{
	gettimeofday(&this->finalTime, NULL); 
	this->localTime = (float)(this->finalTime.tv_sec - this->startTime.tv_sec);
	this->localTime += (this->finalTime.tv_usec - this->startTime.tv_usec) / (float)1000000;

	return this->localTime;
}

//Função que armazena os tempos de inserção
void Hash::setTimeVector(float timeVector)
{
	
	this->timeVector.push_back(timeVector);
	this->totalTime += timeVector;

}

//Função que retorna os tempos de inserção
void Hash::getTimeVector()
{
	int vectorSize = this->timeVector.size();
	for(int i=0; i < vectorSize; i++)
	{
		printf("%i %f \n",this->insertions[i], this->timeVector[i]);
	}
	printf("Tempo total decorrido: %f\n",this->totalTime );
}

void Hash::printTable()
{
	vector<Pair>::iterator iterator;
	for(iterator = this->hashTable.begin(); iterator != this->hashTable.end(); iterator++)
	{
		cout << iterator->getData() << endl;
	}

}

//Insere dados na lista encadeada
void Hash::insertListValue(string key, int data)
{
	Pair *novo;
	novo = new Pair();
	novo->setKey(key);
	novo->setData(data);
	this->listaEncadeada.push_back(*novo);
}

void Hash::clearList()
{
	this->listaEncadeada.clear();
}

void Hash::clearTable()
{
	this->hashTable.clear();
}

//Procura a chave na lista encadeada
Pair* Hash::getValueList(string Key)
{
	list<Pair>::iterator iterator;
	for (iterator = this->listaEncadeada.begin(); iterator != this->listaEncadeada.end(); iterator++)
	{
		if(iterator->getKey() == Key)
		{
			return &(*iterator);
		}
	}
}
//Copia a Lista encadeada
list<Pair> Hash::getList()
{
	return this->listaEncadeada;
}

//Copia a tabela
vector<Pair> Hash::getHashTable()
{
	return this->hashTable;
}

//Fim funções de get e set

//Função Hash disponibilizada pelo professor
int Hash::hashFunction(string key)
{
	int i, keySize, size;
	int indexValue,tableSize;
	indexValue = 0;
	tableSize = getTableSize();
	keySize = key.size();
	for(i=0;i<keySize;i++)
	{
		indexValue+= key[i]*31*keySize;
	}
	indexValue = indexValue%tableSize;
	return indexValue;
}

//Segunda função Hash
int Hash::hashFunction2(string key)
{
	//primeira função testada
	/*unsigned int hash = 0xAAAAAAAA;
	for(std::size_t i = 0; i < key.length(); i++)
	{
		hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ key[i] * (hash >> 3)) : (~((hash << 11) + (key[i] ^ (hash >> 5))));
	}
	return hash%getTableSize();*/
	//segunda função testada
	const unsigned int fnv_prime = 0x811C9DC5;
 	unsigned int hash = 0;
	for(std::size_t i = 0; i < key.length(); i++)
	{
		hash *= fnv_prime;
		hash ^= key[i];
	}
	return hash%getTableSize();
}

//Função de Inserção
void Hash::insertFunction(string key, int data)
{
	int hash,i;
	hash = hashFunction(key);
	float actualChargeFactor = getInsertionNumber()/getTableSize();
	if(actualChargeFactor < 0.75)
	{
		if(this->hashTable[hash].getKey().empty() || this->hashTable[hash].getKey().compare(key) == 0)
		{
			setInsertionNumber();
			setDatas(key,data,hash);
			if(getInsertionNumber() == getInsertionControl())
			{
				float localTime = getTime();
				setTimeVector(localTime);							
				setTime();
				setInsertionControl();
				saveInsertions(getInsertionNumber());
			}
		}
		else
		{
			hash = hashFunction2(key);
			if(this->hashTable[hash].getKey().empty() || this->hashTable[hash].getKey().compare(key) == 0)
			{
				setInsertionNumber();
				setDatas(key,data,hash);
				if(getInsertionNumber() == getInsertionControl())
				{
					
					float localTime = getTime();
					setTimeVector(localTime);							
					setTime();
					setInsertionControl();
					saveInsertions(getInsertionNumber());
				}
			}
			else
			{
				insertListValue(key,data);
				if(getInsertionNumber() == getInsertionControl())
				{
					float localTime = getTime();
					setTimeVector(localTime);							
					setTime();
					setInsertionControl();
					saveInsertions(getInsertionNumber());
				}
			}
		}
	}
	else	//realocação da tabela e reinserção
	{
		setInsertionNumber();
		resizeHash();
		insertFunction(key,data);
		if(getInsertionNumber() == getInsertionControl())
		{
			float localTime = getTime();
			setTimeVector(localTime);							
			setTime();
			setInsertionControl();
			saveInsertions(getInsertionNumber());
		}
	}
}

//Função de Busca
int Hash::searchFunction(string key)
{
	int hash;
	hash = hashFunction(key);
	if(this->hashTable[hash].getKey().compare(key) == 0)
	{
		return this->hashTable[hash].getData();
	}
	else
	{
		hash = hashFunction2(key);
		if (this->hashTable[hash].getKey().compare(key) == 0)
		{
			return this->hashTable[hash].getData();
		}
		else
		{
			return getValueList(key)->getData();
		}
	}
}

void Hash::resizeHash()
{
	list<Pair>::iterator iterator;
	vector<Pair> oldHash(hashTable);
	list<Pair> oldList = this->listaEncadeada;
	int size = getTableSize();
	int newSize = (getTableSize())*2;
	clearTable();
	clearInsertions();
	clearList();
	int i;
	setTableSize(newSize);
	this->hashTable.resize(newSize,Pair());
	for(i=0;i < size;i++)
	{
		if(!oldHash[i].getKey().empty())
		{
			insertFunction(oldHash[i].getKey(),oldHash[i].getData());
		}
	}
	for(iterator = oldList.begin(); iterator != oldList.end(); iterator++)
	{
		if(!iterator->getKey().empty())
		{
			insertFunction(iterator->getKey(),iterator->getData());
		}
	}
}
