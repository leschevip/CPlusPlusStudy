#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


#define T char
#define true 1 == 1
#define false 1 != 1
typedef int boolean;

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} BinTreeIntNode;


void printIntArray(int* array, int size, int offset) {
    char format[7];
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < size; ++i) {
        printf(format, array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");
}

void fillIntRandom(int* array, int size, int border) {
    for (int i = 0; i < size; ++i)
        *(array + i) = rand() % border;
}

BinTreeIntNode* treeInsert(BinTreeIntNode *t, int data) {
    BinTreeIntNode *newNode;
    newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    BinTreeIntNode *current = t;
    BinTreeIntNode *parent = t;
    if (t == NULL) {
        t = newNode;
    } else {
        while (current->key != data) {
            parent = current;
            if (current->key > data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return t;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printBinTree(BinTreeIntNode *root) {
    if (root) {
        printf("%d", root->key);
        if (root->left || root->right) {
            printf("(");
            if (root->left)
                printBinTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printBinTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

BinTreeIntNode* getSuccessor(BinTreeIntNode *node) {
    BinTreeIntNode *current = node->right;
    BinTreeIntNode *parent = node;
    BinTreeIntNode *s = node;

    while (current != NULL) {
        parent = s;
        s = current;
        current = current->left;
    }
    if (s != node->right) {
        parent->left = s->right;
        s->right = node->right;
    }
    return s;
}

boolean treeNodeDelete(BinTreeIntNode *root, int key) {
    BinTreeIntNode *current = root;
    BinTreeIntNode *parent = root;
    boolean isLeftChild = true;

    while (current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
        if (current == NULL)
            return false;
    }

    if (current->left == NULL && current->right == NULL) {
        if (current == root)
            root = NULL;
        else if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if (current->right == NULL) {
        if (isLeftChild)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if (current->left == NULL) {
        if (isLeftChild)
            parent->left = current->right;
        else
            parent->right = current->right;
    }
    else {
        BinTreeIntNode *successor = getSuccessor(current);
        if (current == root)
            root = successor;
        else if (isLeftChild)
            parent->left = successor;
        else
            parent->right = successor;
        successor->left = current->left;
    }
    return true;
}

int getCountNodes(BinTreeIntNode *root)
{
	int n = 0;
	if (root->left != NULL)
	{
		n++;
		n += getCountNodes(root->left);
	}

	if (root->right != NULL)
	{
		n++;
		n += getCountNodes(root->right);
	}

	return n;
}

int getHeightTree(BinTreeIntNode *root)
{
	if (root == NULL)
		return 0;

	int hR = 0;
	if (root->right != NULL)
	{
		hR++;
		int h = getHeightTree(root->right);
		if (h == -1)
			return -1;
		else
			hR += h;
	}

	int hL = 0;
	if (root->left != NULL)
	{
		hL++;
		int h = getHeightTree(root->left);
		if (h == -1)
			return -1;
		else
			hL += h;
	}

	return abs(hR-hL) > 1 ? -1 : ((hL >= hR) ? hL : hR);
}

boolean isBalancedTree(BinTreeIntNode *root)
{
	return getHeightTree(root) >= 0;
}

boolean binSearch(BinTreeIntNode* root, int v)
{
	if (root == NULL)
		return false;
	if (root->key == v)
		return true;
	else if (v < root->key)
		return binSearch(root->left, v);
	else
		return binSearch(root->right, v);

	//return false;
}







BinTreeIntNode* balancedTree(int n, FILE *file)
{
	BinTreeIntNode *newNode;
	int x;
	int nL;
	int nR;
	if (n == 0)
		return NULL;
	else
	{
		fscanf(file, "%d", &x);
		nL = n/2;
		nR = n - nL - 1;
		newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
		newNode->key = x;
		newNode->left = balancedTree(nL, file);
		newNode->right = balancedTree(nR, file);
	}
	return newNode;
}

void isBalancedTreeFuncCheckForBalancedTree()
{
	FILE *file;
	BinTreeIntNode *tree = NULL;
	// file.txt { 5 13 7 98 70 67 34 87 6 9 68 88 32 20 45 }
	file = fopen("D:/Workspace/Git/C/lessons/lesson08/file.txt", "r");
	if (file == NULL)
	{
		printf("Cannot open file");
		return;
	}
	const int count = 15;
	tree = balancedTree(count, file);
	printBinTree(tree);
	if (isBalancedTree(tree))
		printf(" <-- balanced");
	else
	{
		printf(" <-- not balanced");
	}
}

void Task1()
{
	const int SIZE = 50;
	const int NODES_COUNT = 1000;
	const int BORDER = 100;
	BinTreeIntNode* tree[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		srand(time(NULL));
		tree[i] = NULL;
		tree[i] = treeInsert(tree[i], rand() % ((int)((1 + i*0.1)*BORDER)));

		for (int k = 1; k < NODES_COUNT; k++)
		{
			treeInsert(tree[i], rand() % ((int)((1 + i*0.1)*BORDER)));
		}
	}

	int balanced = 0;
	for (int i = 0; i < SIZE; i++)
	{
		printf("tree %d: ", i);
		printBinTree(tree[i]);
		if (isBalancedTree(tree[i]))
		{
			balanced++;
			printf(" <-- balanced");
		}
		else
		{
			printf(" <-- not balanced");
		}
		printf("\n");
	}
	float p = (balanced / SIZE) * 100;
	printf("balanced tree: %4.2f\n", p);

	isBalancedTreeFuncCheckForBalancedTree();
	printf("\n");
}

void Task2()
{
	BinTreeIntNode *root = NULL;
	root = treeInsert(root, 10);
	treeInsert(root, 8);
	treeInsert(root, 19);
	treeInsert(root, 5);
	treeInsert(root, 9);
	treeInsert(root, 16);
	treeInsert(root, 21);

	printBinTree(root);
	printf("\n");
	printf("8 in tree = %s\n", binSearch(root, 8) ? "true" : "false");
	printf("100 in tree = %s\n", binSearch(root, 100) ? "true" : "false");
}

int main(int argv, char** argc)
{
	Task1();

	Task2();

	return 0;
}


