// ALGO2 IN1 20B LAB05
// KRZYSZTOF ZAWADZKI
// zk45145@zut.edu.pl

#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>

int power(int a, int b)
{
	int result = 1;
	for (int i = 0; i < b; i++)
	{
		result *= a;
	}
	return result;
}

class Element
{	
	public:
	int key;
	Element();
	Element(int);
};

class HashTable
{
	public:
	Element* table [997];
	HashTable() {};
	HashTable(int);
	bool addElementDouble(int key);
	bool addElementLinear(int key);
	void addXElementsDouble(int X);
	void addXElementsLinear(int X);
	bool deleteElementDouble(int key);
	bool deleteElementLinear(int key);
	int findElementDouble(int key);
	int findElementLinear(int key);
	void printKeyValues(int L, int R);

	int H(int);
	int Hp(int);
};

Element::Element()
{
	key = 0;
}

Element::Element(int key)
{
	this->key = key;
}


HashTable::HashTable(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		table[i] = new Element();
	}
}

int HashTable::H(int key)
{
	return (((key % 1000) + (power(2, key % 10)) + 1) % 997);
}

int HashTable::Hp(int key)
{
	return (3 * key) % 19 + 1;
}


bool HashTable::addElementDouble(int key)
{	
	int index, i = 0;
	Element* temp = new Element(key);
	do
	{
		index = (H(key) + i * Hp(key)) % 997;
		i++;
		if (this->table[index]->key == key)
			return 1;
	} while ((this->table[index]->key != 0 && this->table[index]->key != -1) && i < 997);
	this->table[index] = temp;
	return 0;
}

bool HashTable::addElementLinear(int key)
{
	int index, i = 0;
	Element* temp = new Element(key);
	do
	{
		index = (H(key) + i) % 997;
		i++;
		if (this->table[index]->key == key)
			return 1;
	} while ((this->table[index]->key != 0 && this->table[index]->key != -1) && i < 997);
	this->table[index] = temp;
	return 0;
}

void HashTable::addXElementsDouble(int X)
{
	for (int i = 0; i < X; i++)
	{
		do {} while (addElementDouble(rand ()% 20000 + 20000));
	}
}

void HashTable::addXElementsLinear(int X)
{
	for (int i = 0; i < X; i++)
	{
		do {} while (addElementLinear(rand() % 20000 + 20000));
	}
}

bool HashTable::deleteElementDouble(int key)
{
	int index, i = 0;
	do
	{
		index = (H(key) + i * Hp(key)) % 997;
		i++;
		if (this->table[index]->key == key)
		{
			this->table[index]->key = -1;
			return 0;
		}
	} 
	while (i < 997);
	return 1;
}

bool HashTable::deleteElementLinear(int key)
{
	int index, i = 0;
	do
	{
		index = (H(key) + i) % 997;
		i++;
		if (this->table[index]->key == key)
		{
			this->table[index]->key = -1;
			return 0;
		}
	} while (i < 997);
	return 1;
}

int HashTable::findElementDouble(int key)
{
	int index, i = 0;
	do
	{
		index = (H(key) + i * Hp(key)) % 997;
		i++;
		if (this->table[index]->key == key)
			return index;
	} while (i < 997);
	return -1;
}

int HashTable::findElementLinear(int key)
{
	int index, i = 0;
	do
	{
		index = (H(key) + i) % 997;
		i++;
		if (this->table[index]->key == key)
			return index;
	} while (i < 997);
	return -1;
}

void HashTable::printKeyValues(int L, int R)
{
	for (int i = L; i <= R; i++)
	{
		std::cout << table[i]->key << std::endl;
	}
}


int main()
{
	srand(time(NULL));

	int X, k1, k2, k3, k4;

	std::ifstream file;
	file.open("inlab05.txt");
	if (!file)
	{
		std::cout << "Blad odczytu pliku! " << std::endl;
		return false;
	}
	file >> X >> k1 >> k2 >> k3 >> k4;
	file.close();

	clock_t begin, end;
	double time_spent;
	begin = clock();

	HashTable* tablica = new HashTable(997);
	tablica->deleteElementLinear(k1);
	tablica->addElementLinear(k1);
	tablica->printKeyValues(0, 100);
	tablica->addXElementsLinear(X);
	tablica->printKeyValues(0, 100);
	tablica->addElementLinear(k2);
	tablica->addElementLinear(k3);
	tablica->addElementLinear(k4);
	tablica->printKeyValues(0, 100);
	tablica->printKeyValues(500, 600);
	tablica->deleteElementLinear(k3);
	tablica->deleteElementLinear(k4);
	tablica->printKeyValues(0, 100);
	tablica->printKeyValues(500, 600);

	end = clock();
	time_spent = (double)(end - begin) / 1000;
	std::cout << time_spent << " s - czas wykonania 1. czesci programu" << std::endl;

	begin = clock();

	HashTable* tablica2 = new HashTable(997);
	tablica2->deleteElementDouble(k1);
	tablica2->addElementDouble(k1);
	tablica2->printKeyValues(0, 100);
	tablica2->addXElementsDouble(X);
	tablica2->printKeyValues(0, 100);
	tablica2->addElementDouble(k2);
	tablica2->addElementDouble(k3);
	tablica2->addElementDouble(k4);
	tablica2->printKeyValues(0, 100);
	tablica2->printKeyValues(500, 600);
	tablica2->deleteElementDouble(k3);
	tablica2->deleteElementDouble(k4);
	tablica2->printKeyValues(0, 100);
	tablica2->printKeyValues(500, 600);

	end = clock();
	time_spent = (double)(end - begin) / 1000;
	std::cout << time_spent << " s - czas wykonania 2. czesci programu" << std::endl;

	return 0;
}