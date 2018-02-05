/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (implementation).
 *
 */
#include "GraphAlgorithms.hpp"

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to GraphAlgorithms.hpp if you write a helper
 * function!
 *
 */

/**
 * TODO: Implement Prim's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Prim's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				onMST and notOnMST are two vectors defined in
 *				GraphAlgorithms.hpp
 * 				that you can use to store which nodes are both in/not in the
 * 				MST. These are cleared at the start of the MST computation for 
 * 				you. To access the nodes that a specific node connects to
 *				you, you can use the vector<Node *> edges which is part
 *				of the Node struct in structs.hpp
 * 				You can compare two nodes to see if they are the same by
 * 				comparing the id attribute of a Node.
 *				You can calculate distance from one node to another by calling
 * 				the double distance(Node a) function of the Node struct.
 * 				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function
 *				in GraphAlgorithms.cpp
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Outline:
 * declare temp_edgy
 * Add the first node in g.nodes to OnMST
 * loop the following:
     * If OnMST.size() == g.nodes.size(), break
     * Load all edges in the graph that start with any node within onMST,
     * and end with a node that isn't in onMST, onto temp_edgy
     * Find the edge in this vector with the minimum weight. 
     * load the node at the end of this edge to OnMST
     * draw the edge
     * clear temp_edgy
 */
void buildMSTPrim(Graph g, GraphApp *app) 
{
    onMST.erase(onMST.begin(), onMST.end()); // works for unordered maps too!
    
    vector<Edge*> temp_edgy = vector<Edge*>();
    // Adding the first {id, node} pair to onMST
    onMST[(*(g.nodes.begin()))->id] = *(g.nodes.begin()); 
    while(true)
    {
        if (onMST.size() == g.nodes.size())
        {
            break; // We have added every node in the tree!
        }
        // Now I will add all valid edges to temp_edgy
        vector<Edge*>::iterator i;
        for (i = g.edges.begin(); i != g.edges.end(); i++)
        {
            //IF: edge starts within MST   AND  edge ends not within MST
            if ((onMST.count(((*i)->a->id)) == 1 && 
            0 == onMST.count(((*i)->b->id))) || 
            (onMST.count(((*i)->b->id)) == 1 && 
            0 == onMST.count(((*i)->a->id))))
            {
                temp_edgy.push_back(*i);
            }
        }
        // Get min
        Edge * edgy = minWeight(temp_edgy); 
        // Load min onto MST
        if (onMST.count(edgy->a->id) == 1)
        {
            onMST[(edgy->b)->id] = edgy->b;
        }
        else
        { 
            onMST[(edgy->a)->id] = edgy->a;
        }
        //Draw edge
        drawEdge(edgy->a, edgy->b, g.edges, app, 1);
        // Clear the temporary vector
        temp_edgy.erase(temp_edgy.begin(), temp_edgy.end());
        
    }
    // clean up the edge_map
    auto iter = g.edge_map.begin();
    while (iter != g.edge_map.end())
    {
        int * arr = iter->first;
        delete[] arr;
        iter++;
    }
    
}

/**
 * @brief Helper funtion that accepts a vector of edges and returns a
 * pointer to the edge with the minimum weight. 
 * @param v Vector of edge pointers
 * @return pointer to min weight edge
 */
Edge* minWeight(vector<Edge*> v)
{
    vector<Edge*>::iterator iter;
    Edge * min = *(v.begin()); // sets min to the first edge
    for (iter = v.begin(); iter != v.end(); iter++)
    {
        if (min->weight > (**iter).weight) // if min has a greater weight
        {
            min = *iter; // switch min
        }
    }
    return min;
}

/**
 * TODO: Implement Kruskal's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Kruskal's algorithm
 *
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than
 *passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You'll want to use a priority queue to determine which edges
 * 				to add first. We've created the priority queue for you
 * 				along with the compare function it uses. All you need to do
 * 				is call edge_queue.top(), edge_queue.pop(), edge_queue.push()
 * 				The data type that this priority queue stores, KruskalEdge 
 *              is defined in GraphAlgorithms.hpp and is an edge between
 *              any two trees. Each Node has a kruskal_edges attribute to store
 *              all the nodes it connects to in the MST. Make sure to use this
 *				to be able to join trees later!
 * 				To know which tree a node is in, use the which_tree attribute.
 * 				You can still use the edges, distance, and id
 *				attributes of a Node.
 * 				When connecting trees, you can call the
 *				kruskalFloodFill function
 * 				defined in structs.hpp on a node to convert it and its
 * 				MST connected nodes to a different tree number recursively.
 *				As in Prim's algorith, call drawEdge to add a connection between
 * 				two nodes to the MST
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * Add your outline here
 *
 *
 */
void buildMSTKruskal(Graph g, GraphApp *app) 
{
    auto compare_func = [](KruskalEdge *a, KruskalEdge *b) 
    {
        return (a->weight > b->weight);
    };
    std::priority_queue<KruskalEdge *, std::vector<KruskalEdge *>,
                        decltype(compare_func)>
        edge_queue(compare_func);

    // Write code here
}

/**
 * TODO: Implement Djikstra's shortest path algorithm.
 *
 * @brief Find the shortest path between start and end nodes with Djikstra's
 * 		  shortest path algorithm
 *
 * @param start	Index of start node of path to find
 * 				Can access the Node * element by using
 *				g.nodes[start]
 * @param end	Index of end node of path to find
 * 				Can access the Node * element by using g.nodes[end]
 * @param g 	Graph object containing vector of nodes and edges
 * 				Definition for struct Graph in structs.hpp
 * @param app	Graphics application class
 * 				Class definition in GraphApp.hpp
 * 				You should not need to use this class other than passing app
 * 				as a parameter to drawEdge
 *
 * @attention 	Some hints for implementation and how to interact with our code
 * 				You can use the distance_to_start attribute of the Node struct
 * 				in structs.hpp to keep track of what the distance from each
 * 				Node to the start node during computation
 * 				You can use the previous attribute of the Node struct
 *				in structs.hpp to keep track of the path you are taking to
 *				later backtrack.
 *				To access the nodes that a specific node connects to you, you
 * 				can use the vector<Node *> edges which is part of the Node struct
 * 				in structs.hpp
 *				Whenever you decide to add an edge between two nodes
 *				to the MST, you can use the provided drawEdge function in
 *				GraphAlgorithms.cpp
 *
 * 
 * set current_node to start
 * Loop:
     * if current node = end
     *      break
     * Add the current node to an unordered map of visited nodes
     * Check all the edges in the graph, and add the edges that start on the
     * current node and end on a unvisited node to a new vector temp_edgy
     * For each vector:
     *      if the distance to start of the current node, plus the edge weight,
     *      is less than the distance to start of the node at the end of the 
     *      edge, change the distance to start, and update the previous node
     * Find the min weighted edge in temp_edgy
     * set the current node to the node at the end of this edge 
 * while current.previous != nullptr:
 *      draw the edge between the current and the previous nodes
 *      current = previous
 */
void findShortestPath(int start, int end, Graph g, GraphApp *app) 
{
    visited.erase(visited.begin(), visited.end()); // works for unordered maps too!
    Node * current = g.nodes[start];
    current->distance_to_start = 0;
    while (true)
    {
        // Update visited map
        visited[current->id] = current; 
        // Vector of relevant edges 
        vector<Edge*> temp_edgy = vector<Edge*>();
        vector<Edge*>::iterator i;
        for (i = g.edges.begin(); i != g.edges.end(); i++)
        {
            //IF: edge starts with current   AND  edge ends with an unvisited node
            if (((current->id ==(*i)->a->id) && 
             0 == visited.count((*i)->b->id)) || 
               ((current->id == (*i)->b->id) && 
             0 == visited.count((*i)->a->id)))
            {
                temp_edgy.push_back(*i); // this is a relevant node
            }
        }
        // loop through all relevant nodes 
        vector<Edge*>::iterator j;
        for (j = temp_edgy.begin(); j != temp_edgy.end(); j++)
        {
            Node * tail_node = nullptr;
            if ((*j)->a->id == current->id)
            {
                tail_node = (*j)->b;
            }
            else
            {
                tail_node = (*j)->a;
            }
            if (tail_node->distance_to_start > 
                current->distance_to_start + (*j)->weight)
            {
                tail_node->previous = current;
                tail_node->distance_to_start = 
                  current->distance_to_start + (*j)->weight;
            }
        }
        if (current->id == g.nodes[end]->id)
        {
            break; // exits loop if end is found
        }
        // If the node cannot be extended from, we will try to extend from
        // The previous node, having already visited this one. 
        if (temp_edgy.size() == 0)
        {
            current = current->previous;
        }
        else // Normal Case
        {
            // Get min
            Edge * edgy = minWeight(temp_edgy);
            // Set current to min
            if (edgy->a->id == current->id)
            {
                current = edgy->b;
            }
            else
            {
                current = edgy->a;
            }
            // clear relevant edges
            temp_edgy.erase(temp_edgy.begin(), temp_edgy.end());
        }
    }
    while (current->previous != nullptr)
    {
        drawEdge(current, current->previous, g.edges, app, 0);
        current = current->previous;
    }
    // clean up the edge_map
    auto iter = g.edge_map.begin();
    while (iter != g.edge_map.end())
    {
        int * arr = iter->first;
        delete[] arr;
        iter++;
    }
}

/**
 * @brief Adds an edge to either the MST or the shortest path based on the
 * 			nodes to connect given. This is done by iterating through the edges
 * 			to find the correct edge given the nodes.
 *
 * @param pt1	One side of edge to draw
 * @param pt2	Other side of edge to draw
 * @param edges	Vector of edges in the graph
 * @param app	Graphics application class
 * @param mst	True if we are adding edge to MST, False if we are adding edge
 * 				to shortest path
 **/

void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app,
              bool mst) 
{
    for (unsigned int i = 0; i < edges.size(); i++) 
    {
        if ((edges[i]->a == pt1 && edges[i]->b == pt2) ||
            (edges[i]->a == pt2 && edges[i]->b == pt1)) 
        {
            if (mst)
                app->add_to_mst(edges[i]);
            else
                app->add_to_path(edges[i]);
            break;
        }
    }
    return;
}
