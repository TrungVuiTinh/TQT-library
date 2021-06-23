#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weightedGraphlib.h"

#define INFINITIVE_VALUE 10000000

Graph createGraph(){
  Graph g = (Graph)malloc(sizeof(struct _Graph));
  if(g==NULL) {
	  printf("NULL, can not allocate mem, abort...\n");
	  return NULL;
  }
  g->vertices = make_jrb();
  g->edges = make_jrb();
  return g;
}

void addVertex(Graph graph, int id, char* name)
{
	JRB vertices  = graph->vertices;
	JRB edges  = graph->edges;
	JRB tree;
	//update vertex
	detailVertex iver = (detailVertex)malloc(sizeof(struct _detailVertex));
	if(iver==NULL) {
	  printf("NULL, can not allocate mem, abort...\n");
	  return;
	}
	iver->name = strdup(name);
	iver->indegreeTree = make_jrb();
	jrb_insert_int(vertices,id,new_jval_v(iver));
	//update edge
	tree = make_jrb();
	jrb_insert_int(edges,id,new_jval_v(tree));
}

char *getVertex(Graph graph, int id)
{
	JRB vnode=jrb_find_int(graph->vertices,id);
	
	if(vnode==NULL) return NULL;
	detailVertex iver = (detailVertex) vnode->val.v;
	
	return iver->name;
}

void addEdge(Graph graph, int v1, int v2, double wei)
{
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB vnode = jrb_find_int(graph->vertices,v2);
	JRB tree;
	if((enode==NULL)||(vnode==NULL)) {
		printf("vertex not found\n");
		return;
    }
	tree=(JRB)(enode->val).v;
	jrb_insert_int(tree,v2,new_jval_d(wei));
	detailVertex iver = (detailVertex) vnode->val.v;
	tree = iver->indegreeTree;
	jrb_insert_int(tree,v1,JNULL);
}
void addEdge2(Graph graph, int v1, int v2, double wei){
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB vnode = jrb_find_int(graph->vertices,v2);
	JRB tree;
	if((enode==NULL)||(vnode==NULL)) {
		printf("vertex not found\n");
		return;
    }
	detailEdge iver2 = (detailEdge)malloc(sizeof(detailEdge));
	iver2->wei = wei;
	iver2->station = make_jrb();
	tree = (JRB)(enode->val).v;
	jrb_insert_int(tree, v2, new_jval_v(iver2));
	detailVertex iver = (detailVertex) vnode->val.v;
	tree = iver->indegreeTree;
	jrb_insert_int(tree,v1,JNULL);
}
void addStation(Graph graph, int v1, int v2, int bus_station){
	JRB enode = jrb_find_int(graph->edges,v1);
	if(enode==NULL) {
		printf("vertex not found\n");
		return;
    }
	JRB tree = jrb_find_int((JRB)(enode->val).v, v2);
	if(tree==NULL){
		printf("edge not found\n");
		return;
	}
	detailEdge iver2 = (detailEdge)(tree->val).v;
	jrb_insert_int(iver2->station, bus_station, JNULL);
}
JRB getStation(Graph graph, int v1, int v2){
	JRB enode = jrb_find_int(graph->edges, v1);
	if(enode==NULL) {
		printf("vertex not found\n");
		return NULL;
    }
	JRB tree = jrb_find_int((JRB)(enode->val).v, v2);
	if(tree == NULL)
		return NULL;
	detailEdge iver2 = (detailEdge)(tree->val).v;
	return iver2->station;
}
int hasStation(Graph graph, int v1, int v2, int bus_station){
	JRB station = getStation(graph, v1, v2);
	if(station == NULL) return 0;
	JRB tmp = jrb_find_int(station, bus_station);
	if(tmp == NULL) return 0;
	return 1;
}
int hasEdge(Graph graph, int v1, int v2)
{
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB tree;
	if(enode==NULL) {
		printf("vertex not found\n");
		return 0;
    	}
    	tree=(JRB)(enode->val).v;
	if(jrb_find_int(tree,v2)!=NULL)
		return 1;
	else return 0;
}
double getEdgeValue2(Graph graph, int v1, int v2)
{
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB tree;

	if(enode==NULL) {
		printf("vertex not found\n");
		return INFINITIVE_VALUE;
    	}
    
    	tree = jrb_find_int((JRB)(enode->val).v,v2);

	if(tree==NULL){
		return INFINITIVE_VALUE;
	}
	detailEdge iver2 = (detailEdge)(tree->val).v;
    	return iver2->wei;
}
double getEdgeValue(Graph graph, int v1, int v2){
	JRB enode = jrb_find_int(graph->edges,v1);
	JRB tree;

	if(enode==NULL) {
		printf("vertex not found\n");
		return INFINITIVE_VALUE;
    	}
    
    	tree = jrb_find_int((JRB)(enode->val).v,v2);

	if(tree==NULL){
		return INFINITIVE_VALUE;
	}

    	return (tree->val).d;
}
int indegree(Graph graph, int v, int* output)
{
	JRB vnode = jrb_find_int(graph->vertices,v);
	JRB tree,node;
	int innum = 0;
	
	if(vnode==NULL) {
		printf("vertex not found\n");
		return 0;
    	}
    	detailVertex iver = (detailVertex) vnode->val.v;
	tree = iver->indegreeTree;
	//traverse tree
	jrb_traverse(node, tree){
		output[innum] = node->key.i;
		innum++;
		//printf("\nnumber innum:%d\n",output[innum-1]);
	}
	return innum;
}
int outdegree(Graph graph, int v, int* output)
{
	JRB enode = jrb_find_int(graph->edges,v);
	JRB tree,node;
	int outnum = 0;
	
	if(enode==NULL) {
		printf("vertex not found\n");
		return 0;
    	}

	tree =(JRB)(enode->val).v;
	//traverse tree
	jrb_traverse(node, tree){
		output[outnum] = node->key.i;
		outnum++;
		//printf("\nnumber innum:%d\n",output[outnum-1]);
	}
	return outnum;
}

void dropGraph(Graph graph)
{
	JRB node,innode;
	detailVertex detailnode;
	
	jrb_traverse(node,graph->edges){
		jrb_free_tree((JRB)jval_v(node->val));
	}
	jrb_free_tree(graph->edges);
	
	jrb_traverse(node,graph->vertices){
		detailnode = (detailVertex) node->val.v;
		free(detailnode->name);
		jrb_free_tree((JRB)detailnode->indegreeTree);
	}
	jrb_free_tree(graph->vertices);
	
	free(graph);
}
