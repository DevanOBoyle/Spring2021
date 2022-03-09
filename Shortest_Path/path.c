#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Path {
    Stack *vertices; //stack to hold the vertices
    uint32_t length; //holds the length of the path
} Path;

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path)); //allocates memory for the path
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
    }
    return p;
}

void path_delete(Path **p) {
    if ((*p) && (*p)->vertices) {
        stack_delete(&(*p)->vertices); //deletes the stack
        free(*p); //frees the memory allocated for the path
        *p = NULL; //sets the path to null
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t i = 0;
    stack_peek(p->vertices, &i); //peeks the stack to get the previous value
    bool pushed = stack_push(p->vertices, v); //pushes the vertex onto the stack
    if (pushed == true) { //if the vertex was successfully pushed
        p->length += graph_edge_weight(G, i, v); //add the edge weight to the length of the path
        return true;
    }
    return false;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t i = 0;
    bool popped = stack_pop(p->vertices, v); //pops from the stack
    stack_peek(p->vertices, &i); //peeks the stack to get the previous value
    if (popped == true) { //if the vertex was successfully popped
        if (stack_size(p->vertices) != 0) { //if the stack isn't empty
            p->length -= graph_edge_weight(G, i,
                *v); //subtract the path from v to the previus vertex from the total path length
        }
        return true;
    }
    return false;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices); //returns the number of vertices
}

uint32_t path_length(Path *p) {
    return p->length; //returns the length of the path
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length; //sets the length of the source to the length of the destination
    stack_copy(dst->vertices, src->vertices); //copies the stack
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path: "); //starts to print the path
    stack_print(p->vertices, outfile, cities); //prints the stack
}
