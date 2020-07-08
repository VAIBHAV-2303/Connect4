# Connect4

C++ implemented code for playing Connect4 in the command-line. 

## Release 1
A Two-Player Game designed using the MiniMax Algorithm alongwith alpha-beta pruning in C++14. It Contains three difficulty levels which are nothing but the maximum depth allowed for the maximiser to evaluate. Although the algorithm performs considerably well, it is not impossible to beat it and an algorithm designed with better heuristics will beat it easily. To overcome this problem, a version making use of Zobrist hashing will soon be released.

## Release 2
Much improved heuristics(Value of End state with no clear result calculated using the number of '2 in a row' and '3 in a row' present in the board with more weight given to '3 in a row') added making the algorithm practically impossible to beat and eliminating the need of Zobrist hashing.
