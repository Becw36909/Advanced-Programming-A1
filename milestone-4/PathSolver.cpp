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
// void PathSolver::forwardSearch(Env env) {
//     int startRow = -1, startCol = -1, goalRow = -1, goalCol = -1;
//     bool startFound = false, goalFound = false;
//             std::cerr << "inside forwardSearch" << std::endl;


//     // Determine the dimensions of the environment dynamically
//     int rows = 0;
//     int cols = 0;
//     for (int row = 0; env[row] != nullptr; ++row) {
//         ++rows;
//         for (int col = 0; env[row][col] != '\0'; ++col) {
//             if (row == 0) {
//                 ++cols;
//             }
//         }
//     }

//     // Find the start and goal nodes
//     for (int row = 0; row < rows && (!startFound || !goalFound); ++row) {
//         for (int col = 0; col < cols && (!startFound || !goalFound); ++col) {
//             if (env[row][col] == SYMBOL_START) {
//                 startRow = row;
//                 startCol = col;
//                 startFound = true;
//             } else if (env[row][col] == SYMBOL_GOAL) {
//                 goalRow = row;
//                 goalCol = col;
//                 goalFound = true;
//             }
//         }
//     }

//             std::cerr << "found start and goal nodes" << std::endl;

//     Node* startNode = new Node(startRow, startCol, 0);
//                     std::cout << "startNode (" << startNode->getRow() << "," << startNode->getCol() << ") ";

//     Node* goalNode = new Node(goalRow, goalCol, 0);
//                     std::cout << "goalNode (" << goalNode->getRow() << "," << goalNode->getCol() << ") ";


//     if (startFound && goalFound) {
//         openList->addElement(startNode);
//     } else {
//         std::cerr << "Error: Start or goal node not found." << std::endl;
//         delete startNode;
//         delete goalNode;
//         return;
//     }

//     int dx[] = {-1, 1, 0, 0};  // Up, Down, Left, Right
//     int dy[] = {0, 0, -1, 1};  // Up, Down, Left, Right
//     int possibleMoves = 4;
//     bool goalReached = false;
//     Node* currentNode = startNode;

//     while (openList->getLength() > 0 && !goalReached) {
//         currentNode = openList->getNodeWithMinEstimatedDist(goalNode);
//         // std::cout << "currentNode (" << currentNode->getRow() << "," << currentNode->getCol() << ")" << std::endl;

//         if (currentNode->getRow() == goalRow && currentNode->getCol() == goalCol) {
//             nodesExplored->addElement(new Node(*currentNode));  // Add a copy to nodesExplored
//             std::cout << "Goal node added to nodesExplored: (" << currentNode->getRow() << "," << currentNode->getCol() << ")" << std::endl;
//             goalReached = true;
//         } else {
//             nodesExplored->addElement(new Node(*currentNode));  // Add a copy to nodesExplored
//             // std::cout << "Adding to nodesExplored: (" << currentNode->getRow() << "," << currentNode->getCol() << ")" << std::endl;

//             for (int i = 0; i < possibleMoves; ++i) {
//                 int newRow = currentNode->getRow() + dx[i];
//                 int newCol = currentNode->getCol() + dy[i];

//                 if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
//                     if (env[newRow][newCol] != SYMBOL_WALL) {
//                         Node* neighborNode = new Node(newRow, newCol, currentNode->getDistanceTraveled() + 1);

//                         if (!nodesExplored->contains(neighborNode) && !openList->contains(neighborNode)) {
//                             openList->addElement(neighborNode);
//                             // std::cout << "Neighbor added to openList: (" << newRow << "," << newCol << ")" << std::endl;
//                         } else {
//                             delete neighborNode;
//                         }
//                     }
//                 }
//             }

//             NodeList* newOpenList = new NodeList();
//             for (int i = 0; i < openList->getLength(); ++i) {
//                 if (!openList->getNode(i)->isEqual(*currentNode)) {
//                     newOpenList->addElement(new Node(*openList->getNode(i)));
//                 }
//             }
//             openList = newOpenList;
//         }
//     }

//   if (goalReached) {
//     std::cout << "Goal reached!" << std::endl;
//   } else {
//     std::cout << "No path found!" << std::endl;
//   }

//   std::cout << "nodesExplored size: " << nodesExplored->getLength() << std::endl;

//   // Cleanup memory
//   delete startNode;
//   delete goalNode;
// }

// Main function to execute forward search algorithm
void PathSolver::forwardSearch(Env env) {
    int startRow, startCol, goalRow, goalCol;
    int rows, cols;
    if (!getEnvDimensions(env, rows, cols)) {
        std::cerr << "Error: Invalid environment dimensions." << std::endl;
        return;
    }

    if (!findStartAndGoal(env, rows, cols, startRow, startCol, goalRow, goalCol)) {
        std::cerr << "Error: Start or goal node not found." << std::endl;
        return;
    }

    Node* startNode = new Node(startRow, startCol, 0);
    Node* goalNode = new Node(goalRow, goalCol, 0);
    openList->addElement(startNode);

    processNodes(env, rows, cols, startNode, goalNode);

    delete startNode;
    delete goalNode;
}

// Function to calculate the dimensions of the environment
bool PathSolver::getEnvDimensions(Env env, int& rows, int& cols) {
    rows = 0;
    cols = 0;
    for (int row = 0; env[row] != nullptr; ++row) {
        ++rows;
        for (int col = 0; env[row][col] != '\0'; ++col) {
            if (row == 0) {
                ++cols;
            }
        }
    }
    return rows > 0 && cols > 0;
}

// Function to find the start and goal nodes in the environment
bool PathSolver::findStartAndGoal(Env env, int rows, int cols, int& startRow, int& startCol, int& goalRow, int& goalCol) {
    bool startFound = false, goalFound = false;
    for (int row = 0; row < rows && (!startFound || !goalFound); ++row) {
        for (int col = 0; col < cols && (!startFound || !goalFound); ++col) {
            if (env[row][col] == SYMBOL_START) {
                startRow = row;
                startCol = col;
                startFound = true;
            } else if (env[row][col] == SYMBOL_GOAL) {
                goalRow = row;
                goalCol = col;
                goalFound = true;
            }
        }
    }
    return startFound && goalFound;
}

// Function to process nodes and execute the forward search algorithm
void PathSolver::processNodes(Env env, int rows, int cols, Node* startNode, Node* goalNode) {
    int dx[] = {-1, 1, 0, 0};  // Up, Down, Left, Right
    int dy[] = {0, 0, -1, 1};  // Up, Down, Left, Right
    int possibleMoves = 4;
    bool goalReached = false;
    Node* currentNode = startNode;

    int goalRow = goalNode->getRow();
    int goalCol = goalNode->getCol();

    while (openList->getLength() > 0 && !goalReached) {
        currentNode = openList->getNodeWithMinEstimatedDist(goalNode);

        if (currentNode->getRow() == goalRow && currentNode->getCol() == goalCol) {
            nodesExplored->addElement(new Node(*currentNode));  // Add a copy to nodesExplored
            goalReached = true;
        } else {
            nodesExplored->addElement(new Node(*currentNode));  // Add a copy to nodesExplored
            addNeighbors(env, rows, cols, currentNode, dx, dy, possibleMoves);

            NodeList* newOpenList = new NodeList();
            for (int i = 0; i < openList->getLength(); ++i) {
                if (!openList->getNode(i)->isEqual(*currentNode)) {
                    newOpenList->addElement(new Node(*openList->getNode(i)));
                }
            }
            openList = newOpenList;
        }
    }

    if (goalReached) {
        std::cout << "Goal reached!" << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }
    std::cout << "nodesExplored size: " << nodesExplored->getLength() << std::endl;
}


// Function to check neighbors and add valid ones to the open list
void PathSolver::addNeighbors(Env env, int rows, int cols, Node* currentNode, int dx[], int dy[], int possibleMoves) {
    for (int i = 0; i < possibleMoves; ++i) {
        int newRow = currentNode->getRow() + dx[i];
        int newCol = currentNode->getCol() + dy[i];

        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
            if (env[newRow][newCol] != SYMBOL_WALL) {
                Node* neighborNode = new Node(newRow, newCol, currentNode->getDistanceTraveled() + 1);

                if (!nodesExplored->contains(neighborNode) && !openList->contains(neighborNode)) {
                    openList->addElement(neighborNode);
                } else {
                    delete neighborNode;
                }
            }
        }
    }
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

  return deepCopy;
}

// Execute backtracking and Get a DEEP COPY of the path the
// robot should travel
// To be implemented for Milestone 3
NodeList* PathSolver::getPath(Env env) {
    std::cout << "in getPath()" << std::endl;

    // Get a deep copy of the nodesExplored list
    NodeList* nodesExploredCopy = getNodesExplored();

    std::cout << "in getPath() past nodesExploredCopy" << std::endl;

    if (nodesExploredCopy == nullptr || nodesExploredCopy->getLength() == 0) {
        std::cerr << "Error: nodesExplored is nullptr or empty." << std::endl;
        delete nodesExploredCopy; // Cleanup in case of error
        return nullptr;
    }

    // Initialize an empty NodeList for the path
    NodeList* path = new NodeList();

    std::cout << "in getPath() initialised path list" << std::endl;
    std::cout << "nodesExploredCopy size: " << nodesExploredCopy->getLength() << std::endl;

    // Get the goal node from nodesExplored (assumed to be the last node)
    Node* goalNode = nodesExploredCopy->getNode(nodesExploredCopy->getLength() - 1);
    // std::cout << "goalNode (" << goalNode->getRow() << "," << goalNode->getCol() << ") " << std::endl;

    Node* currentNode = goalNode;
    // std::cout << "currentNode (" << currentNode->getRow() << "," << currentNode->getCol() << ") " << std::endl;

    path->addElement(new Node(*currentNode));  // Add the goal node to the path

    bool reachedStart = false;

    // Loop until we reach the starting node
    while (!reachedStart) {
        Node* nextNode = nullptr;
        int minDistance = currentNode->getDistanceTraveled();
        // std::cout << "Current node: (" << currentNode->getRow() << "," << currentNode->getCol() << ") with distance " << minDistance << std::endl;
bool foundNextNode = false;

        // Iterate through nodesExplored to find the next node in reverse path
        for (int i = 0; i < nodesExploredCopy->getLength(); ++i) {
            Node* neighbor = nodesExploredCopy->getNode(i);
            int distance = neighbor->getDistanceTraveled();
            // std::cout << "Checking neighbor: (" << neighbor->getRow() << "," << neighbor->getCol() << ") with distance " << distance << std::endl;

            // Check if neighbor node is one step closer to current node
            if (distance == minDistance - 1 &&
                ((abs(neighbor->getRow() - currentNode->getRow()) == 1 && neighbor->getCol() == currentNode->getCol()) ||
                 (abs(neighbor->getCol() - currentNode->getCol()) == 1 && neighbor->getRow() == currentNode->getRow()))) {
                nextNode = neighbor;
foundNextNode = true;            }
        }

        // If nextNode found, update currentNode and add it to the path
        if (foundNextNode && nextNode != nullptr) {
            currentNode = nextNode;
            // std::cout << "Next node: (" << currentNode->getRow() << "," << currentNode->getCol() << ")" << std::endl;
            path->addElement(new Node(*currentNode));
        } 


        // Check if we have reached the starting node
        if (currentNode->getDistanceTraveled() == 0) {
            reachedStart = true;
        }
    }

    std::cout << "passed getPath() while loop" << std::endl;

    // Reverse the path to start from the starting node
    // Initialize an empty NodeList for reversed path
    NodeList* reversedPath = new NodeList();
    // Add nodes in reverse order
    for (int i = path->getLength() - 1; i >= 0; --i) {
        reversedPath->addElement(new Node(*path->getNode(i)));
    }

    // Clean up memory used by path NodeList
    delete path;
    delete nodesExploredCopy;

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



