/**
 * This program will leak memory because the insert function creates 
 * Node objects using the "new" keyword, thus storing them in the heap. 
 * Subsequently, when the deconstructor is called, only the head node is
 * deleted; all the nodes that were created via the insert function will
 * remain in the heap at termination. 
 * 
 * If this program were called repeatedly by another program, eventually 
 * the computer running the process would run out of memory, and the 
 * program would crash. 
 */


/**
 * @file
 * @author The CS2 TA Team (Edited by John Heath)
 * @version 1.1
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Example of a linked list class and usage.
 *
 */

#include <iostream>

/**
 * A class defining the shell of a linked list data structure.
 */
class List
{

/**
 * Public methods accessible by external code.
 */
public:
    List();
    ~List();
    void insert(int item);
    void printList();

/**
 * Private data, including structure definition and class variables.
 */
private:
    struct Node
    {
        int data;
        Node *next;

        /**
         * Constructor for a node structure.
         */
        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
    Node *head;
    int num_elements;
};

/**
 * List constructor.
 */
List::List()
{
    head = nullptr;
    num_elements = 0;
}

/**
 * List destructor.
 */
List::~List()
{
    Node *temp = head; // This variable will cycle through the list and
                       // will be repeatedly deleted. 
    Node *temp_2;
    while(temp->next != nullptr)
    {
        temp_2 = temp->next;
        delete temp;
        temp = temp_2;
    }
    delete temp;
}

/**
 * insert   Insert an integer at the end of the list.
 * @param   item integer to be inserted at the end of the list
 */
void List::insert(int item)
{
    // If we have elements...
    if (num_elements > 0)
    {
        // Set up a pointer to get to end of current list
        Node *temp = head;
        for (int i = 0; i < num_elements - 1; ++i)
        {
            temp = temp->next;
        }
        // temp now points to node at end of list

        // Construct our new node, it doesn't point to anything yet
        Node *new_node = new Node(item, nullptr);

        // Make the old tail point to the new tail
        temp->next = new_node;

        // and update the number of elements in the list
        num_elements++;
    }
    else
    {
        head = new Node(item, nullptr);
        num_elements++;
    }
    return;
}

/**
 * printList    Prints the contents of our list out, one integer per line.
 */
void List::printList()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << std::endl;
        temp = temp->next;
    }
    return;
}

int main(int argc, char const *argv[])
{
    List lst;
    for (int i = 0; i < 10; ++i)
    {
        lst.insert(i);
    }
    lst.printList();
    return 0;
}
