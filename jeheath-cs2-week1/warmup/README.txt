Running warmup.py will cause a prompt for user input on the terminal. The 
desired array will then be printed given any string inputted. 

Python dictionaries seemed like a very good way to implement this algorithm, but
I am unsure of the time complexity required for python to search a dictionary. 
If searching the dictionary is not a rate limiting step, the time would be O(n), 
because there are two loops that each run through the array once, linearly. 
However, if python searching the dictionary is the equivalent of searching 
through an array, Then both loops would be imbedded loops, and time/space 
complexity would be O(n^2). 