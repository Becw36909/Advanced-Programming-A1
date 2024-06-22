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

    // Print current node details

    void printCurrentNode(Node* node);

    void printNeighbourNode(Node* node);

    void printCheckNode(Node* node);

    // Print out the Closed list
    void printClosedList(NodeList* closedList);

    // Print out the Open list
    void printOpenList(NodeList* openList);

    bool checkOpenList(Node* neighbourNode);

    bool checkNodesExplored(Node* neighbourNode);



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

    // Helper functions
    void findStartAndGoal(Env env, int& startRow, int& startCol, int& goalRow, int& goalCol);
    
    void getEnvDimensions(Env env, int& rows, int& cols);
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER