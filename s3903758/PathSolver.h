#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver {
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

  // Function to calculate the dimensions of the environment
  bool getEnvDimensions(Env env, int& rows, int& cols);

  // Function to find the start and goal nodes in the environment
  bool findStartAndGoal(Env env, int rows, int cols, int& startRow,
                        int& startCol, int& goalRow, int& goalCol);

  // Function to process nodes and execute the forward search algorithm
  void processNodes(Env env, int rows, int cols, Node* startNode,
                    Node* goalNode);

  // Function to check neighbors and add valid ones to the open list
  void addNeighbors(Env env, int rows, int cols, Node* currentNode, int dx[],
                    int dy[], int possibleMoves);

  // Function to initialize the path and get the goal node
  NodeList* initializePath(NodeList* nodesExploredCopy);

  // Function to trace back the path from goal to start
  void traceBackPath(NodeList* nodesExploredCopy, NodeList* path);

  // Helper function to find the next node in the path
  Node* findNextNode(NodeList* nodesExploredCopy, Node* currentNode);

  // Function to reverse the path
  NodeList* reversePath(NodeList* path);

  // Function to print the path for debugging
  void printPath(NodeList* path);

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

#endif  // COSC_ASSIGN_ONE_PATHSOLVER