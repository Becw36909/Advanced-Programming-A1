#ifndef COSC_ASSIGN_ONE_NODELIST
#define COSC_ASSIGN_ONE_NODELIST

#include "Node.h"
#include "Types.h"

class NodeList {
 public:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // Constructor/Destructor
  NodeList();
  ~NodeList();

  // Copy Constructor
  // Produces a DEEP COPY of the NodeList
  NodeList(NodeList& other);

  // Number of elements in the NodeList
  int getLength();

  // Add a COPY node element to the BACK of the nodelist.
  void addElement(Node* newNode);

  // Get a pointer to the ith node in the node list
  Node* getNode(int i);

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

  // Finds & returns a node in the NodeList
  // with min estimated dist to given goal node.
  Node* getNodeWithMinEstimatedDist(Node* goalNode);

  // Checks if a given node exists in the NodeList.
  bool contains(Node* node);

 private:
  /*                                           */
  /* DO NOT MOFIFY THESE VARIABLES             */
  /*                                           */

  // Milestone 4 change for nodes list.
  Node** nodes;

  // Number of nodes currently in the NodeList
  int length;

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

  // Indicates the maximum number of nodes the NodeList
  // can hold before needing to resize.
  int capacity;

  // Doubles the capacity of the internal array to
  // accommodate more nodes.
  void resize();
};

#endif  // COSC_ASSIGN_ONE_NODELIST