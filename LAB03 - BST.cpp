// ALGO2 IN1 20B LAB03
// KRZYSZTOF ZAWADZKI
// zk45145@zut.edu.pl

#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <stack>


class Node
{
public:
	int key;
	Node* left;
	Node* right;
	char keyChar[10];

	Node() {};
};

class BSTtree
{
public:
	Node* root;

	BSTtree();
	Node* findMinimum(Node* root);
	int insertNode(int key);
	void insertManyNodes(int X);
	std::stack <Node*> findNode(int key);
	bool deleteNode(int key);
	int postOrder(Node* root);
	int inOrder(Node* root);
	int preOrder(Node* root);
};


BSTtree :: BSTtree()
{
	root = NULL;
}

Node* BSTtree::findMinimum(Node* root)
{
	Node* temp = root;
	while (temp->left != NULL) temp = temp->left;
	return temp;
}


int BSTtree::insertNode(int key)
{
	Node* previous = NULL;
	Node* p = root;
	while (p != NULL)
	{
		if (p->key == key) return 1;
		previous = p;
		if (p->key < key)
			p = p->right;
		else p = p->left;
	}
	Node* new_Node = new Node;
	new_Node->key = key;
	sprintf_s(new_Node->keyChar, "%d", key);
	new_Node->left = NULL;
	new_Node->right = NULL;
	if (previous == NULL)
	{
		root = new_Node;
		return 0;
	}
	if (previous->key < key) previous->right = new_Node;
	else previous->left = new_Node;
	return 0;
}

void BSTtree::insertManyNodes(int X)
{
	for (int i = 0; i < X; i++)
	{
		do{} while (insertNode(rand() % 20000 - 10000));
	}
}

std::stack <Node*> BSTtree::findNode(int key)
{
	std::stack <Node*> S;
	bool found = 0;
	Node* p = root;
	while ((p != NULL) && !found)
	{
		S.push(p);
		if (p->key == key) found = 1;
		else if (p->key < key) p = p->right;
		else p = p->left;
	}
	if (p == NULL) S.push(p);
	return S;
}

bool BSTtree :: deleteNode(int key)
{
	std::stack <Node*> tempS = findNode(key);
	Node* temp = tempS.top();
	if (temp == NULL) 
		return 1;

	if (temp->left == NULL && temp->right == NULL)
	{
		tempS.pop();
		if (tempS.top()->right == temp) tempS.top()->right = NULL;
		else tempS.top()->left = NULL;
		delete temp;
		temp = NULL;
		return 0;
	}
	if (temp->left != NULL && temp->right == NULL)
	{	
		Node* help = temp;
		tempS.pop();
		if (tempS.top()->right == temp) tempS.top()->right = temp->left;
		else tempS.top()->left = temp->left;

		temp = temp->left;
		if (help == this->root) this->root = temp->left;
		return 0;
	}
	if (temp->left == NULL && temp->right != NULL)  
	{
		Node* help = temp;
		tempS.pop();
		if (tempS.top()->right == temp) tempS.top()->right = temp->right;
		else tempS.top()->left = temp->right;

		temp = temp->right;
		if (help == this->root) this->root = temp->right;
		return 0;
	}
	if (temp->left != NULL && temp->right != NULL)
	{
		Node* successor = findMinimum(temp->right);	

		if (successor->right == NULL)
		{
			tempS = findNode(successor->key);
			tempS.pop();
			tempS.top()->left = NULL;
			temp->key = successor->key;
			successor = NULL;
			return 0;
		}
		else
		{
			tempS = findNode(successor->key);
			tempS.pop();
			tempS.top()->left = successor->right;
			temp->key = successor->key;
			for (int i = 0; successor->keyChar[i] != '\0'; i++)
			{
				temp->keyChar[i] = successor->keyChar[i];
			}
			successor = NULL;
			return 0;
		}
	}
}

int BSTtree::postOrder(Node* root)
{
	int number = 1;
	if (root == NULL) return 0;
	if (root->left != NULL) number+=postOrder(root->left);
	if (root->right != NULL) number+=postOrder(root->right);
	std::cout << root->key << std::endl;
	return number;
}

int BSTtree::inOrder(Node* root)
{
	int number = 1;
	if (root == NULL) return 0;
	if (root->left != NULL) number += inOrder(root->left);
	std::cout << root->key << std::endl;
	if (root->right != NULL) number += inOrder(root->right);
	return number;
}

int BSTtree::preOrder(Node* root)
{
	int number = 1;
	if (root == NULL) return 0;
	std::cout << root->key << std::endl;
	if (root->left != NULL) number += preOrder(root->left);
	if (root->right != NULL) number += preOrder(root->right);
	return number;
}

int main()
{
	srand(time(NULL));

	int X, k1, k2, k3, k4;

	std::ifstream file;
	file.open("inlab03.txt");
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

	BSTtree* drzewo = new BSTtree();
	drzewo->deleteNode(k1);
	drzewo->insertNode(k1);
	drzewo->insertManyNodes(X);
	drzewo->inOrder(drzewo->root);
	std::cout << std::endl << std::endl;
	drzewo->preOrder(drzewo->root);
	std::cout << std::endl << std::endl;
	drzewo->insertNode(k2);
	drzewo->inOrder(drzewo->root);
	std::cout << std::endl << std::endl;
	drzewo->insertNode(k3);
	drzewo->insertNode(k4);
	drzewo->deleteNode(k1);
	drzewo->preOrder(drzewo->root);
	std::cout << std::endl << std::endl;
	drzewo->findNode(k1);
	drzewo->deleteNode(k2);
	drzewo->inOrder(drzewo->root);
	drzewo->deleteNode(k3);
	drzewo->deleteNode(k4);

	end = clock();
	time_spent = (double)(end - begin) / 1000;
	std::cout << time_spent << " s - czas wykonania programu" << std::endl;



	return 0;
}