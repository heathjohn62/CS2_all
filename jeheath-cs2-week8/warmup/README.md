EXPLANATION OF HOW TO RUN YOUR WARMUP SOLUTION CODE:
Compile and build the c++ file, and then run the program with the list as command line
arguments. Here is how I did it:

$ cd dir/warmup
dir/warmup$ g++ -Wall -c -g --std=c++11 warmup.cpp
dir/warmup$ g++ --std=c++11 -Wall -o  warmup  warmup.cpp
dir/warmup$ ./warmup 1 2 3 4 5 1 2 3 4 5 -62 44 -62 -88 44
The non-repeated number is: -88

EXPLANATION OF TIME/SPACE COMPLEXITY OF WARMUP SOLUTION CODE:
Time is linear with respect to the length of the list, and space complexity is constant. 
I ran a loop through the list 32 times, but since the number of iterations is independant 
of the length of the list, time is O(n). 

