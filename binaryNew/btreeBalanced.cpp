#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <ctime>
#include </usr/local/include/valgrind/callgrind.h>
using namespace std;


const int maxSize = 10000;
const int maxNumber = 10000;

struct node {
    int value;
    int height;
    node *left;
    node *right;
};

class btree {

public:

    btree();

    ~btree();

    void insert(int key);

    int search(int key);

    void destroy_tree();

private:
    void destroy_tree(node *n);

    node *insert(int value, node *n);

    int search(int value, node *n);

    node *root;
};

void btree::destroy_tree(node *n) {
    if (n != NULL) {
        destroy_tree(n->left);
        destroy_tree(n->right);
        delete n;
    }
}

void btree::destroy_tree() {
    destroy_tree(root);
}

btree::btree() {
    root = NULL;
}

btree::~btree() {
    destroy_tree();
}

int height(node *n) {
    if (n == NULL)
        return -1;

    return n->height;
}

int max(int left, int right) {
    if (left > right)
        return left;
    return right;
}

node *rotateWithLeftChild(node* n)
{
    node *leftChild = n->left;
    n->left = leftChild->right;
    leftChild->right = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    leftChild->height = max(height(leftChild->left), n->height) + 1;
    return leftChild;
}

node *rotateWithRightChild(node *n)
{
    node *rightChild = n->right;
    n->right = rightChild->left;
    rightChild->left = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    rightChild->height = max(height(rightChild->right), n->height) + 1;
    return rightChild;
}

node *doubleWithLeftChild(node *n)
{
    n->left = rotateWithRightChild(n->left);
    return rotateWithLeftChild(n);
}

node *doubleWithRightChild(node *n)
{
    n->right = rotateWithLeftChild(n->right);
    return rotateWithRightChild(n);
}

node* btree::insert(int key, node *n) {
    if (n == NULL) {
        n = new node;
        n->left = NULL;
        n->right = NULL;
        n->value = key;
        n->height = 0;
    }
    else if (key < n->value)
    {
        n->left = insert(key, n->left);
        if (height(n->left) - height(n->right) == 2)
            if (key < n->left->value)
                n = rotateWithLeftChild(n);
            else
                n = doubleWithLeftChild(n);
    }
    else if (key > n->value)
    {
        n->right = insert(key, n->right);
        if (height(n->right) - height(n->left) == 2)
            if (key > n->right->value)
                n = rotateWithRightChild(n);
            else
                n = doubleWithRightChild(n);
    }
    n->height = max(height(n->left), height(n->right)) + 1;
    return n;
}

void btree::insert(int key) {
    root = insert(key, root);
}

int btree::search(int key, node *n) {

    if (key == n->value) {
        return key;
    }

    if (key > n->value) {

        if (n->right == NULL) {
            return n->value;
        } else {
            int res = search(key, n->right);
            if (res <= key) {
                return res;
            } else {
                return n->value;
            }
        }
    } else {
        if (n->left == NULL) {
            return n->value;
        } else {
            return search(key, n->left);
        }
    }
}

int btree::search(int key) {
    return search(key, root);
}

int search_callgrind(btree *tree, int key, int size) {
    clock_t begin = clock();
    CALLGRIND_ZERO_STATS;
    CALLGRIND_START_INSTRUMENTATION;

    int res = tree->search(key);

    CALLGRIND_STOP_INSTRUMENTATION;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    char msg[100];
    sprintf(msg, "4 %d %f", size, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);

    cout << "\n----Results----- " << endl;
    cout << "size: " << size << endl;
    cout << "res: " << res << endl;
    return res;
}

int main() {

    srand(time(0));

    for (int j = 2; j < maxSize; j += 1000) {
        btree *tree = new btree();

        for (int i = 0; i < j; i++) {
            int n = rand() % maxNumber;
            tree->insert(n);
        }

        for (int i = 0; i < j; i++) {
            int n = rand() % maxNumber;
            tree->insert(n);
        }

        for (int i = 0; i < j; i++) {
            int n = rand() % maxNumber;
            tree->insert(n);
        }

        search_callgrind(tree, rand() % maxNumber, j);
        tree->destroy_tree();
    }

}