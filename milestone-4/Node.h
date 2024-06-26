#ifndef COSC_ASSIGN_ONE_NODE
#define COSC_ASSIGN_ONE_NODE

#include "Types.h"

class Node {
 public:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // Constructor/Desctructor
  Node(int row, int col, int dist_traveled);
  ~Node();

  // Get row-coodinate of the node
  int getRow();

  // Get column-coodinate of the node
  int getCol();

  // Getter and setter for distance traveled
  int getDistanceTraveled();
  void setDistanceTraveled(int dist_traveled);

  // Getter for estimated dist to goal -
  // returns -> Manhatten distance + distance
  // traveled
  int getEstimatedDist2Goal(Node* goal);

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

  // Copy constructor
  Node(Node& other);

  // Function to compare two Node objects
  bool isEqual(Node& other);

  // Equality comparison operator
  bool operator==(Node& other);

 private:
  /*                                           */
  /* DO NOT MOFIFY THESE VARIABLES             */
  /*                                           */

  int row;
  int col;

  // distance from start node
  int dist_traveled;

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */
};

#endif  // COSC_ASSIGN_ONE_NODE