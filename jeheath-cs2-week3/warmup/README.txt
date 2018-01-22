The minesweeper program is simple to run. Any file that contains Es and Ms, and is also
square in character count, may be read by the program and played. demo.txt is a good
example of such a file. The main function takes no arguments, and it will prompt for
a filename. Admittedly I changed the input output format to something that suited the
terminal better, and I made the program interactive. I did not think this would influence
the value of the algorithm, and it is now quite close to an actual minesweeper game. 

For every clearing operation, r_reveal performs 9 operations to check for bombs, and 
if no bombs are found, then another 9 operations to reveal other empty cells. In the
worst case of this, since repeats are avoided, these 18 operations can't be performed
more than n times. This gives us linear time for the algorithm.
O(n) where n is the number of elements in the game board. Note that this is worst case;
it only applies when the board is completely empty. 


Here is the terminal output from a successful run of the program:

What is the name of the file you want to input? 
The name of the demo file is demo.txt    demo.txt
E E E E E E E E 
E E E E M E M E 
E E E E E E E E 
E E E E E E E E 
E M M M E E E E 
E E E E E E E E 
E E E M E E E E 
E E E E E E E E 
Enter a move in the form "row column" where the firstrow/column is 0. 
Enter 2 negative numbers to quit.
Enter: 0 0
B B B 1 E E E E 
B B B 1 M E M E 
B B B 1 E E E E 
1 2 3 2 E E E E 
E M M M E E E E 
E E E E E E E E 
E E E M E E E E 
E E E E E E E E 
Enter: 7 7
B B B 1 E E E E 
B B B 1 M E M E 
B B B 1 1 2 1 1 
1 2 3 2 1 B B B 
E M M M 1 B B B 
E E E E 2 B B B 
E E E M 1 B B B 
E E E E 1 B B B 
Enter: 1 4
B B B 1 E E E E 
B B B 1 X E M E 
B B B 1 1 2 1 1 
1 2 3 2 1 B B B 
E M M M 1 B B B 
E E E E 2 B B B 
E E E M 1 B B B 
E E E E 1 B B B 
Enter: -1 -1
You have quit


------------------
(program exited with code: 0)
Press return to continue

