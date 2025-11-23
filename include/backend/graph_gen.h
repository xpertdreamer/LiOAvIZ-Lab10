//
// Created by IWOFLEUR on 29.10.2025.
//

#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include <iomanip>
#include <iostream>
#include <vector>

struct Graph {
    int** adj_matrix;
    std::vector<std::vector<std::pair<int, int>>> adj_list;
    int n;
};

/**
 * Function for allocating memory for a graph with edge generating probabilities
 * @param n Graph size
 * @param edgeProb Edge generating probability
 * @param loopProb Loop edge generating probability
 * @param seed Seed for random generator
 * @param weighted Value that determines whether the graph is weighted
 * @param directed Value that determines whether the graph is directed
 * @return New Graph
 */
extern Graph create_graph(int n, double edgeProb = 0.4, double loopProb = 0.15, unsigned int seed = 0, bool weighted = false, bool directed = false);

// Function to display the matrix
extern void print_matrix(int **matrix, int rows, int cols, const char *name);

// Free matrix memory
extern void delete_graph(Graph& graph, int n);

// Display adj list
extern void print_list(const std::vector<std::vector<std::pair<int, int>>> &list, const char *name);

/**
 * Breadth First Search (BFS) algorithm for finding distances from a source vertex
 * @param graph Graph being examined
 * @param start_v Start vertex
 * @return Vector of distances
 */
extern std::vector<int> find_distances(const Graph& graph, int start_v);

/**
 * BFS Helper Function
 * @param graph Graph being examined
 * @param start_v Start vertex
 * @param DIST Vector of distances
 */
extern void BFSD(const Graph& graph, int start_v, std::vector<int>& DIST);

/**
 * Distance vector output
 * @param DIST Vector of distances
 * @param start_v Start vector
 */
extern void print_distances(const std::vector<int>& DIST, int start_v);

/**
 * Calculating the distance matrix between all pairs of vertices using BFS
 * @param graph Processed graph
 * @return Distances matrix n x n
 */
extern std::vector<std::vector<int>> build_distance_matrix(const Graph& graph);


extern std::vector<int> compute_eccentricities(const std::vector<std::vector<int>>& dist_matrix);


extern int compute_radius(const std::vector<int>& ecc);
#endif //GRAPH_GEN_H
