// ALGO2 IN1 20B LAB04
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

	void rotateRight(Node*, Node*, Node*);
	void rotateLeft(Node*, Node*, Node*);
	void balanceTree(int n);
	int getHeight(Node*);
	bool deleteAllNodes(Node*);
	int countNodes(Node*);
};


BSTtree::BSTtree()
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
		do {} while (insertNode(rand() % 20000 - 10000));
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

bool BSTtree::deleteNode(int key)
{
	std::stack <Node*> tempS = findNode(key);
	Node* temp = tempS.top();
	if (temp == NULL)
		return 1;
	if (temp == this->root)
	{
		delete temp;
		temp = NULL;
		this->root = NULL;
		return 0;
	}

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
	if (root->left != NULL) number += postOrder(root->left);
	if (root->right != NULL) number += postOrder(root->right);
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

void BSTtree::rotateRight(Node* grandfather, Node* parent, Node* child)
{
	Node* temp;
	if (grandfather != NULL)
	{
		if (grandfather->right == parent)
			grandfather->right = child;
		else grandfather->left = child;
	}
	else
		root = child;
	temp = child->right;
	child->right = parent;
	parent->left = temp;
}

void BSTtree::rotateLeft(Node* grandfather, Node* parent, Node* child)
{
	Node* temp;
	if (grandfather != NULL)
	{
		if (grandfather->right == parent)
			grandfather->right = child;
		else grandfather->left = child;
	}
	else
		root = child;
	temp = child->left;
	child->left = parent;
	parent->right = temp;
}


void BSTtree::balanceTree(int n)
{
	Node* grandfather = NULL;
	Node* temp = root;
	Node* temp2;
	while (temp != NULL)
	{
		if (temp->left != NULL)
		{
			temp2 = temp->left;
			rotateRight(grandfather, temp, temp->left);
			temp = temp2;
		}
		else
		{
			grandfather = temp;
			temp = temp->right;
		}
	}
	grandfather = NULL;
	temp = root;
	int m = 1;
	while (m <= n) m = 2 * m + 1;
	m = m / 2;
	for (int i = 0; i < n - m; i++)
	{
		temp2 = temp->right;
		if (temp2 != NULL)
		{
			rotateLeft(grandfather, temp, temp->right);
			grandfather = temp2;
			temp = temp2->right;
		}
	}
	while (m > 1)
	{
		m = m / 2;
		grandfather = NULL;
		temp = root;
		for (int i = 0; i < m; i++)
		{
			temp2 = temp->right;
			rotateLeft(grandfather, temp, temp->right);
			grandfather = temp2;
			temp = temp2->right;
		}
	}
}

int BSTtree::getHeight(Node* root)
{
	if (root == NULL) return 0;
	else
	{
		int hl = getHeight(root->left);
		int hp= getHeight(root->right);
		if ( hl > hp)
			return hl+1;
		else
			return hp+1;
	}
}

bool BSTtree::deleteAllNodes(Node* root)
{
	if (root == NULL) return 0;
	if (root->left != NULL) deleteAllNodes(root->left);
	if (root->right != NULL) deleteAllNodes(root->right);
	deleteNode(root->key);
	return 0;
}

int BSTtree::countNodes(Node* root)
{
	int number = 1;
	if (root == NULL) return 0;
	if (root->left != NULL) number += countNodes(root->left);
	if (root->right != NULL) number += countNodes(root->right);
	return number;
}

int main()
{
	srand(time(NULL));

	int X1, X2;

	std::ifstream file;
	file.open("inlab04.txt");
	if (!file)
	{
		std::cout << "Blad odczytu pliku! " << std::endl;
		return false;
	}
	file >> X1 >> X2;
	file.close();

	clock_t begin, end;
	double time_spent;
	begin = clock();

	BSTtree* drzewo = new BSTtree();
	drzewo->insertManyNodes(X1);
	std::cout << drzewo->getHeight(drzewo->root) << std::endl;
	drzewo->balanceTree(drzewo->countNodes(drzewo->root));
	std::cout << drzewo->getHeight(drzewo->root) << std::endl;
	drzewo->deleteAllNodes(drzewo->root);
	drzewo->insertManyNodes(X2);
	std::cout << drzewo->getHeight(drzewo->root) << std::endl;
	drzewo->balanceTree(drzewo->countNodes(drzewo->root));
	std::cout << drzewo->getHeight(drzewo->root) << std::endl;

	end = clock();
	time_spent = (double)(end - begin) / 1000;
	std::cout << time_spent << " s - czas wykonania programu" << std::endl;

	



	return 0;
}