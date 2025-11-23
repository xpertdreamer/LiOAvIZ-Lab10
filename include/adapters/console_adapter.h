//
// Created by IWOFLEUR on 13.10.2025.
//

#ifndef CONSOLE_ADAPTER_H
#define CONSOLE_ADAPTER_H

#define SILENCE_COUT_BEGIN \
std::streambuf* __cout_original_buf = std::cout.rdbuf(); \
std::stringstream __cout_silent_buffer; \
std::cout.rdbuf(__cout_silent_buffer.rdbuf());

#define SILENCE_COUT_END \
std::cout.rdbuf(__cout_original_buf);

#include <memory>

#include "../core/console.h"
#include "../backend/graph_gen.h"

class GraphConsoleAdapter {
    public:
    explicit GraphConsoleAdapter(bool is_weighted, bool is_directed,
        const std::string& config_path = "", const std::string& aliases_path = "");
    ~GraphConsoleAdapter();

    void run();

    private:
    Console console;

    bool graphs_created;
    std::unique_ptr<Graph> graph;
    int n;
    bool weighted;
    bool directed;

    void cleanup();
    void register_graph_commands();
    std::string find_config_file(const std::string& filename, const std::vector<std::string>& search_paths);
    std::string get_default_config_path();

    void cmd_create(const std::vector<std::string>& args);
    void cmd_print() const;
    void cmd_clear();
    void cmd_cleanup();
    void cmd_exit();
    void cmd_help(const std::vector<std::string>& args);
    void cmd_history();
    void cmd_find(const std::vector<std::string>& args) const;
    void cmd_analyse() const;

    static void cmd_smile();
};

#endif //CONSOLE_ADAPTER_H
