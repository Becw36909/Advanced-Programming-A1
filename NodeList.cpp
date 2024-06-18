#include "NodeList.h"
#include <iostream>

// Constructor
NodeList::NodeList()
{
    length = 0;
}


// Destructor
NodeList::~NodeList()
{
    // TODO
}

// Copy Constructor
// Produces a DEEP COPY of the NodeList
NodeList::NodeList(NodeList &other)
{
    // Set the length of the new NodeList to be the same as 
    // the original NodeList
    length = other.length;
    
    // Iterate over each Node in the original NodeList
    for (int i = 0; i < length; ++i) {
        // Create a new Node object that is a copy of the 
        // original Node
        nodes[i] = new Node(*other.nodes[i]);
    }
}

// Number of elements in the NodeList
int NodeList::getLength()
{
    return length;
}

// Add a COPY node element to the BACK of the nodelist.
void NodeList::addElement(Node *newPos)
{
    if (length < NODE_LIST_ARRAY_MAX_SIZE)
    {
        nodes[length] = new Node(*newPos);
        ++length;
    }
    else {
        std::cerr << "Error: NodeList is full." << std::endl;
    }
}

// Get a pointer to the ith node in the node list
Node *NodeList::getNode(int i)
{
    Node *result = nullptr;

    if (i >= 0 && i < length)
    {
        result = nodes[i];
    }
    else
    {
        std::cerr << "Error: Index out of bounds." << std::endl;
    }

    return result;
}

// Function to compare two Node objects
// bool Node::isEqual(Node &other) {
//     return (row == other.row && col == other.col &&
//             dist_traveled == other.dist_traveled);
// }

// The below may be able to be removed
// Equality comparison operator
// bool Node::operator==(Node &other) {
//   return (row == other.row && col == other.col &&
//           dist_traveled == other.dist_traveled);
// }

// void NodeList::removeElement(Node* node) {
//     for (int i = 0; i < length; ++i) {
//          if (*nodes[i] == *node) {
//             // Delete the node
//             delete nodes[i]; 
//             // Set the pointer to nullptr
//             nodes[i] = nullptr; 

//             // Exit the function after deleting the node
//             return; 
//         }
//     }
// }


void NodeList::removeElement(Node* node) {
    for (int i = 0; i < length; ++i) {
        if (*nodes[i] == *node) {
            delete nodes[i];
            // Shift remaining elements to fill the gap
            for (int j = i; j < length - 1; ++j) {
                nodes[j] = nodes[j + 1];
            }
            --length;
            return;
        }
    }
}

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

bool NodeList::contains(Node* node) {
    bool found = false;
    for (int i = 0; i < this->length && !found; ++i) {
        if (this->nodes[i]->isEqual(*node)) {
            found = true;
        }
    }
    return found;
}

