// Created by IWOFLEUR on 19.10.2025

#include "../../include/backend/graph_gen.h"

#include <chrono>

Graph create_graph(const int n, const double edgeProb, const double loopProb,
                    const unsigned int seed, const bool weighted, const bool directed) {
    Graph graph;
    graph.n = n;

    // Matrix memory allocating
    graph.adj_matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        graph.adj_matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            graph.adj_matrix[i][j] = 0;
        }
    }

    // List initialization
    graph.adj_list.resize(n);

    static unsigned int counter = 0;
    const auto now = std::chrono::high_resolution_clock::now();
    const auto nanos = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
    unsigned int state = seed == 0 ? static_cast<unsigned int>(nanos) + counter++ : seed;

        for (int i = 0; i < n; i++) {
        for (int j = directed ? 0 : i; j < n; j++) {
            if (!directed && j < i) continue;

            state = (state * 1664525 + 1013904223) & 0x7fffffff;
            const int rand_value = static_cast<int>(state) % 100;

            if (i == j) {
                if (rand_value < static_cast<int>(loopProb * 100)) {
                    if (weighted) {
                        state = (state * 1664525 + 1013904223) & 0x7fffffff;
                        int weight = (static_cast<int>(state) % 10) + 1;
                        graph.adj_matrix[i][j] = weight;
                        graph.adj_list[i].emplace_back(i, weight);
                    } else {
                        graph.adj_matrix[i][j] = 1;
                        graph.adj_list[i].emplace_back(i, 1);
                    }
                }
            } else {
                if (rand_value < static_cast<int>(edgeProb * 100)) {
                    if (weighted) {
                        state = (state * 1664525 + 1013904223) & 0x7fffffff;
                        int weight = (static_cast<int>(state) % 10) + 1;

                        graph.adj_matrix[i][j] = weight;
                        graph.adj_list[i].emplace_back(j, weight);

                        if (!directed) {
                            graph.adj_matrix[j][i] = weight;
                            graph.adj_list[j].emplace_back(i, weight);
                        }
                    } else {
                        graph.adj_matrix[i][j] = 1;
                        graph.adj_list[i].emplace_back(j, 1);

                        if (!directed) {
                            graph.adj_matrix[j][i] = 1;
                            graph.adj_list[j].emplace_back(i, 1);
                        }
                    }
                }
            }
        }
    }

    return graph;
}

void print_matrix(int **matrix, const int rows, const int cols, const char *name) {
    if (!matrix || rows <= 0 || cols <= 0) {
        std::cout << "Invalid matrix parameters" << std::endl;
        return;
    }

    std::cout << name << ":" << std::endl;

    // Calculate maximum width needed for numbers
    int max_num_width = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (const int num_width = static_cast<int>(std::to_string(matrix[i][j]).length()); num_width > max_num_width) {
                max_num_width = num_width;
            }
        }
    }

    // Calculate width for row indices
    const int row_index_width = static_cast<int>(std::to_string(rows - 1).length());
    max_num_width = std::max(max_num_width, 2);

    // Print column headers with dynamic spacing
    std::cout << std::setw(row_index_width + 2) << " ";
    for (int j = 0; j < cols; j++) {
        std::cout << std::setw(max_num_width + 1) << j;
    }
    std::cout << std::endl;

    // Print separator line
    std::cout << std::setw(row_index_width + 2) << " " << "+";
    for (int j = 0; j < cols; j++) {
        std::cout << std::string(max_num_width + 1, '-');
    }
    std::cout << std::endl;

    // Print matrix rows with borders
    for (int i = 0; i < rows; i++) {
        std::cout << std::setw(row_index_width) << i << " |";
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(max_num_width + 1) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

void delete_graph(Graph& graph, const int n) {
    for (int i = 0; i < n; i++) {
        delete[] graph.adj_matrix[i];
    }
    delete[] graph.adj_matrix;
    graph.adj_matrix = nullptr;
    graph.n = 0;
    graph.adj_list.resize(0);
}

void print_list(const std::vector<std::vector<std::pair<int, int>>> &list, const char* name) {
    std::cout << name << ":" << std::endl;
    for (int i = 0; i < list.size(); i++) {
        std::cout << i << ": ";
        for (const auto&[fst, snd] : list[i]) {
            std::cout << "(" << fst << ", " << snd << ") ";
        }
        std::cout << std::endl;
    }
}