#pragma once

#include "command.hpp"
#include "parser.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <cwctype>
#include <stdexcept>

static void skip_wspace(const std::string& s, int& i) {

    while (i < s.size() && iswspace(s[i]))
    {
        ++i;
    }
}

static std::string parse_word(const std::string& s, int& i) 
{
    std::string word;
    while (i < s.size() && !iswspace(s[i])) 
    {
        word.push_back(s[i]);
        ++i;
    }
    return word;
}

static std::pair<std::vector<Command*>, std::unordered_map<std::string, size_t>> parse(const std::string& s)
{
    std::vector<Command*> commands;
    std::unordered_map<std::string, size_t> labels;
    bool is_found_begin = false;
    bool is_found_end = false;

    for (int i = 0; i < s.size(); i++) 
    {
        skip_wspace(s, i);
        if (i == s.size()) { break; }

        if (s[i] == '.')
        {
            auto label = parse_word(s, i);
            if (label.back() != ':') { throw std::runtime_error(std::string("Wrong label definition: " + label).c_str()); }
            if (labels.count(label)) { throw std::runtime_error(std::string("Redefinition of label: " + label).c_str()); }
            label.pop_back();
            labels[label] = commands.size();
        } else 
        {
            auto command_name = parse_word(s, i);

            if (command_name == "BEGIN") {
                commands.push_back(new BEGIN());
                is_found_begin = true;
            } else if (command_name == "END") {
                commands.push_back(new END());
                is_found_end = true;
            } else if (command_name == "POP") {
                commands.push_back(new POP());
            } else if (command_name == "ADD") {
                commands.push_back(new ADD());
            } else if (command_name == "SUB") {
                commands.push_back(new SUB());
            } else if (command_name == "MUL") {
                commands.push_back(new MUL());
            } else if (command_name == "DIV") {
                commands.push_back(new DIV());
            } else if (command_name == "OUT") {
                commands.push_back(new OUT());
            } else if (command_name == "IN") {
                commands.push_back(new IN());
            } else if (command_name == "RET") {
                commands.push_back(new RET());
            } else if (command_name == "NPOUT") {
                commands.push_back(new NPOUT());
            } else if (command_name == "PUSH") {
                skip_wspace(s, i);
                int arg = std::stoi(parse_word(s, i));
                commands.push_back(new PUSH(arg));
            } else if (command_name == "PUSHR") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new PUSHR(arg));
            } else if (command_name == "POPR") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new POPR(arg));
            } else if (command_name == "JMP") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new JMP(arg));
            } else if (command_name == "JEQ") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new JEQ(arg));
            } else if (command_name == "JNE") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new JNE(arg));
            } else if (command_name == "JA") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new JA(arg));
            } else if (command_name == "JAE") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new JAE(arg));
            } else 
            if (command_name == "JB") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new JB(arg));
            } else if (command_name == "JBE") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new JBE(arg));
            } else if (command_name == "CALL") {
                skip_wspace(s, i);
                auto arg = parse_word(s, i);
                commands.push_back(new CALL(arg));
            } else if (command_name == "ST") {
                commands.push_back(new ST());
            } else {
                throw std::runtime_error(std::string("Command not found!" + command_name).c_str());
            }
        }
    }

    if (!is_found_begin) { throw std::runtime_error("Not found BEGIN command, unable to proceed!"); }
    if (!is_found_end) { throw std::runtime_error("Not found END command, unable to proceed!"); }

    return std::make_pair(commands, labels);
}

