#pragma once

#include "registers.hpp"
#include "stack.hpp"
#include "command.hpp"

#include <unordered_map>
#include <vector>

class State 
{
public:
    State(const std::vector<Command*>& cd, const std::unordered_map<std::string, size_t>& labels);
    void run();
    Registers regs_;

    stack::Stack<int> stack_;
    stack::Stack<size_t> call_stack_;
    const std::vector<Command*> code_;
    const  std::unordered_map<std::string, size_t> labels_;
};