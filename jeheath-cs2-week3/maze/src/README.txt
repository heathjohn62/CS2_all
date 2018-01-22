A breadth first searching algorithm is going to be faster when the paths required to 
find any solution is short, but there are many different paths. A shorter maze would be
a good example, because a solution might be only a few spaces away from the start, 
and if so, a depth first searching algorithm might get stuck in a rabbit-hole of a path 
when the solution was directly in front of it. In contrast, the breadth first algorithm 
would find the solution quickly because it would explore all options availiable 
simultaneously. On the other hand, if a solution is many moves away, the breadth first
algorithm would be forced to explore many long paths in parallel, wheras the depth
first algorithm, statistically, is likely to stumble into the solution midway through, 
without exploring the entire maze. 

Applications of a stack are obvious: The way computer code is structured is stack-
based. It is useful to call a function that does something, and then resume directly
where you left off upon function termination. If a computer is focusing on completing
a single task, usually a stack is the best choice because it is easy to control the order of 
operation. Arithmitic is a great use of the stack in a computer. 

On the other hand, computers are required to perform multiple tasks in 
parallel today. For example, I want to be alerted by my mac when I recieve a text 
message, and also an email, and while I'm writing code in a virtual machine. 
It makes sense to queue these items so that they come up at a regular requency, 
rather than putting them in a stack where they might be called  immediately, or not at
 all for long periods of time. I would not want my use of a word processor to prevent 
the computer from alterting me. 