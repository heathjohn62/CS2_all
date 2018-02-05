John Heath
CS2 Assignment 5

Part 1 Short Answer

A minimum spanning tree is a tree that connects all nodes together, but has the 
minimum total edge weight. For example, if each edge is a certain length, the MST
would be the tree with the smallest sum of the lengths of each edge, that still connects
all nodes. 

If there was only one node in the candidate tree, it would make sense to add the node 
connected to our tree with the minimum edge weight. For every node we add, there will
be some penalty for adding the edge. Thus, it makes sense to accept the minimum 
penalty, and that there would be no better way to do it. 

If there were more nodes in the candidate tree, we still want to add the node (not 
already in the tree) that connects to our current tree with the minimum edge weight. 
The explanation for this follows the same logic as before. There will always be some 
penalty for adding a node, so it makes sense to accept the minimum penalty, given that
we are truly adding a node new to the tree. We will know we are done when any edge
in the tree is found to connect two nodes within the tree. This way, we can be sure 
there are not more efficient ways with which to travel to each node. It will always yield
the shortest path the final node. 


If we started with a forest of trees, it would make sense to add the edge  with the
minimum wieght that connects two trees. Then, each edge added would be necessary
for the connection of each node to the MST, and the MST would be built from the edges
that achieve this with the smallest weight. 

Part 2 Short Answer

The closest neighbor seems like the best option to investigate first. 

Then, it would be worthwhile to investigate the next closest node to any node in the 
tree. Every time we add a node, we should update the distance from the orginal 
node required to get there, and if it is updated, we should keep track of which node it
came from. 

If the function naturally progresses so that the final node is visited, this means that it
is the nearest node to the current tree, and we will have found the shortest path.  If we
kept track of which node led to each node having the shortest distace from the start, 
we can trace back along that path to find the shortest path. 
