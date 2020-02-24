// ALGO2 IN1 20B LAB06
// KRZYSZTOF ZAWADZKI
// zk45145@zut.edu.pl

#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>

class Node
{
public:
	int key;
	Node();
	Node(int);
};

class Heap
{
private:
	void heapifyUp(int);
	void heapifyDown(int);
public:
	Node* table[10000000];
	int size;

	Heap();
	void addElement(int);
	Node* poll();
	void clear();
	std::string returnString();
};

Node::Node()
{
	this->key = rand() % 100000;
}

Node::Node(int key)
{
	this->key = key;
}

Heap::Heap()
{
	this->size = 0;
}

void Heap::heapifyUp(int index)
{
	while (index != 0 && (table[index]->key > table[(index - 1) / 2]->key))
	{
		std::swap(table[index], table[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

void Heap::heapifyDown(int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	while ((right < size) && ((table[index]->key < table[left]->key) || (table[index]->key < table[right]->key)))
	{
		if (table[left]->key > table[right]->key)
		{
			std::swap(table[index], table[left]);
			index = left;
			left = 2 * index + 1;
			right = 2 * index + 2;
		}
		else
		{
			std::swap(table[index], table[right]);
			index = right;
			left = 2 * index + 1;
			right = 2 * index + 2;
		}
	}
	if (left < size && (table[index]->key < table[left]->key))
			std::swap(table[index], table[left]);
}

void Heap::addElement(int key)
{
	this->table[size] = new Node(key);
	heapifyUp(size);
	size++;
}

Node* Heap::poll()
{
	if (size == 0) return NULL;
	std::swap(table[0], table[size - 1]);
	size--;
	heapifyDown(0);
	return table[size];
}

void Heap::clear()
{
	for (int i = 0; i < size; i++)
	{
		delete table[i];
	}
	size = 0;
}

std::string Heap::returnString()
{
	std::string result="";
	for (int i = 0; i < size; i++)
	{
		result += std::to_string(table[i]->key)+" ";
	}
	return result;
}

int main()
{
	srand(time(NULL));
	Heap* kopiec = new Heap();
	const int MAX_ORDER = 7;

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o);
		clock_t begin, end;
		double time_spent;
		begin = clock();
		for (int i = 0; i < n; i++)
		{
			Node* temp = new Node();
			kopiec->addElement(temp->key);
		}
		end = clock();
		time_spent = (double)(end - begin) / 1000;
		std::cout << time_spent << " s - czas wykonania dodawania " << n << " elementow" << std::endl;

		begin = clock();
		for (int i = 0; i < n; i++)
		{
			Node* polled = kopiec->poll();
			delete polled;
		}
		end = clock();
		time_spent = (double)(end - begin) / 1000;
		std::cout << time_spent << " s - czas wykonania pobierania i usuwania " << n << " elementow" << std::endl;

		kopiec->clear();
	}
	delete kopiec;
}
