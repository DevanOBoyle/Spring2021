#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    uint32_t vertices; //number of vertices
    bool undirected; //checks whether the graph is undirected or not
    bool visited[VERTICES]; //array to tell which vertices have been visited
    uint32_t matrix[VERTICES][VERTICES]; //matrix for the graph
} Graph;

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph)); //allocates memory for the graph
    if (G) {
        G->undirected = undirected;
        G->vertices = vertices;
        for (uint32_t i = 0; i < G->vertices; i++) {
            G->visited[i] = false; //sets all of the vertices to unvisited
            for (uint32_t j = 0; j < G->vertices; j++) {
                G->matrix[i][j] = 0; //sets 0 to all values in the matrix
            }
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    if (*G) {
        free(*G); //frees the memory allocated for the graph
        *G = NULL; //sets the graph to null
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices; //returns the number of vertices in the graph
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < 0 || i > VERTICES || j < 0 || j > VERTICES) { //if the vertices are not within bounds
        return false;
    }
    G->matrix[i][j] = k; //sets the edge to the weight k
    if (G->undirected == true) { //if the graph is undirected
        G->matrix[j][i] = k; //then it adds the value of vertex j going to i
    }
    return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i >= 0 && i < VERTICES && j >= 0 && j < VERTICES
        && G->matrix[i][j]
               > 0) { //if the vertices are within bounds and the edge weight is greater than 0
        return true;
    } else {
        return false;
    }
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i < 0 || i > VERTICES || j < 0 || j > VERTICES
        || G->matrix[i][j]
               == 0) { //if the vertices are not within bounds or if there is no edge weight
        return 0;
    } else {
        return G->matrix[i][j]; //otherwise returns the edge weight from vertex i to j
    }
}

bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v]; //returns whether vertex v has been visited or not
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v >= 0 && v < VERTICES) { //if vertex v is within bounds
        G->visited[v] = true; //sets vertex v as visited
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v >= 0 && v < VERTICES) { //if vertex v is within bounds
        G->visited[v] = false; //sets vertex v as unvisited
    }
}

void graph_print(Graph *G) {
    //iterates through the matrix
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%u ", G->matrix[i][j]); //prints out each edge weight in the matrix
        }
        printf("\n"); //indents each row
    }
}
