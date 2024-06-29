This project implements a pathfinding algorithm, using a 
combination of forward search and backtracking techniques.
The forwardSearch() algorithm explores eligible nodes level 
by level, expanding outward from the start node to find the 
goal node. The getPath() function is then used to trace 
back from the goal node to the start node once it's found, 
ensuring the path is reconstructed correctly. 
Challenges initially involved a lot of segmentation faults 
as I got the hang of pointers and how to use them, followed
by needing to check that every new object was appropriately
deleted off the heap when it was no longer needed.
The biggest challenge was changing a working program in 
Milestone 3 with defined Env dimensions to accommodate a 
dynamic array - the hardest part was figuring out how to 
handle an environment with more rows than columns, which was 
solved in the readreadEnvStdin()with the assistance of the 
Milestone 4 helper code provided. 
To do this, I also had to change the original function parameters 
to take in initial variables for rows and columns in the main.cpp. 
Therefore, the printEnvStdout() was also changed to take in 
these same parameters to enable proper print out of the completed 
path in the environment.
