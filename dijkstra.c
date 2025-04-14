/* Basic implementation of Dijkstra's algorithm.
 * A graph is represented as a (symmetric) matrix (the so called adjacency matrix)
 * A path is represented as an array listing the sequence of labels of the nodes the path consists of.
 * 
 * 
 * --- gcc -shared -o dijkstra.so -fPIC dijkstra.c ---
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct node{
    int label;
    int dist;
    int previous;
};

typedef struct node Node;

void path_extractor(Node* nodes, int end_node, int* result_path){
    bool running;
    int next_node;
    int i;

    result_path[0] = end_node;
    next_node = nodes[end_node].previous;
    running = true;
    i = 1;
    while(running==true){
        if(nodes[next_node].dist==0){
            running = false;
        }
        result_path[i] = next_node;
        next_node = nodes[result_path[i]].previous;
        i += 1;
    }

}

int* dijkstra (int* graph, int DIM, int start_node, int end_node){
    Node* nodes;
    int* result_path;
    nodes = calloc(DIM, sizeof(Node));
    result_path = calloc(DIM, sizeof(int));

    // Initialize nodes
    for(int i=0; i<DIM; ++i){
        nodes[i].label = i;
        if(i!=start_node){
            nodes[i].dist = -2; // how do you construct an 'infinity' object?
        }else{
            nodes[i].dist = 0;
        }
    }

    int step;
    int current_node;
    for(step=0; step<DIM; ++step){
        for(current_node=0; current_node<DIM; ++current_node){
            if(nodes[current_node].dist==step){
                for(int j=0; j<DIM; ++j){
                    if(graph[DIM*current_node+j]>0&&
                    (nodes[j].dist<0 ||
                    nodes[current_node].dist+1<nodes[j].dist)){
                            nodes[j].dist = nodes[current_node].dist+1;
                            nodes[j].previous = nodes[current_node].label;
                    }
                }
            }
        }
    }
    path_extractor(nodes, end_node, result_path);
    free(nodes);
    return result_path;
}

void free_pointer(int* ptr){
    if (ptr) {
        free(ptr);
    }
}
