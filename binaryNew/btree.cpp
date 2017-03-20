#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <ctime>
#include </usr/local/include/valgrind/callgrind.h>
using namespace std;


const int maxSize = 1000000;
const int maxNumber = 1000000;

struct node {
    int value;
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
        void insert(int value, node *n);
        int search(int value, node *n);
        
        node *root;
};

void btree::destroy_tree(node *n){
  if(n!=NULL)
  {
    destroy_tree(n->left);
    destroy_tree(n->right);
    delete n;
  }
}

void btree::destroy_tree()
{
  destroy_tree(root);
}

btree::btree(){
    root = NULL;
}
btree::~btree(){
    destroy_tree();
}



void btree::insert(int key, node *n){
  if(key< n->value)
  {
    if(n->left!=NULL)
     insert(key, n->left);
    else
    {
      n->left=new node;
      n->left->value=key;
      n->left->left=NULL;    //Sets the left child of the child node to null
      n->left->right=NULL;   //Sets the right child of the child node to null
    }  
  }
  else if(key>=n->value){
    if(n->right!=NULL)
      insert(key, n->right);
    else{
      n->right=new node;
      n->right->value=key;
      n->right->left=NULL;  //Sets the left child of the child node to null
      n->right->right=NULL; //Sets the right child of the child node to null
    }
  }
}

void btree::insert(int key)
{
  if(root!=NULL)
    insert(key, root);
  else
  {
    root=new node;
    root->value=key;
    root->left=NULL;
    root->right=NULL;
  }
}

int btree::search(int key, node *n){
  
    if (key == n->value) {
        return key;
    }

    if (key > n->value ) {

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

int btree::search(int key)
{
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
    sprintf(msg,"3 %d %f", size, elapsed_secs);
    CALLGRIND_DUMP_STATS_AT(msg);

    cout << "\n----Results----- " << endl;
    cout << "size: " << size << endl;
    cout << "res: " << res << endl;
	return res;
}

int main() {

    srand(time(0));

    for (int j = 2; j < maxSize; j+=10000) {
        btree *tree = new btree();

        for (int i = 0; i < j; i++) {
            int n = rand() % maxNumber;
            tree->insert(n);
        }

        search_callgrind(tree, rand() % maxNumber, j);
    }

}