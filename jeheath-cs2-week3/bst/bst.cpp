/**
 * This implementation of a binary search tree was defective for a few
 * reasons. The insert function written didn't specify what to do if the
 * root of the tree was still a null pointer, so the first node couldn't 
 * be added. Also, there was no destructor for the tree, and all nodes 
 * had been created with the new keyword. This was fixed by writing a simple 
 * destructor. Finally, the find function had a really weird feature where
 * if would add a node if it didn't find the number, and only on the left 
 * of the parent node. That seemed like a pretty silly mistake, but I 
 * removed it because it didn't really fit the purpose of the function. 
 */


#include <iostream>
#include <stdlib.h>

#define TEST_SIZE 10
#define TEST_SPACE 50

using namespace std;

struct Node
{
    int value;
    Node * left;
    Node * right;
    Node(int v)
    {
        value = v;
        left = nullptr;
        right = nullptr;
    }

    /** @brief Inserts an integer into the subtree rooted at this node.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    bool insert(int val)
    {
        if(val == value)
        {
            return false;
        }
        else if(val < value)
        {
            if(left == nullptr)
            {
                left = new Node(val);
                return true;
            }
            else
            {
                return left->insert(val);
            }
        }
        else
        {
            if(right == nullptr)
            {
                right = new Node(val);
                return true;
            }
            else
            {
                return right->insert(val);
            }
        }
    }

    /** @brief Finds an integer in the subtree rooted at this node.

    @return whether or not the entry exists in this subtree.

    */
    bool find(int val)
    {
        if(val == value)
        {
            return true;
        }
        else if(val < value)
        {
            if(left == nullptr)
            {
               //left = new Node(val);// This seems weird. Why would a
                                      // find function add a node to the 
                                      // tree?
                return false;
            }
            else
            {
                return left->find(val);
            }
        }
        else
        {
            if(right == nullptr)
            {
                return false; // And the addition isn't included here!
            }
            else
            {
                return right->find(val);
            }
        }
    }
};

class BinarySearchTree
{
private:
    Node * root;
public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    /** @brief Inserts an integer into this tree.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    bool insert(int val)
    {
        if (root == nullptr) // This should fix the problem
        {
            root = new Node(val);
            return true;
            // Great, this fix allows the program to run, but its still
            // leaking memory. I probably need a destructor. 
        }
        else
        {
            return root->insert(val); // But what if root is 
        }                             // still a null pointer?
    }

     /** @brief Finds an integer in this tree.

    @return whether or not the entry exists in this tree.

    */
    bool find(int val)
    {
        return root->find(val);
    }
    
    /**
     * This is a helper function for the destructor that calls itself 
     * recursively. It will delete all nodes in a tree via a depth-first 
     * searching method. 
     * @returns nothing
     */
    void destroy(Node* n)
    {
        if (n == nullptr)
        {
            return;
        }
        else
        {
            destroy(n->left);
            destroy(n->right);
            delete n;
        }
    }
    
    /**
     * This is the destructor for the binary search tree class. It
     * essentially checks to see if the root has been initialized, and 
     * if so, calls a function that deletes the entire tree, including 
     * the root. 
     */
    ~BinarySearchTree()
    {
        if (root == nullptr)
        {
            return; // nothing needs to be deleted because 0 nodes were 
                    // allocated
        }
        else
        {
            destroy(root); //Helper function that I can use recursively
        }
    }
    
    
};

int main(int argc, char ** argv)
{
    BinarySearchTree b;
    srand(42);

    // first insert some test numbers
    cout << endl << endl
         << "adding " << TEST_SIZE << " numbers" << endl << endl;
    for(int i = 0; i < TEST_SIZE; i++)
    {
        int k = rand() % TEST_SPACE;
        cout << "Inserting " << k << "... ";
        bool s = b.insert(k);
        if(s)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "already in" << endl;
        }
    }

    // now print out all the numbers in the tree
    // (by finding all possible numbers, not by traversing the tree)
    cout << endl << endl
         << "ok, now printing contents (the slow way)" << endl << endl;
    for(int j = 0; j < TEST_SPACE; j++)
    {
        if(b.find(j))
        {
            cout << j;
        }
    }

    cout << endl << endl << "all done" << endl << endl;
    // Destructor is called implicitly -- Memory Errors are gone!
    return 0;
}
