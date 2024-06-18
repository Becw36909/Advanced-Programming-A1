#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"
#include "Types.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);

int main(int argc, char** argv) {
  // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
  // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
  // AS YOU GO ALONG.
  // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
  // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" <<
  // std::endl; testNode(); testNodeList(); std::cout << "DONE TESTING" <<
  // std::endl << std::endl;

  // Load Environment
  Env env;
  readEnvStdin(env);

  // Solve using forwardSearch
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
  PathSolver* pathSolver = new PathSolver();
  pathSolver->forwardSearch(env);

  // NodeList* exploredPositions = nullptr;
  // exploredPositions = pathSolver->getNodesExplored();

  // Get the path
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
  NodeList* solution = pathSolver->getPath(env);

    std::cout << "NodeList SOLUTION size: " << solution->getLength() << std::endl;


  printEnvStdout(env, solution);

  delete pathSolver;
  //delete exploredPositions;
  delete solution;
}

void readEnvStdin(Env env) {
  for (int row = 0; row < ENV_DIM; ++row) {
    for (int col = 0; col < ENV_DIM; ++col) {
      std::cin >> env[row][col];
    }
  }
  // Print
  // std::cout << "Printing input env" << std::endl;

  // for (int row = 0; row < ENV_DIM; ++row)
  // {
  //     for (int col = 0; col < ENV_DIM; ++col)
  //     {
  //         std::cout << env[row][col] << " ";
  //     }
  //     std::cout << std::endl;
  // }
}

void printEnvStdout(Env env, NodeList* solution) {

    std::cout << "INSIDE printEnvStdout: " << std::endl;
    std::cout << "NodeList SOLUTION size: " << solution->getLength() << std::endl;

  // Iterate through the solution path NodeList
  for (int i = 1; i < solution->getLength(); ++i) {
    // Previous node in path
    Node* prevNode = solution->getNode(i - 1);  
      std::cout << prevNode->getRow() << ",";
  std::cout << prevNode->getCol() << ",";
  std::cout << prevNode->getDistanceTraveled() << std::endl;
    // Current node in path
    Node* currNode = solution->getNode(i);      

// Row of previous node
    int prevRow = prevNode->getRow(); 
    // Column of previous node 
    int prevCol = prevNode->getCol();  
    // Row of current node
    int currRow = currNode->getRow();  
    // Column of current node
    int currCol = currNode->getCol();  

    // Determine direction symbol based on movement between nodes
    if (currRow == prevRow && currCol == prevCol + 1) {
      env[prevRow][prevCol] = SYMBOL_RIGHT;  // Move right symbol
    } else if (currRow == prevRow && currCol == prevCol - 1) {
      env[prevRow][prevCol] = SYMBOL_LEFT;  // Move left symbol
    } else if (currRow == prevRow + 1 && currCol == prevCol) {
      env[prevRow][prevCol] = SYMBOL_DOWN;  // Move down symbol
    } else if (currRow == prevRow - 1 && currCol == prevCol) {
      env[prevRow][prevCol] = SYMBOL_UP;  // Move up symbol
    }
  }

  // Print the updated environment with path symbols
  for (int row = 0; row < ENV_DIM; ++row) {
    for (int col = 0; col < ENV_DIM; ++col) {
      // Print each symbol in the environment
      std::cout << env[row][col];  
    }
    // Move to the next line after each row
    std::cout << std::endl;  
  }
}

void testNode() {
  std::cout << "TESTING Node" << std::endl;

  // Make a Node and print out the contents
  Node* node = new Node(1, 1, 2);
  std::cout << node->getRow() << ",";
  std::cout << node->getCol() << ",";
  std::cout << node->getDistanceTraveled() << std::endl;
  delete node;

  // Change Node and print again
  node = new Node(4, 2, 3);
  std::cout << node->getRow() << ",";
  std::cout << node->getCol() << ",";
  std::cout << node->getDistanceTraveled() << std::endl;
  delete node;
}

void testNodeList() {
  std::cout << "TESTING NodeList" << std::endl;

  // Make a simple NodeList, should be empty size
  NodeList* nodeList = new NodeList();
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add a Node to the NodeList, print size
  Node* b1 = new Node(2, 1, 0);
  nodeList->addElement(b1);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add second Nodetest
  Node* b2 = new Node(0, 0, 1);
  nodeList->addElement(b2);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add goal node
  Node* b3 = new Node(4, 6, 0);
  nodeList->addElement(b3);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Test Get-ith - should be 0,0,1
  Node* getB = nodeList->getNode(1);
  std::cout << getB->getRow() << ",";
  std::cout << getB->getCol() << ",";
  std::cout << getB->getDistanceTraveled() << std::endl;

  // Print out the NodeList
  std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO"
            << std::endl;
  for (int i = 0; i < nodeList->getLength(); ++i) {
    Node* currentNode = nodeList->getNode(i);
    if (currentNode != nullptr) {
      std::cout << "Node at index " << i << ": ";
      std::cout << "Row: " << currentNode->getRow() << ", ";
      std::cout << "Column: " << currentNode->getCol() << ", ";
      std::cout << "Distance Traveled: " << currentNode->getDistanceTraveled()
                << std::endl;
    } else {
      std::cout << "Node at index " << i << " is null." << std::endl;
    }
    std::cout << std::endl;
  }

  int estimatedDistance = b1->getEstimatedDist2Goal(b3);

  std::cout << "Estimated distance between b1 and goal b3: "
            << estimatedDistance << std::endl;

  std::cout << "Removing node b2 from the list " << std::endl;

  nodeList->removeElement(b2);

  for (int i = 0; i < nodeList->getLength(); ++i) {
    Node* currentNode = nodeList->getNode(i);
    if (currentNode != nullptr) {
      std::cout << "Node at index " << i << ": ";
      std::cout << "Row: " << currentNode->getRow() << ", ";
      std::cout << "Column: " << currentNode->getCol() << ", ";
      std::cout << "Distance Traveled: " << currentNode->getDistanceTraveled()
                << std::endl;
    } else {
      std::cout << "Node at index " << i << " is null." << std::endl;
    }
    std::cout << std::endl;
  }

  // Add fourth Nodetest
  Node* b4 = new Node(4, 3, 0);
  nodeList->addElement(b4);
  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  // Add fifth Nodetest
  Node* b5 = new Node(4, 3, 0);
  nodeList->addElement(b5);

  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
  std::cout << "checking if node b4 and b5 have the same values: "
            << std::boolalpha << b4->isEqual(*b5) << std::endl;

  for (int i = 0; i < nodeList->getLength(); ++i) {
    Node* currentNode = nodeList->getNode(i);
    if (currentNode != nullptr) {
      std::cout << "Node at index " << i << ": ";
      std::cout << "Row: " << currentNode->getRow() << ", ";
      std::cout << "Column: " << currentNode->getCol() << ", ";
      std::cout << "Distance Traveled: " << currentNode->getDistanceTraveled()
                << std::endl;
    } else {
      std::cout << "Node at index " << i << " is null." << std::endl;
    }
    std::cout << std::endl;
  }

  std::cout << "Removing node b4 from the list " << std::endl;
  nodeList->removeElement(b4);

  std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

  for (int i = 0; i < nodeList->getLength(); ++i) {
    Node* currentNode = nodeList->getNode(i);
    if (currentNode != nullptr) {
      std::cout << "Node at index " << i << ": ";
      std::cout << "Row: " << currentNode->getRow() << ", ";
      std::cout << "Column: " << currentNode->getCol() << ", ";
      std::cout << "Distance Traveled: " << currentNode->getDistanceTraveled()
                << std::endl;
    } else {
      std::cout << "Node at index " << i << " is null." << std::endl;
    }
    std::cout << std::endl;
  }

  delete nodeList;
}