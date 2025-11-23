//
// Created by IWOFLEUR on 29.10.2025.
//

#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H

#include <iomanip>
#include <iostream>
#include <vector>

/**
 * @brief Structure representing a graph in two forms: adjacency matrix and adjacency list
 *
 * The graph is stored simultaneously as an adjacency matrix (for efficient edge access)
 * and an adjacency list (for efficient neighbor traversal).
 */
struct Graph {
    int** adj_matrix;                                       ///< 2D array representing adjacency matrix
    std::vector<std::vector<std::pair<int, int>>> adj_list; ///< Adjacency list with pairs (vertex, weight)
    int n;                                                  ///< Number of vertices in the graph
};

/**
 * @brief Creates a random graph with specified parameters
 *
 * Generates a graph using a probabilistic approach. For each possible vertex pair,
 * it decides whether an edge should exist based on given probabilities.
 *
 * @param n Number of vertices in the graph (must be > 0)
 * @param edgeProb Probability of creating an edge between two distinct vertices (0.0 - 1.0)
 * @param loopProb Probability of creating a loop (edge from vertex to itself) (0.0 - 1.0)
 * @param seed Seed for random number generator (0 for random seed based on time)
 * @param weighted If true, creates a weighted graph (weights 1-10), else unweighted (all weights = 1)
 * @param directed If true, creates a directed graph, else undirected
 * @return Graph Generated graph
 *
 * @throws std::bad_alloc If unable to allocate memory for adjacency matrix
 *
 * @note For undirected graphs, the adjacency matrix is symmetric
 * @note For weighted graphs, weights are randomly generated in range 1-10
 *
 * @example
 * Graph g1 = create_graph(10, 0.3, 0.1, 123, false, false); // Unweighted undirected
 * Graph g2 = create_graph(8, 0.5, 0.2, 456, true, true);    // Weighted directed
 */
extern Graph create_graph(int n, double edgeProb = 0.4, double loopProb = 0.15,
                         unsigned int seed = 0, bool weighted = false, bool directed = false);

/**
 * @brief Prints a matrix in formatted form
 *
 * Displays a matrix with row and column headers, alignment, and separators.
 * Special values: -1 is displayed as "∞" (infinity/unreachable)
 *
 * @param matrix Pointer to 2D array to print
 * @param rows Number of rows in matrix
 * @param cols Number of columns in matrix
 * @param name Title for matrix output
 *
 * @warning Function validates parameters. If matrix == nullptr or dimensions <= 0,
 *          an error message is printed.
 *
 * @example
 * print_matrix(graph.adj_matrix, 5, 5, "Adjacency Matrix");
 */
extern void print_matrix(int **matrix, int rows, int cols, const char *name);

/**
 * @brief Frees memory occupied by the graph
 *
 * Deletes the adjacency matrix and clears the adjacency list.
 * After calling this function, the graph becomes invalid.
 *
 * @param graph Reference to graph to clean up
 * @param n Number of vertices in graph (for proper matrix memory deallocation)
 *
 * @note Sets graph.adj_matrix to nullptr and graph.n to 0
 * @note Safe to call multiple times on the same graph
 *
 * @example
 * Graph g = create_graph(10);
 * // work with graph...
 * delete_graph(g, 10); // free memory
 */
extern void delete_graph(Graph& graph, int n);

/**
 * @brief Prints the adjacency list of the graph
 *
 * Displays for each vertex its list of neighbors in format (vertex, weight).
 *
 * @param list Adjacency list to print
 * @param name Title for list output
 *
 * @example
 * print_list(graph.adj_list, "Adjacency List");
 * // Output:
 * // 0: (1, 3) (2, 1)
 * // 1: (0, 3) (3, 2)
 * // ...
 */
extern void print_list(const std::vector<std::vector<std::pair<int, int>>> &list, const char *name);

// ============================================================================
// GRAPH ANALYSIS FUNCTIONS BASED ON BFS
// ============================================================================

/**
 * @brief Finds distances from given vertex to all others using BFS
 *
 * Uses Breadth-First Search (BFS) algorithm to compute shortest distances
 * from start vertex to all reachable vertices.
 *
 * @param graph Graph to analyze
 * @param start_v Starting vertex (must be in range [0, graph.n-1])
 * @return std::vector<int> Vector of distances where distances[i] = distance to vertex i,
 *                         or -1 if vertex i is unreachable from start_v
 *
 * @throws std::out_of_range If start_v is outside valid range
 *
 * @note For weighted graphs, considers edge weights when computing distances
 * @note For directed graphs, respects edge direction
 *
 * @example
 * auto dist = find_distances(graph, 0);
 * // dist[3] contains distance from vertex 0 to vertex 3
 */
extern std::vector<int> find_distances(const Graph &graph, int start_v);

/**
 * @brief Implementation of BFS algorithm for distance computation (BFSD)
 *
 * Helper function that performs breadth-first search from given vertex
 * and fills the distance vector DIST.
 *
 * @param graph Graph to traverse
 * @param start_v Starting vertex for traversal
 * @param DIST Distance vector (filled by function). Must be initialized with
 *             size graph.n and values -1
 *
 * @note Modifies DIST vector, setting distances to reachable vertices
 * @note Does not print traversal order (unlike some educational BFS implementations)
 *
 * @see find_distances
 */
extern void BFSD(const Graph &graph, int start_v, std::vector<int> &DIST);

/**
 * @brief Prints distance vector in readable format
 *
 * Displays distances from start vertex to all other vertices,
 * marking unreachable vertices as "unreachable".
 *
 * @param DIST Distance vector to print
 * @param start_v Starting vertex (used only for header)
 *
 * @example
 * print_distances(distances, 0);
 * // Output:
 * // Distances from vertex 0:
 * // Vertex 0: 0
 * // Vertex 1: 3
 * // Vertex 2: unreachable
 */
extern void print_distances(const std::vector<int> &DIST, int start_v);

/**
 * @brief Builds distance matrix between all vertex pairs
 *
 * Computes shortest distances between all pairs of vertices in the graph
 * by repeatedly calling BFS from each vertex.
 *
 * @param graph Graph to analyze
 * @return std::vector<std::vector<int>> n×n matrix where dist_matrix[i][j] contains
 *         distance from vertex i to vertex j, or -1 if j is unreachable from i
 *
 * @note Time complexity: O(n × (n + m)) where m is number of edges
 * @note For large graphs, may be inefficient; consider Floyd-Warshall for dense graphs
 *
 * @example
 * auto dist_matrix = build_distance_matrix(graph);
 * // dist_matrix[2][4] contains distance from vertex 2 to vertex 4
 */
extern std::vector<std::vector<int>> build_distance_matrix(const Graph &graph);

/**
 * @brief Computes eccentricities of all graph vertices
 *
 * Vertex eccentricity is the maximum distance from that vertex to any other
 * reachable vertex in the graph.
 *
 * @param dist_matrix Distance matrix between all vertex pairs
 * @return std::vector<int> Vector of eccentricities where ecc[i] is eccentricity of vertex i,
 *                         or -1 if vertex i is isolated (no reachable vertices)
 *
 * @note For isolated vertices (no edges), eccentricity is -1
 * @note Eccentricity is used to compute graph radius and diameter
 *
 * @see compute_radius, compute_diameter
 */
extern std::vector<int> compute_eccentricities(const std::vector<std::vector<int>> &dist_matrix);

/**
 * @brief Computes graph radius
 *
 *  is the minimum eccentricity among all graph vertices.
 *
 * @param ecc Vector of vertex eccentricities
 * @return int Graph radius, or -1 if graph is completely disconnected (all vertices isolated)
 *
 * @note Radius = min(ecc[i]) for all i where ecc[i] != -1
 *
 * @example
 * // For 3-vertex path: 0-1-2
 * // Eccentricities: [2, 1, 2]
 * // Radius = 1 (vertex 1)
 */
extern int compute_radius(const std::vector<int> &ecc);

/**
 * @brief Computes graph diameter
 *
 * Graph diameter is the maximum eccentricity among all graph vertices.
 *
 * @param ecc Vector of vertex eccentricities
 * @return int Graph diameter, or -1 if graph is completely disconnected
 *
 * @note Diameter = max(ecc[i]) for all i
 *
 * @example
 * // For 3-vertex path: 0-1-2
 * // Eccentricities: [2, 1, 2]
 * // Diameter = 2
 */
extern int compute_diameter(const std::vector<int> &ecc);

/**
 * @brief Finds central vertices of the graph
 *
 * Central vertices are vertices with eccentricity equal to graph radius.
 *
 * @param ecc Vector of vertex eccentricities
 * @param radius Graph radius
 * @return std::vector<int> Vector of central vertex indices
 *
 * @note May return empty vector if radius = -1 (disconnected graph)
 *
 * @see compute_radius
 */
extern std::vector<int> find_central_vertices(const std::vector<int> &ecc, int radius);

/**
 * @brief Finds peripheral vertices of the graph
 *
 * Peripheral vertices are vertices with eccentricity equal to graph diameter.
 *
 * @param ecc Vector of vertex eccentricities
 * @param diameter Graph diameter
 * @return std::vector<int> Vector of peripheral vertex indices
 *
 * @note May return empty vector if diameter = -1 (disconnected graph)
 *
 * @see compute_diameter
 */
extern std::vector<int> find_peripheral_vertices(const std::vector<int> &ecc, int diameter);

/**
 * @brief Prints distance matrix in formatted form
 *
 * Displays distance matrix with headers, alignment, and special
 * notation "∞" for unreachable vertices (-1).
 *
 * @param dist_matrix Distance matrix to print
 *
 * @see build_distance_matrix
 */
extern void print_distance_matrix(const std::vector<std::vector<int>> &dist_matrix);
#endif //GRAPH_GEN_H
