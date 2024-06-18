#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver() {
  openList = new NodeList();
  nodesExplored = new NodeList();
}

PathSolver::~PathSolver()
{
  delete openList;
  delete nodesExplored;
}

// Execute forward search algorithm
// To be implemented for Milestone 2
void PathSolver::forwardSearch(Env env) {
  // Initialize openList and nodesExplored
  // NodeList* openList = new NodeList();
  // NodeList* nodesExplored = new NodeList();

  // Variables for movement directions (up, down, left, right)
  int dx[] = {-1, 1, 0, 0};  // Up, Down, Left, Right
  int dy[] = {0, 0, -1, 1};  // Up, Down, Left, Right
  int possibleMoves = 4;

  // Find the start and goal nodes
  Node* startNode = nullptr;
  Node* goalNode = nullptr;
  for (int row = 0; row < ENV_DIM; ++row) {
    for (int col = 0; col < ENV_DIM; ++col) {
      if (env[row][col] == SYMBOL_START) {
        startNode = new Node(row, col, 0);
      } else if (env[row][col] == SYMBOL_GOAL) {
        goalNode = new Node(row, col, 0);
      }
    }
  }

  // Check if start and goal nodes are found
  if (startNode == nullptr || goalNode == nullptr) {
    std::cerr << "Error: Start or goal node not found." << std::endl;
    delete startNode;
    delete goalNode;
    delete openList;
    delete nodesExplored;
    return;
  }

  // Add start node to openList
  openList->addElement(startNode);

  // Perform forward search algorithm
  bool goalReached = false;
  Node* currentNode = startNode;

  while (openList->getLength() > 0 && !goalReached) {
    // Find the node with the smallest estimated distance in openList
    currentNode = openList->getNodeWithMinEstimatedDist(goalNode);

    // Check if the current node is the goal node
    if (currentNode->getRow() == goalNode->getRow() &&
        currentNode->getCol() == goalNode->getCol()) {
      goalReached = true;
    } else {
      nodesExplored->addElement(currentNode);
      std::cout << "Moved node (" << currentNode->getRow() << ", "
                << currentNode->getCol() << ") to nodesExplored list"
                << std::endl;

      // Explore neighbors of the current node
      for (int i = 0; i < possibleMoves; ++i) {
        int newRow = currentNode->getRow() + dx[i];
        int newCol = currentNode->getCol() + dy[i];

        // Check if the neighbor is within the environment boundaries
        if (newRow >= 0 && newRow < ENV_DIM && newCol >= 0 &&
            newCol < ENV_DIM) {
          if (env[newRow][newCol] != SYMBOL_WALL) {
            Node* neighborNode = new Node(
                newRow, newCol, currentNode->getDistanceTraveled() + 1);

            // Add the neighbor node to openList if it's not already there
            if (!nodesExplored->contains(neighborNode) &&
                !openList->contains(neighborNode)) {
              openList->addElement(neighborNode);
              std::cout << "Added neighbor node (" << newRow << ", " << newCol
                        << ") to open list" << std::endl;
            } else {
              delete neighborNode;
            }
          }
        }
      }

      // Remove the current node from openList
      NodeList* newOpenList = new NodeList();
      for (int i = 0; i < openList->getLength(); ++i) {
        if (!openList->getNode(i)->isEqual(*currentNode)) {
          newOpenList->addElement(openList->getNode(i));
        }
      }
      delete openList;
      openList = newOpenList;
    }
  }

  if (goalReached) {
    std::cout << "Goal reached!" << std::endl;
  } else {
    std::cout << "No path found!" << std::endl;
  }

  std::cout << "nodesExplored size: " << nodesExplored->getLength() << std::endl;

  // Cleanup memory
  delete openList;
  delete goalNode;
}

// Get a DEEP COPY of the explored NodeList in forward search
// To be implemented for Milestone 2
NodeList* PathSolver::getNodesExplored() {
  NodeList* deepCopy = new NodeList();
  for (int i = 0; i < nodesExplored->getLength(); ++i) {
    Node* originalNode = nodesExplored->getNode(i);
    Node* nodeCopy = new Node(*originalNode);  // Use the copy constructor
    deepCopy->addElement(nodeCopy);
  }
    std::cout << "nodesExplored DEEP COPY size: " << nodesExplored->getLength() << std::endl;
    PathSolver::printOpenList(deepCopy);

  return deepCopy;
}

// Execute backtracking and Get a DEEP COPY of the path the
// robot should travel
// To be implemented for Milestone 3
NodeList* PathSolver::getPath(Env env) {


  std::cout << "in getPath()" << std::endl;

  // Get a deep copy of the nodesExplored list
  NodeList* nodesExploredCopy = getNodesExplored();

    if (nodesExploredCopy == nullptr || nodesExploredCopy->getLength() == 0) {
        std::cerr << "Error: nodesExplored is nullptr or empty." << std::endl;
        return nullptr; // or handle the error appropriately
    }

  // Initialize an empty NodeList for the path
  NodeList* path = new NodeList();

    // Get the goal node from nodesExplored (assumed to be the last node)
    Node* goalNode = nodesExploredCopy->getNode(nodesExploredCopy->getLength() - 1);
            std::cout << "goalNode (" << goalNode->getRow() << "," << goalNode->getCol() << ") ";

    Node* currentNode = goalNode;
                std::cout << "currentNode (" << currentNode->getRow() << "," << currentNode->getCol() << ") ";

    path->addElement(new Node(*currentNode));  // Add the goal node to the path

    bool reachedStart = false;

    // Loop until we reach the starting node
    while (!reachedStart) {

        Node* nextNode = nullptr;
        int minDistance = currentNode->getDistanceTraveled();

        // Iterate through nodesExplored to find the next node in reverse path
        for (int i = 0; i < nodesExploredCopy->getLength() && nextNode == nullptr; ++i) {
            Node* neighbor = nodesExploredCopy->getNode(i);
            int distance = neighbor->getDistanceTraveled();
            
            // Check if neighbor node is one step closer to current node
            if (distance == minDistance - 1 &&
                ((abs(neighbor->getRow() - currentNode->getRow()) == 1 && neighbor->getCol() == currentNode->getCol()) ||
                 (abs(neighbor->getCol() - currentNode->getCol()) == 1 && neighbor->getRow() == currentNode->getRow()))) {
                nextNode = neighbor;
            }
        }

        // If nextNode found, update currentNode and add it to the path
        if (nextNode != nullptr) {

            currentNode = nextNode;
            // Add to path
            path->addElement(new Node(*currentNode));  
        }

        // Check if we have reached the starting node
        if (currentNode->getDistanceTraveled() == 0) {
            reachedStart = true;

        }
    }

    // Reverse the path to start from the starting node
    // Initialize an empty NodeList for reversed path
    NodeList* reversedPath = new NodeList();  
    // Add nodes in reverse order
    for (int i = path->getLength() - 1; i >= 0; --i) {
        reversedPath->addElement(new Node(*path->getNode(i)));  
    }

// Clean up memory used by path NodeList
    delete path;  

        // Print the reversed path to debug
    std::cout << "Reversed Path:" << std::endl;
    for (int i = 0; i < reversedPath->getLength(); ++i) {
        Node* node = reversedPath->getNode(i);
        std::cout << "(" << node->getRow() << "," << node->getCol() << ") ";
    }
    std::cout << std::endl;
    // Return the reversed path
    return reversedPath;  
}



 bool PathSolver::checkNodesExplored(Node* neighbourNode){
  bool inNodesExplored = false;

        for (int i = 0; i < nodesExplored->getLength(); ++i) {
          std::cout << "in inNodesExplored for loop, checking node " << i
                    << std::endl;
          Node* checkNode = nodesExplored->getNode(i);
          if (checkNode) {
            printNeighbourNode(neighbourNode);

            if (checkNode->isEqual(*neighbourNode)) {
              std::cout << "inNodesExplored if condition " << std::endl;
              inNodesExplored = true;
              std::cout << "inNodesExplored: " << nodesExplored << std::endl;
            } else {
              std::cout << "Nodes are not equal" << std::endl;
            }
          } else {
            std::cout << "checkNode is nullptr" << std::endl;
          }
        }

        return inNodesExplored;

 }

bool PathSolver::checkOpenList(Node* neighbourNode){

  bool inOpenList = false;

        for (int i = 0; i < openList->getLength(); ++i) {
          std::cout << "in openList for loop, checking node " << i << std::endl;
          Node* checkNode = openList->getNode(i);
          if (checkNode) {
           printCheckNode(checkNode);
            printNeighbourNode(neighbourNode);

            if (checkNode->isEqual(*neighbourNode)) {
              std::cout << "inOpenList if condition " << std::endl;
              inOpenList = true;
              std::cout << "inOpenList: " << inOpenList << std::endl;
            } else {
              std::cout << "Nodes are not equal" << std::endl;
            }
          } else {
            std::cout << "checkNode is nullptr" << std::endl;
          }
        }
        return inOpenList;
}

void PathSolver::printClosedList(NodeList* closedList) {
  std::cout << "PRINTING OUT closedLIST" << std::endl;
  for (int i = 0; i < closedList->getLength(); ++i) {
    Node* currentNode = closedList->getNode(i);
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
}

void PathSolver::printOpenList(NodeList* openList) {
  std::cout << "PRINTING OUT openLIST" << std::endl;
  for (int i = 0; i < openList->getLength(); ++i) {
    Node* currentNode = openList->getNode(i);
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
}

void PathSolver::printCurrentNode(Node* currentNode) {
  std::cout << "Current node (" << currentNode->getRow() << ", "
            << currentNode->getCol() << ") with distance traveled "
            << currentNode->getDistanceTraveled() << std::endl;

  std::cout << "Exploring neighbors of node (" << currentNode->getRow() << ", "
            << currentNode->getCol() << ")" << std::endl;
}

void PathSolver::printNeighbourNode(Node* neighbourNode) {
  std::cout << "Current node neighbour (" << neighbourNode->getRow() << ", "
            << neighbourNode->getCol() << ") with distance traveled "
            << neighbourNode->getDistanceTraveled() << std::endl;
}

void PathSolver::printCheckNode(Node* checkNode) {
  std::cout << "checkNode (row: " << checkNode->getRow()
            << ", col: " << checkNode->getCol()
            << ", dist: " << checkNode->getDistanceTraveled() << ")"
            << std::endl;
}
