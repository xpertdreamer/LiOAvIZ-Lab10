#include "../include/adapters/console_adapter.h"

struct GraphParameters {
    bool is_weight;
    bool is_directed;
};

GraphParameters parse_args(int argc, char **argv);
void print_help(const char* program_name);

int main(const int argc, char *argv[]) {
    try {
        const GraphParameters params = parse_args(argc, argv);
        GraphConsoleAdapter console(params.is_weight, params.is_directed);
        console.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch(...) {
        std::cerr << "Unknown exception" << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}

GraphParameters parse_args(const int argc, char **argv) {
    static const std::unordered_map<std::string, std::function<void(GraphParameters&)>> options = {
        {"-w", [](GraphParameters& params) { params.is_weight = true; }},
        {"--weighted", [](GraphParameters& params) { params.is_weight = true; }},
        {"-d", [](GraphParameters& params) { params.is_directed = true; }},
        {"--directed", [](GraphParameters& params) {params.is_directed = true; }}
    };

    GraphParameters params{false, false};

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            print_help(argv[0]);
        }

        if (auto it = options.find(arg); it != options.end()) {
            it->second(params);
        } else {
            if (arg != "-h" && arg != "--help") std::cerr << "Unknown option: " << arg << "\nUse -h for help" <<
                                                std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return params;
}

void print_help(const char* program_name) {
    std::cout << "Usage: " << program_name << " [OPTIONS]\n"
          << "Options:\n"
          << "  -w, --weighted    Use weighted graph\n"
          << "  -d, --directed    Use directed graph\n"
          << "  -h, --help        Show this help message\n\n"
          << "Examples:\n"
          << "  " << program_name << " -w -d    # Weighted directed graph\n"
          << "  " << program_name << " --weighted    # Weighted undirected graph\n"
          << "  " << program_name << "          # Unweighted undirected graph\n";
}