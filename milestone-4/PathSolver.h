#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */


bool getEnvDimensions(Env env, int& rows, int& cols);

bool findStartAndGoal(Env env, int rows, int cols, int& startRow, int& startCol, int& goalRow, int& goalCol);

void processNodes(Env env, int rows, int cols, Node* startNode, Node* goalNode);

void addNeighbors(Env env, int rows, int cols, Node* currentNode, int dx[], int dy[], int possibleMoves);



   private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // Open list for forward search
    NodeList* openList;

    int rows;
    int cols;
    Node* startNode;
    Node* goalNode;

};




#endif //COSC_ASSIGN_ONE_PATHSOLVER