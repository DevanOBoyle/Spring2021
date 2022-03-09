//Devan O'Boyle
//Assignment 4: The Circumnavigations of Denver Long

#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK   4096
#define OPTIONS "hvui:o:"

//depth first search function based on Eugene Chou's pseudocode that he provided during his lab section
void DFS(Graph *g, uint32_t v, Path *c, Path *s, char *cities[], uint32_t vertices, uint32_t *calls,
    FILE *outfile, bool verbose) {
    graph_mark_visited(g, v); //marks the incoming vertex as visited
    path_push_vertex(c, v, g); //pushes the vertex onto the path
    *calls += 1; //increments the number of recursive calls
    for (uint32_t w = 0; w < graph_vertices(g);
         w++) { //iterates through the other vertices that v may connect to
        if (graph_has_edge(g, v, w)
            && (graph_visited(g, w)
                == false)) { //if there is an edge at v and w and w hasn't been visited yet
            if (path_length(c) < path_length(s)
                || path_length(s)
                       == 0) { //if the current path is shorter than the shortest path assuming the shortest path isn't 0
                DFS(g, w, c, s, cities, vertices, calls, outfile,
                    verbose); //calls itself recursively with vertex w as the new parameter
            }
        }
    }
    if (path_vertices(c) == vertices
        && graph_has_edge(g, v, 0)) { //if the current path is Hamiltonian
        path_push_vertex(c, 0, g); //push the origin vertex to go at the end
        if (path_length(c) < path_length(s)
            || path_length(s) == 0) { //if the current path is the shortest
            path_copy(s, c); //make the current path the new shortest path
            if (verbose
                == true) { //if verbose printing is enabled, print out each Hamiltonian path found
                printf("Path length: %u\n", path_length(c));
                path_print(c, outfile, cities);
            }
        }
        path_pop_vertex(c, &v, g);
    }

    path_pop_vertex(
        c, &v, g); //pops the last vertex from the pather to move back to find other paths
    graph_mark_unvisited(g, v); //marks the last vertex as unvisited so that other paths can find it
}

int main(int argc, char **argv) {
    bool verbose = false; //if enabled, prints out all Hamiltonian paths found
    bool undirected = false; //if enabled, makes the graph undirected
    FILE *infile = stdin; //stores the input file, defaults to standard input
    FILE *outfile = stdout; //stores the output file, defaults to standard output
    char buffer[BLOCK]; //stores the buffer
    uint32_t num_vertices = 0; //total number of vertices
    uint32_t recursive_calls = 0; //number of times the DFS function calls itself
    int e, j, k, c;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //prints out the help message
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS.\n\n");
            printf("USAGE\n");
            printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -u             Use undirected graph.\n");
            printf("  -v             Enable verbose printing\n");
            printf("  -h             Program usage and help\n");
            printf("  -i infile      Input containing graph (default: stdin)\n");
            printf("  -o outfile     Output of computed path (default: stdout)\n");
            return 1;
        case 'v': verbose = true; break; //enables verbose printing
        case 'u': undirected = true; break; //enables the graph to be undirected
        case 'i':
            infile = fopen(optarg, "r"); //opens the input file to read from
            if (infile == NULL) {
                fprintf(
                    stderr, "failed to open %s \n", optarg); //prints an error if the file is null
                return 1;
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w"); //opens the output file to write to
            if (outfile == NULL) {
                fprintf(
                    stderr, "failed to open %s \n", optarg); //prints an error if the file is null
                return 1;
            }
            break;
        }
    }
    fscanf(infile, "%d\n", &num_vertices); //reads in the number of vertices
    if (num_vertices < 1 || num_vertices > VERTICES) { //checks that each vertex is within range
        fprintf(stderr, "invalid number of cities"); //prints an error if not
        return 1;
    }
    char *cities[num_vertices];
    for (uint32_t i = 0; i < num_vertices; i++) {
        fgets(buffer, BLOCK, infile); //takes input for the city names
        cities[i] = strdup(buffer);
        cities[i][strlen(cities[i]) - 1] = 0; //removes the newline at the end of the string
    }
    Graph *graph = graph_create(num_vertices, undirected);
    uint32_t places = 0;
    while ((c = fscanf(infile, "%d %d %d\n", &e, &j, &k))
           != EOF) { //reads each vertice until the end of file is reached
        if (c != 3) { //if there are not three values provided
            printf("Error: malformed line.\n"); //error is printed and program exits
            return 1;
        }
        graph_add_edge(graph, e, j, k); //adds each edge to the graph
        places += 1;
    }
    if (places <= 1) {
        fprintf(outfile, "There's nowhere to go.\n");
        return 1;
    }
    fclose(infile); //closes the input file
    Path *shortest = path_create(); //initializes a path to store the shortest path
    Path *current = path_create(); //initializes a pth to store the current path
    DFS(graph, 0, current, shortest, cities, num_vertices, &recursive_calls, outfile,
        verbose); //calls the depth first search function
    fprintf(outfile, "Path length: %u\n", path_length(shortest));
    path_print(shortest, outfile, cities);
    fprintf(outfile, "Total recursive calls: %u\n", recursive_calls);
    for (uint32_t i = 0; i < num_vertices; i++) {
        free(cities[i]); //frees the memory allocated for the cities
    }
    path_delete(&current); //deletes the current path
    path_delete(&shortest); //deletes the shortest path
    graph_delete(&graph); //deletes the graph
    fclose(outfile); //closes the output file
    return 0;
}
