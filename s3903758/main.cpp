#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "EnvUtils.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"
#include "Types.h"


// Read a environment from standard input.
void readEnvStdin(Env& env, int& rows, int& cols);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, int rows, int cols, NodeList* solution);

int main(int argc, char** argv) {

  // Variables for environment size - choosing number to initialise
  int rows = 0;
  int cols = 0;

  // Load Environment
  Env env = nullptr;

  // Read the environment from standard input
  readEnvStdin(env, rows, cols);

  // Solve using forwardSearch
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
  PathSolver* pathSolver = new PathSolver();
  pathSolver->forwardSearch(env);

  NodeList* exploredPositions = nullptr;
  exploredPositions = pathSolver->getNodesExplored();

  // Get the path
  // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
  NodeList* solution = pathSolver->getPath(env);

  // Print the environment with the solution path
  printEnvStdout(env, rows, cols, solution);

  delete pathSolver;
  delete exploredPositions;
  delete solution;
  // Free the allocated memory for the environment
  delete_env(env, rows, cols);
  return 0;
}

// Read a environment from standard input.
void readEnvStdin(Env& env, int& rows, int& cols) {
  char c;
  int currentRow = 0;
  int currentCol = 0;
  int maxRows = 1;
  int maxCols = 1;

  env = make_env(maxRows, maxCols);

  // To track if moved to a new row
  bool rowEnded = false;

  while (std::cin.get(c)) {
    if (c == '\n') {
      if (currentRow == 0) {
        cols = currentCol;
      }
      currentRow++;
      currentCol = 0;
      // Mark that a row has ended
      rowEnded = true;
      if (currentRow >= maxRows) {
        int newMaxRows = maxRows * 2;
        Env newEnv = make_env(newMaxRows, maxCols);
        for (int i = 0; i < maxRows; ++i) {
          for (int j = 0; j < maxCols; ++j) {
            newEnv[i][j] = env[i][j];
          }
        }
        delete_env(env, maxRows, maxCols);
        env = newEnv;
        maxRows = newMaxRows;
      }
    } else {
      if (currentCol >= maxCols) {
        int newMaxCols = maxCols * 2;
        for (int i = 0; i < maxRows; ++i) {
          char* newRow = new char[newMaxCols];
          for (int j = 0; j < maxCols; ++j) {
            newRow[j] = env[i][j];
          }
          delete[] env[i];
          env[i] = newRow;
        }
        maxCols = newMaxCols;
      }
      env[currentRow][currentCol] = c;
      currentCol++;
      // Mark that still on the same row
      rowEnded = false;
    }
  }

  // Check if the last row was added correctly
  if (!rowEnded) {
    currentRow++;
  }

  rows = currentRow;
  cols = (cols < currentCol) ? currentCol : cols;
}

// Print out the environment with solution path
void printEnvStdout(Env env, int rows, int cols, NodeList* solution) {
  // Loop starts at 2 so that the START and GOAL
  // nodes are not printed over with direction arrows
  const int START_INDEX = 2;

  // Iterate through the solution path NodeList
  for (int i = START_INDEX; i < solution->getLength(); ++i) {
    Node* prevNode = solution->getNode(i - 1);
    Node* currNode = solution->getNode(i);

    if (!prevNode || !currNode) {
      std::cerr
          << "Error: Encountered nullptr node in solution NodeList at index "
          << i - 1 << " or " << i << std::endl;
      return;
    }

    int prevRow = prevNode->getRow();
    int prevCol = prevNode->getCol();
    int currRow = currNode->getRow();
    int currCol = currNode->getCol();

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
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      std::cout << env[row][col];
    }
    // Ensure a new line after each row
    std::cout << std::endl;
  }

  // std::cout << "Finished printing environment." << std::endl;
}

