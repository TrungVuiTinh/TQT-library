#include "jval.h"
#include "jrb.h"
#include "dllist.h"
#include "fields.h"
#include "weightedGraphlib.h"
#define MAX 5758
#ifndef mylib_h
#define mylib_h
#endif
typedef struct {
    int color;
    int num_connect;
    int *connect;
}node;
void setEdge_BFS_DFS(JRB tree, int vertex1, int vertex2);
void BFS(JRB tree, Dllist Queue, int begin, int cancel, int size);
void DFS(JRB tree, Dllist Queue, int begin, int cancel, int size);
int extractMin(Dllist q, double setd[]);
void relax(Graph g, int u, int v, double setd[], int setparent[]);
double dijkstra(Graph g, int s, int t, int path[], int *length);
void chooseColor( int i, char *s);
void nodeConnect( node *g, int v1, int v2);
void colorProceed( node *g, int maxVertex);
void print( node *g, int maxVertex);
void Prim(Graph g, Graph X, int s);
