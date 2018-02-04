// Short Answers in README

#include <iostream>
#include <vector>

class Node
{
    int value;
    std::vector<Node*> edges;
    bool visited; // my solution
public:
    Node(int val);
    void add_edge(Node*);
    bool dfs(int to_find);
    bool is_visited();
};

/**
 * Node constructor
 */
Node::Node(int val)
{
    this->value = val;
    visited = false;
}

/**
 * Returns whether a node has already been explored
 */
bool Node::is_visited()
{
    return this->visited;
}
/**
 * Adds a link from the current node to a given node
 */
void Node::add_edge(Node * n)
{
    this->edges.push_back(n);
}

// true indicates that the value was found, and false indicates that the value was not found.
bool Node::dfs(int to_find)
{
    if(this->value == to_find)
    {
        return true;
    }
    this->visited = true; // Node has been visited
    std::vector<Node*>::iterator i;
    for(i = this->edges.begin(); i != this->edges.end(); i++)
    {
        Node * n = *i;
        if (!n->is_visited()) // This is my primary edit
        {
            bool r = n->dfs(to_find);
            if(r)
            {
                return r;
            }
        }
    }
    return false;
}

int main(void)
{
    Node * n1 = new Node(1);
    Node * n2 = new Node(2);
    Node * n3 = new Node(3);
    n1->add_edge(n2);
    // Adding a two-way edge caused the program to loop! 
    // Led to a segfault.
    n2->add_edge(n1);  // Originally caused program failure
    n2->add_edge(n3);
    for (int i = 1; i < 5; i++)
    {
        std::cout << "Value " << i << std::endl;
        std::cout<< "Found: ";
        if (n1->dfs(i))
        {
            std::cout << "True" <<std::endl;
        }
        else
        {
            std::cout <<"False"<<std::endl;
        }
    }
    delete n1; // Clears allocated memory. No memory was allocated 
    delete n2; // by each node individually, so I did not write a 
    delete n3; // deconstructor. 
    return 0;

}
