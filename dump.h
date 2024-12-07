#ifndef __DUMP_H__
#define __DUMP_H__

#include <stdio.h>
#include <stdlib.h>

#include "differentiator.h"

int DrawTree(NODE* root);
int DrawNode(NODE* node, FILE* file_ptr);

#endif