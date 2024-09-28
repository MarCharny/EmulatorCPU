#pragma once
#include <cstddef>
#include <string>
#include <stdexcept>

static constexpr size_t REGISTERS_AMOUNT = 4;
class Registers;

class Register
{
public:
    Register(const std::string& reg)
    {
        if (reg == "pc")
        {
            is_pc_ = true;
            return;
        }

        if (reg.length() == 2 && reg[1] == 'x') 
        {
            int idx = reg[0] - 'a';
            if (idx >= 0 && idx < REGISTERS_AMOUNT)
            {
                is_pc_ = false;
                num_ = idx;
            }
            return;
        }

        throw std::runtime_error(std::string("Not defined register: " + reg).c_str());
    }

private:
    bool is_pc_ = false;
    size_t num_;

    friend Registers;
};

class Registers
{
public:
    int gen_regs_[REGISTERS_AMOUNT];
    int pc_;

    Registers()
    {
        for (size_t i = 0; i < REGISTERS_AMOUNT; i++)
        {
            gen_regs_[i] = 0;
        }
        pc_ = 0;
    }

    int& operator[](const Register& reg) { return reg.is_pc_ ? pc_ : gen_regs_[reg.num_]; }
    int operator[](const Register& reg) const { return reg.is_pc_ ? pc_ : gen_regs_[reg.num_]; }

    friend Register;
};
