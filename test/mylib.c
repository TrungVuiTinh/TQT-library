#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylib.h"
//  DFS va BFS 
void setEdge_BFS_DFS(JRB tree, int vertex1, int vertex2){
    JRB tmp, ls;
    tmp = jrb_find_int(tree, vertex1);
    if(tmp == NULL){
        ls = make_jrb();
        jrb_insert_int(ls, vertex2, new_jval_i(vertex2));
        jrb_insert_int(tree, vertex1, new_jval_v(ls));
    }
    else{
        ls = (JRB)jval_v(tmp->val);
        jrb_insert_int(ls, vertex2, new_jval_i(vertex2));
    }
}
void BFS(JRB tree, Dllist Queue, int begin, int cancel, int size){
    int *visited = malloc((size + 1) * sizeof(int));
    int i, vertex;
    Dllist w;
    JRB checked, ls, tmp;
    for(i = 1; i <= size; i++)
        visited[i] = 0;
    visited[begin] = 2;
    dll_append(Queue, new_jval_i(begin));
    while(!dll_empty(Queue)){
        w = dll_first(Queue);
        i = jval_i(w->val);
        if(i == cancel){
            printf("%d\n", i);
            break;
        }
        dll_delete_node(w);
        ls = jrb_find_int(tree, i);
        checked = (JRB)jval_v(ls->val);
        if(visited[i] != 1){
            printf("%d\n", i);
            visited[i] = 1;
            jrb_traverse(tmp, checked){
                vertex = jval_i( tmp->val);
                if(visited[vertex] == 0){
                    dll_append(Queue, new_jval_i(vertex));
                    visited[vertex] = 2;
                }
            }
        }
    }
}
void DFS(JRB tree, Dllist Queue, int begin, int cancel, int size){
    int *visited = malloc((size + 1) * sizeof(int));
    int i, vertex;
    Dllist w;
    JRB checked, ls, tmp;
    for(i = 1; i <= size; i++)
        visited[i] = 0;
    visited[begin] = 2;
    dll_append(Queue, new_jval_i(begin));
    while(!dll_empty(Queue)){
        w = dll_first(Queue);
        i = jval_i(w->val);
        if(i == cancel){
            printf("%d\n", i);
            break;
        }
        dll_delete_node(w);
        ls = jrb_find_int(tree, i);
        checked = (JRB)jval_v(ls->val);
        if(visited[i] != 1){
            printf("%d\n", i);
            visited[i] = 1;
            jrb_traverse(tmp, checked){
                vertex = jval_i( tmp->val);
                if(visited[vertex] == 0){
                    dll_append(Queue, new_jval_i(vertex));
                    visited[vertex] = 2;
                }
            }
        }
    }
}

//Tim duong di ngan nhat (Dijkstra)
void relax(Graph g, int u, int v, double setd[], int setparent[]){
    if(setd[v] > setd[u] + getEdgeValue(g, u, v)){
        setd[v] = setd[u] + getEdgeValue(g, u, v);
        setparent[v] = u;
    }
}
int extractMin(Dllist q, double setd[]){
    Dllist tmp, check;
    int u;
    double min = INFINITIVE_VALUE + 1;
    check = q->flink;
    u = check->val.i;
    dll_traverse(tmp, q){
    if(setd[tmp->val.i] < min){
        min = setd[tmp->val.i];
        u = tmp->val.i;
        check = tmp;
        }
    }
    dll_delete_node(check);
    return u;
}
double dijkstra(Graph g, int s, int t, int path[], int *length){
    int u;
    JRB tmp;
    int output[5758] = {};
    double setd[5758] = {};
    int setparent[5758] = {};
    Dllist pq = new_dllist();
    jrb_traverse(tmp, g->vertices){
        setd[tmp->key.i] = INFINITIVE_VALUE;
        setparent[tmp->key.i] = -1;
        dll_append(pq, new_jval_i(tmp->key.i));
    }
    setd[s] = 0;
    while(!dll_empty(pq)){
        u = extractMin(pq, setd);
        int n = outdegree(g, u, output);
        int i;
        for(i = 0; i < n; i++){
            relax(g,u,output[i],setd,setparent);
        }
    }
    if(setd[t] == INFINITIVE_VALUE){
        free_dllist(pq);
        return INFINITIVE_VALUE;
    }
    int count = 0;
    int parent = t;
    double weight = setd[t];
    while(parent != s){
        path[count] = parent;
        parent = setparent[parent];
        count++;
    }
    path[count] = s;
    *length = count;
    free_dllist(pq);
    return weight;
}
//Thuat toan to mau
void chooseColor(int i, char *s){
    switch (i){
    case 0:
        strcpy(s, "White");
        break;
    case 1:
        strcpy(s, "Yellow");
        break;
    case 2:
        strcpy(s, "Blue");
        break;
    case 3:
        strcpy(s, "Red");
        break;
    case 4:
        strcpy(s, "Green");
        break;
    case 5:
        strcpy(s, "Black");
        break;
    case 6:
        strcpy(s, "Teal");
        break;
    case 7:
        strcpy(s, "Brown");
        break;
    case 8:
        strcpy(s, "Azure");
        break;
    case 9:
        strcpy(s, "Ivory");
        break;
    case 10:
        strcpy(s, "Silver");
        break;
    case 11:
        strcpy(s, "Purple");
        break;
    case 12:
        strcpy(s, "Navyblue");
        break;
    case 13:
        strcpy(s, "Peagreen");
        break;
    case 14:
        strcpy(s, "Gray");
        break;
    case 15:
        strcpy(s, "Orange");
        break;
    case 16:
        strcpy(s, "Maroon");
        break;
    case 17:
        strcpy(s, "Charcoal");
        break;
    case 18:
        strcpy(s, "Aquamarine");
        break;
    case 19:
        strcpy(s, "Coral");
        break;
    case 20:
        strcpy(s, "Fuchsia");
        break;
    case 21:
        strcpy(s, "Wheat");
        break;
    case 22:
        strcpy(s, "Lime");
        break;
    case 23:
        strcpy(s, "Crimson");
        break;
    case 24:
        strcpy(s, "Khaki");
        break;
    case 25:
        strcpy(s, "Hot pink");
        break;
    case 26:
        strcpy(s, "Magenta");
        break;
    case 27:
        strcpy(s, "Golden");
        break;
    case 28:
        strcpy(s, "Plum");
        break;
    case 29:
        strcpy(s, "Olive");
        break;
    case 30:
        strcpy(s, "Cyan");
        break;
    case 31:
        strcpy(s, "lightbrown");
        break;
    case 32:
        strcpy(s, "lightgreen");
        break;
    case 33:
        strcpy(s, "lightblue");
        break;
    case 34:
        strcpy(s, "darkbrown");
        break;
    case 35:
        strcpy(s, "darkgreen");
        break;
    case 36:
        strcpy(s, "darkblue");
        break;
    default:
        strcpy(s, "white");
        break;
    }
}
void nodeConnect(node *g, int v1, int v2){
    int min, max;
    min = v1 < v2 ? v1 : v2;
    max = v2 > v1 ? v2 : v1;
    int size = g[max].num_connect;
    g[max].connect[size++] = min;
    g[max].num_connect = size;
}

void colorProceed(node *g, int maxVertex){
    int i, j, v, size;
    for(i = 0; i < maxVertex; i++){
        size = g[i].num_connect;
        for(j = 0; j < size; j++){
            v = g[i].connect[j];
            if(g[i].color == g[v].color){
                g[i].color = g[i].color + 1;
                j = -1;
            }
        }
    }
}
void print(node *g, int maxVertex){
    FILE *fp = fopen( "graphz.dot", "w");
    int i, j, size;
    char tmp[10];
    if(fp == NULL){
        printf("Error\n");
        exit(1);
    }
    fprintf(fp, "graph dothi\n{\n");
    for( i = 0; i < maxVertex; i++){
        chooseColor(g[i].color, tmp);
        fprintf(fp, "\t%d [fillcolor=%s, style=filled];\n", i + 1, tmp);
    }
    for(i = 1; i <= maxVertex; i++){
        size = g[i].num_connect;
        for(j = 0; j < size; j++){
            fprintf(fp, "\t%d -- %d\n", i + 1, g[i].connect[j] + 1);
        }
    }
    fprintf(fp, "}");
    fclose(fp);
}
// MST
void Prim(Graph g, Graph X, int s){
    JRB tmp;
    int u;
    int output[MAX];
    double cost[MAX];
    int pre[MAX];
    Dllist q = new_dllist();
    jrb_traverse(tmp, g->vertices){
        cost[tmp->key.i] = INFINITIVE_VALUE + 1;
        pre[tmp->key.i] = -1;
        dll_append(q, new_jval_i(tmp->key.i));
    }
    cost[s] = 0;
    while(!dll_empty(q)){
        u = extractMin(q, cost);
        int j = outdegree(g, u, output);
        int i;
        for(i = 0; i < j; i++){
            int v = output[i];
            if(cost[v] >  getEdgeValue(g, u, v)){
                cost[v] =  getEdgeValue(g, u, v);
                pre[v] = u;
            }
        }
    }
    int i;
    for(i = 1; i <= 5757; i++){
        addVertex(X, i, getVertex(g, i));
    }
    for(i = 2; i <= 5757; i++){
        if(pre[i] != -1 && hasEdge(X, i, pre[i]) != 1){
            addEdge(X, pre[i], i, cost[i]);
        }
    }
    FILE *pt = fopen("graph.dot", "w");
    if(pt == NULL){
        printf("File was not found\n");
        exit(1);
    }
    fprintf(pt, "graph X\n{\n");
        for(i = 2; i <= 5757; i++){
            if(pre[i] != -1 && hasEdge(X, i, pre[i]) != 1)
                fprintf(pt, "\t%d--%d[label=%lf]\n", pre[i], i, getEdgeValue(X, pre[i], i));
        }
    fprintf(pt, "}");
    fclose(pt);
}