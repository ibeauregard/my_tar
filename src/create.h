#ifndef CREATE_H
#define CREATE_H

#include "params.h"
#include "tar_node.h"
#include <stdbool.h>

int create(Params *params, bool append, TarNode *existingHeaders);

#endif
