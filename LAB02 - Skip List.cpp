// ALGO2 IN1 20B LAB02
// KRZYSZTOF ZAWADZKI
// zk45145@zut.edu.pl

#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>

float PROB = 0.5;


class Node
{
	public:
	int key;
	double d;
	char c;
	std::vector <Node*> next;

	Node(int);
	Node() {};
	int random_level(int);
};

class List
{
	public:
	Node* head;
	Node* tail;
	int height;

	List(int);
	bool insertSingleNode(int key);
	void insertManyNodes(int X);
	Node* findNode(int key);
	bool deleteNode(int key);
	void showKeyValues(int howMany, int level);
	void countFromLevel(int level);
	void deleteAll();
};

Node::Node(int key)
{
	this->key = key;
	c = 'T';
	d = (double)rand() / 1000;
}

int Node::random_level(int LMAX)
{
	int level = 1;
	while ((rand() % 100 < PROB * 100) && (level < LMAX))
		level++;
	return level;
}

List::List(int LMAX)
{
	head = new Node(-98);
	tail = new Node(999000);
	height = LMAX;

	for (int i = 0; i < LMAX; i++)
	{
		head->next.push_back(tail);
	}
}

bool List::insertSingleNode(int new_key)
{
	Node* new_Node = new Node(new_key);
	new_Node->c = 'T';
	new_Node->d = (double)rand() / 1000;

	Node* x = head;
	Node** update = new Node * [height];

	for (int i = height - 1; i >= 0; i--)
	{
		while (x->next[i]->key < new_key)
		{
			x = x->next[i];
		}
		update[i] = x;
	}

	x = x->next[0];
	if (x->key == new_key)
	{
		x->c = 'D';
		return false;
	};

	new_Node->key = new_key;
	int level = new_Node->random_level(height);

	for (int i = 0; i < level; i++)
	{
		new_Node->next.push_back(update[i]->next[i]);
	}

	for (int i = 0; i < level; i++)
	{
		new_Node->next[i] = update[i]->next[i];
		update[i]->next[i] = new_Node;
	}
	return true;
}

void List::insertManyNodes(int X)
{
	bool ifSuccessfull;
	for (int i = 0; i < X; i++)
	{
		do
		{
		} while (!insertSingleNode(rand() % 99999 + 99));
	}
}

Node* List::findNode(int key)
{
	if (head == NULL)	
		return NULL;
	
		Node* temp = head;
		for (int i = height - 1; i >= 0; i--)
			while (temp->next[i]->key < key)
				temp = temp->next[i];

		temp = temp->next[0];
		if (temp->key == key)
			return temp;

		return NULL;
}

bool List::deleteNode(int key)
{
	if (head == NULL)
	{
		std::cout << "Lista jest pusta. " << std::endl;
		return 1;
	}
	else
	{
		Node* temp = head;
		Node** update = new Node * [height];
		for (int i = height - 1; i >= 0; i--)
		{
			while (temp->next[i]->key < key)
				temp = temp->next[i];
			update[i] = temp;
		}
		temp = temp->next[0];
		if (temp->key > key) return 1;
		for (int i = 0; i < temp->next.size(); i++)
		{
			update[i]->next[i] = temp->next[i];
		}
		return 0;
	}
}

void List::showKeyValues(int howMany, int level)
{
	if (head == NULL)
		std::cout << "Lista jest pusta. " << std::endl;
	else
	{
		Node* temp = head;
		for (int i = 0; i < howMany && temp->next[level] != tail; i++)
		{
			std::cout << temp->next[level]->key << std::endl;
			temp = temp->next[level];
		}
	}
}

void List::countFromLevel(int level)
{
	if (head == NULL)
		std::cout << "Lista jest pusta. " << std::endl;
	else
	{
		Node* temp = head;
		int i = 0;
		for (i; temp->next[level] != tail; i++)
		{
			temp = temp->next[level];
		}
		std::cout << "Liczba wezlow na podanym poziomie: " << i << std::endl;
	}
}

void List::deleteAll()
{
	if (head == NULL)
	{
		std::cout << "Lista jest pusta " << std::endl;
		return;
	}
	else
	{
		Node* temp = head->next[0];

		while (temp != tail)
		{
			temp = head->next[0];
			delete head;
			head = temp;
		}
		delete tail;
		head = NULL;
		tail = NULL;
	}
}


int main()
{
	srand(time(NULL));

	int LMAX;
	int X, k1, k2, k3, k4, k5;
	std::ifstream file;
	file.open("inlab02.txt");
	if (!file)
	{
		std::cout << "Blad odczytu pliku! " << std::endl;
		return false;
	}
	file >> X >> LMAX >> k1 >> k2 >> k3 >> k4 >> k5;
	file.close();

	clock_t begin, end;
	double time_spent;
	begin = clock();

	List* lista = new List(LMAX);
	lista->findNode(k1);
	lista->insertManyNodes(X);
	lista->countFromLevel(0);
	for (int i = 0; i < LMAX; i++)
	{
		lista->showKeyValues(20, i);
		std::cout << std::endl;
	}
	lista->insertSingleNode(k2);
	lista->showKeyValues(20, 0);
	lista->insertSingleNode(k3);
	lista->showKeyValues(20, 0);
	lista->insertSingleNode(k4);
	lista->showKeyValues(20, 0);
	lista->insertSingleNode(k5);
	
	for (int i = 0; i < LMAX; i++)
	{
		lista->countFromLevel(i);
	}

	lista->deleteNode(k3);
	lista->deleteNode(k2);
	lista->deleteNode(k5);

	for (int i = 0; i < LMAX; i++)
	{
		lista->countFromLevel(i);
	}

	for (int i = 0; i < LMAX; i++)
	{
		lista->showKeyValues(20, i);
		std::cout << std::endl;
	}

	end = clock();
	time_spent = (double)(end - begin) / 1000;
	std::cout << time_spent << " s - czas wykonania programu" << std::endl;

	return 0;
}