#ifndef ENVUTILS_H
#define ENVUTILS_H

#include "Types.h"
//typedef char** Env;

// Dynamically allocates memory for a 2D environment array.

Env make_env(const int rows, const int cols);

// @brief Deletes a dynamically allocated 2D environment array.

void delete_env(Env env, int rows, int cols);

#endif // ENVUTILS_H
