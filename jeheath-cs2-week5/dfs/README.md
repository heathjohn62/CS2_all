John Heath
CS2 Assignment 5 Part 0

The algorythm is not perfect. This is because it immediately travels to the first node 
within its list of nodes, even if that was the node it just came from. Thus, it quickly
gets stuck in an infinite loop, oscillating between two nodes instead of actually
searching the list. This is illustrated by the segfault that occurs when a two-way edge
is added between nodes. I would fix it by ensuring that a node is marked visited once
it is searched, so that it is never searched again. 