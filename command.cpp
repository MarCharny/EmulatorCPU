#include "command.hpp"
#include "state.hpp"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>

void BEGIN::run(State& state) const {}

void END::run(State& state) const 
{
    state.regs_.pc_ = state.code_.size();
}

void POP::run(State& state) const 
{
    state.stack_.pop();
}

void ADD::run(State& state) const 
{
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    state.stack_.push(l + r);
}

void SUB::run(State& state) const 
{
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    state.stack_.push(l - r);
}

void MUL::run(State& state) const
{
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    state.stack_.push(l * r);

    //debug
    std::cout << "MUL RES: " << std::to_string(state.stack_.top()) << std::endl;
}

void DIV::run(State& state) const
{
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    state.stack_.push(l / r);
}

void OUT::run(State& state) const 
{
    std::cout << state.stack_.pop() << std::endl;
}

void NPOUT::run(State& state) const
{
    std::cout << state.stack_.top() << std::endl;
}

void IN::run(State& state) const 
{
    int val;
    if (std::cin >> val) { state.stack_.push(val); }
    else { throw std::runtime_error("Wrong input, unable to proceed"); }
}

void RET::run(State& state) const 
{
    state.regs_.pc_ = state.call_stack_.pop();
}

void PUSH::run(State& state) const 
{
    state.stack_.push(val);
}

void PUSHR::run(State& state) const
{
    state.stack_.push(state.regs_[reg]);
}

void POPR::run(State& state) const 
{
    state.regs_[reg] = state.stack_.pop();
}

void JMP::run(State& state) const 
{
    check(state);
    state.regs_.pc_ = state.labels_.at(label);     
}
void JMP::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void JEQ::run(State& state) const 
{
    check(state);
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    if (l == r) { state.regs_.pc_ = state.labels_.at(label); }
}

void JEQ::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void JNE::run(State& state) const 
{
    check(state);
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    if (l != r) { state.regs_.pc_ = state.labels_.at(label); }
}

void JNE::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void JA::run(State& state) const
{
    check(state);
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    if (l > r) { state.regs_.pc_ = state.labels_.at(label); }
}

void JA::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void JAE::run(State& state) const
{
    check(state);
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    if (l >= r) { state.regs_.pc_ = state.labels_.at(label); }
}

void JAE::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void JB::run(State& state) const 
{
    check(state);
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    if (l < r) { state.regs_.pc_ = state.labels_.at(label); }
}

void JB::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void JBE::run(State& state) const 
{
    check(state);
    auto r = state.stack_.pop();
    auto l = state.stack_.pop();
    if (l <= r) { state.regs_.pc_ = state.labels_.at(label); }
}

void JBE::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void CALL::run(State& state) const 
{
    check(state);
    state.call_stack_.push(state.regs_.pc_);
    state.regs_.pc_ = state.labels_.at(label);

    std::cout << label << " " << std::to_string(state.regs_.pc_) << std::endl;
}

void CALL::check(State st) const
{
    if (!st.labels_.count(label)) { throw std::runtime_error(std::string("Undefined label: " + label).c_str()); }
}

void ST::run(State& state) const
{
    std::cout << "STACK: " << state.stack_.print() << std::endl;
}