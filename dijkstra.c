/* Basic implementation of Dijkstra's algorithm.
 * A graph is represented as a (symmetric) matrix (the so called adjacency matrix)
 * A path is represented as an (ordered) array listing the sequence of labels of the nodes the path consists of.
 *
TODO output an actual path

ISSUE Path is just a list of the nodes ordered by distance to start_node.
      Example: edges = [(1, 2), (1,2025), (2, 3), (2,4), (3,4)]
               --> path = [00...0 1 2 2025 0]


 * --- gcc -shared -o dijkstra.so -fPIC dijkstra.c ---
 */

#include <stdlib.h>
#include <stdio.h>

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
    struct Node* nodes;
    int* path;
    nodes = calloc(DIM, sizeof(struct Node));
    path = calloc(DIM, sizeof(int));

    // Initialize distances
    for(int i=0; i<DIM; ++i){
        nodes[i].label = i;
        if(i!=start_node){
            nodes[i].dist = -2;
        }else{
            nodes[i].dist = 0;
        }
    }

    int step;
    int current_node;
    for(step=0; step<DIM; ++step){
        // Maybe this for(){if({})} could be replaced by a list?
        for(current_node=0; current_node<DIM; ++current_node){
            if(nodes[current_node].dist==step){
                for(int j=0; j<DIM; ++j){
                    if(graph[DIM*current_node+j]>0&&
                    (nodes[j].dist<0 ||
                    nodes[current_node].dist+1<nodes[j].dist)){
                            nodes[j].dist = nodes[current_node].dist+1;
                    }
                }
            }
        }
    }
    qsort(nodes, DIM, sizeof(struct Node), compare);
    for(int i=0; i<DIM; ++i){
        if(nodes[i].dist>=0 && nodes[i].dist<nodes[end_node].dist){
            path[i] = nodes[i].label;
        }
    }
    free(nodes);
    return path;
}

void free_pointer(int* ptr){
    if (ptr) {
        free(ptr);
    }
}
