#include "PathSolver.h"

#include <iostream>

PathSolver::PathSolver() {
  openList = new NodeList();
  nodesExplored = new NodeList();
}

PathSolver::~PathSolver() {
  delete openList;
  delete nodesExplored;
}

// Main function to execute forward search algorithm
void PathSolver::forwardSearch(Env env) {
  int startRow, startCol, goalRow, goalCol;
  int rows, cols;
  if (!getEnvDimensions(env, rows, cols)) {
    std::cerr << "Error: Invalid environment dimensions." << std::endl;
    return;
  }

  if (!findStartAndGoal(env, rows, cols, startRow, startCol, goalRow,
                        goalCol)) {
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
bool PathSolver::findStartAndGoal(Env env, int rows, int cols, int& startRow,
                                  int& startCol, int& goalRow, int& goalCol) {
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
void PathSolver::processNodes(Env env, int rows, int cols, Node* startNode,
                              Node* goalNode) {
  int dx[] = {-1, 1, 0, 0};  // Up, Down, Left, Right
  int dy[] = {0, 0, -1, 1};  // Up, Down, Left, Right

  const int POSSIBLE_MOVES = 4;
  bool goalReached = false;
  Node* currentNode = startNode;

  int goalRow = goalNode->getRow();
  int goalCol = goalNode->getCol();

  while (openList->getLength() > 0 && !goalReached) {
    currentNode = openList->getNodeWithMinEstimatedDist(goalNode);

    if (currentNode->getRow() == goalRow && currentNode->getCol() == goalCol) {
      nodesExplored->addElement(
          // Add a copy to nodesExplored
          new Node(*currentNode));
      goalReached = true;
    } else {
      nodesExplored->addElement(
          // Add a copy to nodesExplored
          new Node(*currentNode));
      addNeighbors(env, rows, cols, currentNode, dx, dy, POSSIBLE_MOVES);

      NodeList* newOpenList = new NodeList();
      for (int i = 0; i < openList->getLength(); ++i) {
        if (!openList->getNode(i)->isEqual(*currentNode)) {
          newOpenList->addElement(new Node(*openList->getNode(i)));
        }
      }
      openList = newOpenList;
    }
  }

  // if (goalReached) {
  //   std::cout << "Goal reached!" << std::endl;
  // } else {
  //   std::cout << "No path found!" << std::endl;
  // }
}

// Function to check neighbors and add valid ones to the open list
void PathSolver::addNeighbors(Env env, int rows, int cols, Node* currentNode,
                              int dx[], int dy[], int possibleMoves) {
  for (int i = 0; i < possibleMoves; ++i) {
    int newRow = currentNode->getRow() + dx[i];
    int newCol = currentNode->getCol() + dy[i];

    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
      if (env[newRow][newCol] != SYMBOL_WALL) {
        Node* neighborNode =
            new Node(newRow, newCol, currentNode->getDistanceTraveled() + 1);

        if (!nodesExplored->contains(neighborNode) &&
            !openList->contains(neighborNode)) {
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
  return deepCopy;
}

// Execute backtracking and get a DEEP COPY of the path the robot should travel
NodeList* PathSolver::getPath(Env env) {
  NodeList* nodesExploredCopy = getNodesExplored();
  if (nodesExploredCopy == nullptr) {
    std::cerr << "Error: nodesExplored is nullptr or empty." << std::endl;
  }

  NodeList* path = initializePath(nodesExploredCopy);
  traceBackPath(nodesExploredCopy, path);

  NodeList* reversedPath = reversePath(path);

  // Clean up memory
  delete path;
  delete nodesExploredCopy;

  // printPath(reversedPath);
  return reversedPath;
}

// Function to initialize the path and get the goal node
NodeList* PathSolver::initializePath(NodeList* nodesExploredCopy) {
  NodeList* path = new NodeList();
  Node* goalNode =
      nodesExploredCopy->getNode(nodesExploredCopy->getLength() - 1);
  Node* currentNode = goalNode;
  path->addElement(new Node(*currentNode));
  return path;
}

// Function to trace back the path from goal to start
void PathSolver::traceBackPath(NodeList* nodesExploredCopy, NodeList* path) {
  Node* currentNode = path->getNode(0);
  bool reachedStart = false;

  while (!reachedStart) {
    Node* nextNode = findNextNode(nodesExploredCopy, currentNode);
    if (nextNode != nullptr) {
      currentNode = nextNode;
      path->addElement(new Node(*currentNode));
    }

    if (currentNode->getDistanceTraveled() == 0) {
      reachedStart = true;
    }
  }
}

// Helper function to find the next node in the path
Node* PathSolver::findNextNode(NodeList* nodesExploredCopy, Node* currentNode) {
  Node* nextNode = nullptr;
  int minDistance = currentNode->getDistanceTraveled();
  bool foundNextNode = false;

  for (int i = 0; i < nodesExploredCopy->getLength() && !foundNextNode; ++i) {
    Node* neighbor = nodesExploredCopy->getNode(i);
    int distance = neighbor->getDistanceTraveled();

    if (distance == minDistance - 1 &&
        ((abs(neighbor->getRow() - currentNode->getRow()) == 1 &&
          neighbor->getCol() == currentNode->getCol()) ||
         (abs(neighbor->getCol() - currentNode->getCol()) == 1 &&
          neighbor->getRow() == currentNode->getRow()))) {
      nextNode = neighbor;
      foundNextNode = true;
    }
  }
  return nextNode;
}

// Function to reverse the path
NodeList* PathSolver::reversePath(NodeList* path) {
  NodeList* reversedPath = new NodeList();
  for (int i = path->getLength() - 1; i >= 0; --i) {
    reversedPath->addElement(new Node(*path->getNode(i)));
  }
  return reversedPath;
}

// Function to print the path for debugging
void PathSolver::printPath(NodeList* path) {
  std::cout << "Reversed Path:" << std::endl;
  for (int i = 0; i < path->getLength(); ++i) {
    Node* node = path->getNode(i);
    std::cout << "(" << node->getRow() << "," << node->getCol() << ") ";
  }
  std::cout << std::endl;
}
