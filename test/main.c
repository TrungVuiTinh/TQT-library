#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mylib.h"
typedef struct V{
    char name[5];
    int id;
}V;
void MENU(){
    printf("=====================MENU=======================\n");
    printf("1. BFS\n");
    printf("2. DFS\n");
    printf("3. Coloring\n");
    printf("4. Dijkstra\n");
    printf("5. MST\n");
    printf("6. Exit\n");
}
int compare(char *a, char *b){
    int i;
    int count = 0;
    for(i = 0; i < 5; i++){
        if(a[i] != b[i])
            count++;
    }
    return count;
}
void readFile(V *v){
    FILE *pt = fopen("main.txt", "r");
    if(pt == NULL){
        printf("File was not found!!!\n");
        exit(1);
    }
    int i = 1;
    fscanf(pt, "%s", v[0].name);
    v[0].id = i;
    char c = fgetc(pt);
    while(c != EOF){
        fscanf(pt, "%s", v[i].name);
        v[i].id = i + 1;
        i++;
        c = fgetc(pt);
    }
    fclose(pt);
}
void Op1(V *v){
    JRB g = make_jrb();
    Dllist Q = new_dllist();
    int i,j;
    for(i = 0; i < 5757; i++){
        for(j = 0; j < 5757; j++){
            int count = compare(v[i].name, v[j].name);
            if(count == 1){
                setEdge_BFS_DFS(g, v[i].id, v[j].id);
            }
        }
    }
    BFS(g, Q, 1, 5757, 5757);
    jrb_free_tree(g);
    free_dllist(Q);
}
void Op2(V *v){
    JRB g = make_jrb();
    Dllist Q = new_dllist();
    int i,j;
    for(i = 0; i < 5757; i++){
        for(j = 0; j < 5757; j++){
            int count = compare(v[i].name, v[j].name);
            if(count == 1){
                setEdge_BFS_DFS(g, v[i].id, v[j].id);
            }
        }
    }
    DFS(g, Q, 1, 5757, 5757);
    jrb_free_tree(g);
    free_dllist(Q);
}
void Op3(V *v){
    node *g;
    int i, j;
    g = (node *)malloc(5757 * sizeof(node));
    for( i = 0; i < 5757; i++){
        g[i].connect = (int*)calloc(i, sizeof(int));
        g[i].num_connect = 0;
        g[i].color = 0;
    }
    for(i = 0; i < 5757; i++){
        for(j = 0; j < 5757; j++){
            int count = compare(v[i].name, v[j].name);
            if(count == 1){
                nodeConnect(g, v[i].id - 1, v[j].id - 1);
            }
        }
    }
    colorProceed(g, 5757);
    print(g, 5757);
}
void Op4(V *v){
    int i, j, n, output[5757];
    Graph g = createGraph();
    for(i = 0; i < 5757; i++){
        addVertex(g, i + 1, v[i].name);
    }
    for(i = 0; i < 5757; i++){
        for(j = 0; j < 5757; j++){
            int count = compare(v[i].name, v[j].name);
            if(count == 1){
                addEdge(g, v[i].id, v[j].id, 1);
            }
        }
    }
    int length, path[5757];
    int s = 8, t = 339;
    double weight = dijkstra(g, s, t, path, &length);
    if(weight == INFINITIVE_VALUE)
    printf("No path between %s and %s\n", v[s - 1].name, v[t - 1].name);
    else{
        printf("Path between %s and %s:", v[s - 1].name, v[t - 1].name);
        for(i = length; i >= 0; i--) 
            printf(" %s ", v[path[i] - 1].name);
        printf("\nTotal weight: %.2f", weight);
    }
    printf("\n");
    dropGraph(g);
}
void Op5(V *v){
    Graph g = createGraph();
    Graph X = createGraph();
    int i, j;
    for(i = 0; i < 5757; i++){
        addVertex(g, i + 1, v[i].name);
    }
    for(i = 0; i < 5757; i++){
        for(j = 0; j < 5757; j++){
            int count = compare(v[i].name, v[j].name);
            if(count == 1){
                addEdge(g, v[i].id, v[j].id, 1);
            }
        }
    }
    Prim(g, X, 1);
    dropGraph(g);
    dropGraph(X);
}
int main(){
    V *v = (V *)malloc(sizeof(V) * 5757);
    int chon;
    readFile(v);
    do{
        MENU();
        scanf("%d", &chon);
        switch(chon){
            case 1:
            Op1(v);
            break;
        case 2:
            Op2(v);
            break;
        case 3:
            Op3(v);
            break;
        case 4:
            Op4(v);
            break;
        case 5:
            Op5(v);
            break;
        case 6:
            exit(1);
            break;
        default:
            printf("Error\n");
            break;
        }
    }while(chon != 6);
    return 0;
}