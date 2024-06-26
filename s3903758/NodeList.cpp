#include "NodeList.h"

#include <iostream>

// Constructor
NodeList::NodeList() {
  // Initial capacity
  capacity = 10;
  length = 0;
  nodes = new Node *[capacity];
}

// Destructor
NodeList::~NodeList() {
  for (int i = 0; i < length; ++i) {
    // Clean up each Node object
    delete nodes[i];
  }
  // Clean up the array of pointers
  delete[] nodes;
}

// Copy Constructor
// Produces a DEEP COPY of the NodeList
NodeList::NodeList(NodeList &other) {
  // Initialize the capacity and length of the new NodeList to match the
  // original
  this->capacity = other.capacity;
  this->length = other.length;

  // Allocate memory for the new array of Node pointers
  this->nodes = new Node *[capacity];

  // Iterate over each Node in the original NodeList
  for (int i = 0; i < length; ++i) {
    // Create a new Node object that is a copy of the original Node
    this->nodes[i] = new Node(*other.nodes[i]);
  }
}

// Number of elements in the NodeList
int NodeList::getLength() { return length; }

// Add a COPY node element to the BACK of the nodelist.
void NodeList::addElement(Node *newNode) {
  if (length == capacity) {
    // Ensure capacity is sufficient
    resize();
  }
  // Add the pointer to the new node
  nodes[length++] = newNode;
}

// Get a pointer to the ith node in the node list
Node *NodeList::getNode(int i) {
  Node *result = nullptr;

  if (i >= 0 && i < length) {
    result = nodes[i];
  } else {
    std::cerr << "Error: Index out of bounds." << std::endl;
  }

  return result;
}

// Finds and returns a pointer to the node in the NodeList
// with the min estimated distance to the given goal node.
Node *NodeList::getNodeWithMinEstimatedDist(Node *goalNode) {
  Node *minNode = nullptr;

  if (length != 0) {
    minNode = nodes[0];
    int minEstDistance = nodes[0]->getEstimatedDist2Goal(goalNode);

    for (int i = 1; i < length; ++i) {
      int estDistance = nodes[i]->getEstimatedDist2Goal(goalNode);
      if (estDistance < minEstDistance) {
        minNode = nodes[i];
        minEstDistance = estDistance;
      }
    }
  }

  return minNode;
}

// Checks if a given node exists in the NodeList.
bool NodeList::contains(Node *node) {
  bool found = false;
  for (int i = 0; i < length && !found; ++i) {
    if (nodes[i]->isEqual(*node)) {
      found = true;
    }
  }
  return found;
}

// Doubles the capacity of the internal array to accommodate more nodes.
void NodeList::resize() {
  // Double the capacity
  int newCapacity = capacity * 2;
  Node **newNodes = new Node *[newCapacity];

  // Copy existing elements to the new array
  for (int i = 0; i < length; ++i) {
    newNodes[i] = nodes[i];
  }

  // Clean up old nodes array
  delete[] nodes;

  // Update capacity and nodes pointer
  nodes = newNodes;
  capacity = newCapacity;
}
