#ifndef __JRB_GRAPH__
#define __JRB_GRAPH__

#include "libfdr/jrb.h"
typedef JRB Graph;

Graph createGraph(int sizemax);
void addEdge(Graph g, char *v1, char *v2);
int adjacent(Graph g, char *v1, char *v2);
int getAdjacentVertices(Graph g, char *v, char *output[]);
void dropGraph(Graph g);

#endif