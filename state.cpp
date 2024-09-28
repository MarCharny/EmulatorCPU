#include "state.hpp"

State::State(const std::vector<Command*>& cd, const std::unordered_map<std::string, size_t>& labels) : code_(cd), labels_(labels) {}

void State::run()
{
    regs_.pc_ = 0;
    while (regs_.pc_ < code_.size())
    {
        ++regs_.pc_;
        code_[regs_.pc_ - 1]->run(*this);
    }
}
