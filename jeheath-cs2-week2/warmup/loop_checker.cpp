/**
 * The algorithm I wrote creates an array of pointers to each node in 
 * the linked list, and checks the next field of the pointer added
 * against all pointers in the list after adding it. 
 * Space complexity will be linear because a single array is required.
 * Time complexity will be O(n^2) in the worst case, because n^2/2 
 * comparisons must be made in total to prove the list is linear. 
 * 
 * This file can be built with a compiler and run alone. My compiler 
 * uses the commands:
 * g++ --std=c++11 -Wall -o  "loop_checker" "loop_checker.cpp"
 * to compile. 
 * 
 * 
 * 
 * 
 * 
 * 
 * Here I have copied and pasted the code from the fixed version of
 * "linked_list.cpp" and commented out the main function.
 * I also changed the deconstructor to work on looped functions.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
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
using namespace std;
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
    bool check_loop();
    void loop_de_loop();

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
    // This now checks for the head link to prevent endless cycling of
    // deletions. This is a poor solution for any linked list, but it 
    // works for the loop_de_loop method. 
    while(temp->next != nullptr && temp->next != head)
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
/**
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
*/

/**
 * NEW FUNCTIONS START HERE
 * 
 * check_loop Determines whether there is a loop in the linked list
 * (Detemines whether a list element points to another list element
 * earlier in the list.)
 * @return bool Whether there is a loop in this linked list. 
 */
bool List::check_loop()
{
    if(num_elements == 0)
    {
        return false;
    }
    Node *arr[num_elements]; // arr is an array of node pointers
    Node *temp = head; // temp begins at head, and moves through the list
    int index = 0;
    while(true) 
    {
        arr[index] = temp;
        index++;
        if(temp->next == nullptr) // If the program reaches the last 
        {                         // node, it will return false
            return false;
        }
        for(int i = 0; i < index; i++) // checks every element in arr
        {
            if(arr[i] == temp->next) // True if there is a duplicate
            {
                return true;
            }
        }
        temp = temp->next; //moves to the next element in the list
    }
}

/**
 * This funtction operates on a linear list and appends a loop to the 
 * end of the list. The loop will point at the head of the list. 
 */
void List::loop_de_loop()
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

        // Construct a new node, make it point to the head
        Node *new_node = new Node(5, head);

        // Make the old tail point to the new tail
        temp->next = new_node;

        // and update the number of elements in the list
        num_elements++;
    }
    else
    {
        head = new Node(5, head); // The head points to itsself!
        num_elements++;
    }
    return;
}


/**
 * This is the main function for the loop checker. It creates two loops,
 * one with a circular reference, and one perfectly linear linked lists,
 * and prints the result of the functions to the terminal. 
 */

int main()
{
    List linear = List(); 
    linear.insert(1); // random elements are added
    linear.insert(2); // There is no way to make a loop list just by 
    linear.insert(5); // using the insert function, so this is safe. 
    linear.insert(1);
    cout << "The linear list scans to be: ";
    if (linear.check_loop())
    {
        cout << "looped." << endl;
    }
    else
    {
        cout << "linear. " << endl;
    }
    List looped = List();
    looped.insert(5);
    looped.insert(6);
    looped.loop_de_loop(); // Creates a new element that points to the
    cout << "The looped list scans to be: ";                    // head.
    if (looped.check_loop())
    {
        cout << "looped." << endl;
    }
    else
    {
        cout << "linear. " << endl;
    }
    
    return 0;
}
