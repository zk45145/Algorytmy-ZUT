// ALGO2 IN1 20B LAB07
// KRZYSZTOF ZAWADZKI
// zk45145@zut.edu.pl

#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <cmath>

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
	Heap(Node* table, int n, bool variant);
	void addElement(int);
	Node* poll();
	void clear();
	std::string returnString();
	void heapSort();
};

Node::Node()
{
	
}

Node::Node(int key)
{
	this->key = key;
}

Heap::Heap()
{
	this->size = 0;
}

Heap::Heap(Node* table, int n, bool variant)
{
	this->size = n;

	for (int i = 0; i < n; i++)
	{
		this->table[i] = table++;
	}

	if (variant == 0) // top-down
	{
		for (int i = n - 2; i >= 0; i--)
		{
			heapifyDown(i);
		}
	}

	else              // bottom-up
	{
		for (int i = 1; i < n; i++)
		{
			heapifyUp(i);
		}
	}
}

void Heap::heapSort()
{
	int n = size;
	while(size>1)
	{
		std::swap(this->table[0], this->table[size - 1]);
		size--;
		heapifyDown(0);
	}
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
	std::string result = "";
	for (int i = 0; i < size; i++)
	{
		result += std::to_string(table[i]->key) + " ";
	}
	return result;
}

void countSort(Node* table, int n, int m)
{
	int dl = m + 1;
	int* count = new int[dl];
	for (int i = 0; i < dl; i++)
	{
		count[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		count[table[i].key]++;
	}
	int currentIndex = 0;
	for (int i = 0; i < dl; i++)
	{
		for (int j = 0; j < count[i]; j++)
		{
			table[currentIndex++].key = i;
		}
	}
}

void bucketSort(Node* table, int n, int m)
{
	int* buckets = new int[m + 1];

	for (int i = 0; i <= m; i++)
	{
		buckets[i] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		buckets[table[i].key]++;
	}

	int lastIndex = 0;
	for (int i = 0; i <= m; i++)
	{
		int j;
		for (j = lastIndex; j < buckets[i] + lastIndex; j++)
		{
			table[j].key = i;
		}
		lastIndex = j;
	}
}

int main()
{
	srand(time(NULL));

	const int MAX_ORDER = 7;
	const int m = (int)pow(10, 7);

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = (int)pow(10, o);

		Node* array1 = new Node[n];
		for (int i = 0; i < n; i++)
		{
			array1[i].key = ((rand() << 15) + rand()) % m;
		}
		std::cout << std::endl << "Tablica przed sortowaniem (w postaci skroconej do 10 elementow):    ";
		for (int i = 0; i < 10; i++)
		{
			std::cout << array1[i].key << " ";
		}
		std::cout << std::endl << std::endl;
		
		Node* array2 = new Node[n];
		Node* array3 = new Node[n];
		memcpy(array2, array1, n * sizeof(Node));
		memcpy(array3, array1, n * sizeof(Node));

		clock_t begin, end;
		double time_spent;
		begin = clock();
		countSort(array1, n, m);
		end = clock();
		time_spent = (double)(end - begin) / 1000;
		std::cout << std::endl << std::endl;
		std::cout << time_spent << " s - czas wykonania sortowania przez zliczanie" << std::endl << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << array1[i].key << " ";
		}


		begin = clock();
		Heap* kopiec = new Heap(array2, n, 1);
		kopiec->heapSort();
		end = clock();
		time_spent = (double)(end - begin) / 1000;
		std::cout << std::endl << std::endl;
		std::cout << time_spent << " s - czas wykonania sortowania przez kopcowanie" << std::endl << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << kopiec->table[i]->key << " ";
		}
		std::cout << std::endl << std::endl;



		begin = clock();
		bucketSort(array3, n, m);
		end = clock();
		time_spent = (double)(end - begin) / 1000;
		std::cout << time_spent << " s - czas wykonania sortowania kubelkowego" << std::endl << std::endl;
		for (int i = 0; i < 10; i++)
		{
			std::cout << array3[i].key << " ";
		}
		std::cout << std::endl << std::endl << std::endl << std::endl;

		delete array1, array2, array3;
	}

	return 0;
}
