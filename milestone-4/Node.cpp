#include "Node.h"
#include <iostream>

// Constructor to initialize the node with given row,
// column, and distance traveled
Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

// Copy constructor
Node::Node(Node &other) {
    this->row = other.row;
    this->col = other.col;
    this->dist_traveled = other.dist_traveled;
}

Node::~Node()
{
    // No dynamic memory to free or resources to release
}

// Getter method to return the row of the node
int Node::getRow()
{
    return this->row;
}

// Getter method to return the column of the node
int Node::getCol()
{
    return this->col;
}

// Getter method to return the distance traveled by the node
int Node::getDistanceTraveled()
{
    return this->dist_traveled;
}

// Setter method to set the distance traveled by the node
void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

// getter for estimated dist to goal - need to return ->
// Manhatten distance + distance traveled
int Node::getEstimatedDist2Goal(Node *goal) {
  // Calculate the Manhattan distance
  int colDiff = abs(this->col - goal->getCol());
  int rowDiff = abs(this->row - goal->getRow());

  int manhattanDistance = colDiff + rowDiff;
  return this->dist_traveled + manhattanDistance;
}

//--------------------------------

// Function to compare two Node objects
bool Node::isEqual(Node& other) {
    return (row == other.row && col == other.col);
}

// Overloading the == operator so that isEqual works
bool Node::operator==(Node &other) {
  return (row == other.row && col == other.col &&
          dist_traveled == other.dist_traveled);
}