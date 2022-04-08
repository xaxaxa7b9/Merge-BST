#include <iostream>
#include <time.h>
#include <string>

struct nodeBST
{
	nodeBST* left;
	nodeBST* right;
	nodeBST* parent;
	int value;
};

void insertBST(nodeBST*& root, int valueToAdd)
{
	nodeBST* nodeToAdd = new nodeBST;
	nodeToAdd->value = valueToAdd;
	nodeToAdd->parent = NULL;
	nodeToAdd->left = NULL;
	nodeToAdd->right = NULL;

	nodeBST* pom;
	if (!root)
	{
		root = nodeToAdd;
	}
	else
	{
		pom = root;
		while (1)
		{
			if (nodeToAdd->value < pom->value)
				if (!pom->left)
				{
					pom->left = nodeToAdd;
					break;
				}
				else
					pom = pom->left;

			else
			{
				if (!pom->right)
				{
					pom->right = nodeToAdd;
					break;
				}
				else
					pom = pom->right;
			}
		}
		nodeToAdd->parent = pom;
	}
}

void preorder(nodeBST* root)
{
	if (root)
	{
		std::cout << root->value << " ";
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(nodeBST* root)
{
	if (root)
	{
		inorder(root->left);
		std::cout << root->value << " ";
		inorder(root->right);
	}
}

void postorder(nodeBST* root)
{
	if (root)
	{
		postorder(root->left);
		postorder(root->right);
		std::cout << root->value << " ";
	}
}
void preorderADD(nodeBST* root, nodeBST* Temp)
{
	if (root)
	{
		insertBST(Temp, root->value);
		preorderADD(root->left, Temp);
		preorderADD(root->right, Temp);
	}
}

nodeBST* findBST(nodeBST* root, int target)
{
	nodeBST* pom = root;
	if (!root)
	{
		return NULL;
	}
	else
	{
		while (pom && (pom->value != target))
		{
			if (pom->value < target)
				pom = pom->right;
			else
				pom = pom->left;
		}
		return pom;
	}
}

	int findBSTByValue(nodeBST * root, int target)
	{
		nodeBST* pom = root;
		if (!root)
		{
			return -1000000;
		}
		else
		{
			while (pom && (pom->value != target))
			{
				if (pom->value < target)
					pom = pom->right;
				else
					pom = pom->left;
			}
		}
		if (pom)
			return pom->value;
		else
			return -1000000;
	}

	nodeBST* findminBST(nodeBST * root)
	{
		nodeBST* pom = root;
		if (pom)
			while (pom->left) pom = pom->left;
		return pom;
	}

	nodeBST* findmaxBST(nodeBST * root)
	{
		nodeBST* pom = root;
		if (pom)
			while (pom->right) pom = pom->right;
		return pom;
	}

	nodeBST* nextnodeBST(nodeBST * p)
	{
		nodeBST* pom;

		if (p)
		{
			if (p->right) return findminBST(p->right);

			else
			{
				pom = p->parent;
				while (pom && pom->right == p)
				{
					p = pom;
					pom = pom->parent;
				}
				return pom;
			}
		}
		return p;
	}

	void removeBST(nodeBST * &root, nodeBST * nodeToRemove)
	{
		nodeBST* pom = NULL;
		nodeBST* pom1 = NULL;
		if (nodeToRemove)
		{
			if ((!nodeToRemove->left) || (!nodeToRemove->right))
				pom = nodeToRemove;
			else
				pom = nextnodeBST(nodeToRemove);
			if (pom->left)
				pom1 = pom->left;
			else
				pom1 = pom->right;

			if (pom1)
				pom1->parent = pom->parent;
			if (!pom->parent) root = pom1;
			else if (pom == pom->parent->left) pom->parent->left = pom1;
			else pom->parent->right = pom1;

			if (pom != nodeToRemove)
			{
				nodeToRemove->value = pom->value;
			}

			delete pom;
		}
	}

	nodeBST* MergeTrees(nodeBST **&Bst, int N)
	{
		nodeBST* MergedTree = Bst[0];
		for (int i = 1; i < N; i++)
			{
				nodeBST* pom = Bst[i];
				preorderADD(pom, MergedTree);
			}
		return MergedTree;
	}

	int main()
	{
		srand(time(NULL));
		int N = 0;

		std::cout << "Ile drzew chcesz zlaczyc?" << std::endl;
		std::cin >> N;

		nodeBST** Bst = new nodeBST * [N];

		for (int i = 0; i < N; i++)
			{
				Bst[i] = NULL;
			}

		for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					insertBST(Bst[i], rand() % 30);
				}
			}
		for (int i = 0; i < N; i++)
			{
				inorder(Bst[i]);
				std::cout << std::endl;
			}
		nodeBST* Temp = MergeTrees(Bst, N);
		inorder(Temp);
	}