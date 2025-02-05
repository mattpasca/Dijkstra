+/* Basic implementation of Dijkstra's algorithm.
 * A graph is represented as a (symmetric) matrix (the so called adjacency matrix)
 * A path is represented as an (ordered) array listing the sequence of labels of the nodes the path consists of.
 *
TODO correct the algorithm, handle infninite distances, priority ordering


 * --- gcc -shared -o dijkstra.so -fPIC dijkstra.c ---
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Node{
    int label;
    int dist;
};

// For the qsort function from <stdio.h>
int compare(const void *a, const void *b){
    const struct Node* node_a = (const struct Node*) a;
    const struct Node* node_b = (const struct Node*) b;
    return node_a->dist - node_b->dist;
}

int* dijkstra (int* graph, int DIM, int start_node, int end_node){
    bool* visited;
    struct Node* nodes;
    int* path;
    int max_count;
    visited = calloc(DIM, sizeof(bool));
    nodes = calloc(DIM, sizeof(struct Node));
    path = calloc(DIM, sizeof(int));
    for(int i=0; i<DIM; ++i){
        nodes[i].label = i;
        if(i!=start_node){
            nodes[i].dist = -2; //See condition for update in line 57
        }else{
            nodes[i].dist = 0;
        }
    }
    if(start_node<end_node){
        max_count = end_node;
    }else{
        max_count = DIM + end_node;
    }
    int current_node;
    int increment;
    int modulo_count;
    for(current_node=start_node; current_node<max_count; ++current_node){
        /* The idea behind this loop is wrong. Counter-example:
         * DIM=10, start_node=5, end_node=6, path=(5,1,2,3,6)
         * but the algorithm would deliver increment=0,1 and terminate.
         */
        for(increment=0; increment<abs(start_node-max_count); ++increment){
            modulo_count = (start_node + increment)%DIM;
            if(graph[DIM*(current_node%DIM)+modulo_count]>0 &&
              (!visited[modulo_count] || nodes[current_node].dist+1<nodes[modulo_count].dist)){
              nodes[modulo_count].dist = nodes[current_node].dist + 1;
            }
        }
        visited[current_node] = true;
        if(0<nodes[end_node].dist&&nodes[end_node].dist<=abs(start_node-current_node)){
            break;
        }
    }
    qsort(nodes, DIM, sizeof(struct Node), compare);
    for(int i=0; i<DIM; ++i){
        if(nodes[i].dist<-1){
            path[i] = nodes[i].label;
        }
    }
    free(visited);
    free(nodes);
    return path;
}

void free_pointer(int* ptr){
    if (ptr) {
        free(ptr);
    }
}
