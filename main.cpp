#include "parser.hpp"
#include "state.hpp"

#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>

static std::string ReadFile(const char* fileName)
{
    std::ifstream file(fileName);
    if (file.is_open())
    {
        std::ostringstream ss;
        ss << file.rdbuf();
        file.close();
        if (ss.str() == "")
        {
            std::cerr << "File is empty! file: " << fileName << std::endl;
            return std::string("");
        }
        return ss.str();
    } 
    else {
        std::cerr << "Cannot open file: " << fileName << std::endl;
        return std::string("");
    }
}

int main(int argc, char** argv) 
{
    if (argc < 2) 
    {
        std::cerr << "No input file name, unable to proceed";
        return -1;
    }

    std::string code = ReadFile(argv[1]);
    if (code == "") 
    {
        return -1;
    }

    std::vector<Command*> commands;
    std::unordered_map<std::string, size_t> labels;
    tie(commands, labels) = parse(code);
    std::vector<Command*> commands_to_exec;
    
    bool is_before_begin = true;
    for (auto* cmd : commands)
    {
        if (cmd->type() != CMDTYPE::CMDBEGIN && is_before_begin)
        {
            continue;
        }
        is_before_begin = false;
        commands_to_exec.push_back(cmd);
    }

    State state(commands_to_exec, labels);
    state.run();

    std::cout << "Program ended" << std::endl;
    return 0;
}
