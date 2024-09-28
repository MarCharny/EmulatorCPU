#pragma once

#include <string>
#include "registers.hpp"

class State;

enum CMDTYPE {
    CMDBEGIN, 
    CMDEND,
    DEFAULT
};

class Command 
{
    public:
        virtual ~Command() {}
        virtual void run(State& state) const = 0;
        virtual CMDTYPE type() const = 0;
};

class BEGIN : public Command 
{
    public: 
        BEGIN() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::CMDBEGIN; };
};

class END : public Command
{
    public:
        END() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::CMDEND; };
};

class POP : public Command 
{
public:
       POP() {}
       void run(State& state) const override;
       CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class ADD : public Command 
{
    public:
        ADD() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class SUB : public Command 
{
    public:
        SUB() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class MUL : public Command 
{
    public:
        MUL() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class DIV : public Command
{
    public:
        DIV() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class OUT : public Command
{
    public:
        OUT() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class NPOUT : public Command
{
public:
    NPOUT() {}
    void run(State& state) const override;
    CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class IN : public Command
{
    public:
        IN() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class RET : public Command
{
    public:
        RET() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};

class PUSH : public Command
{
    public:
        PUSH(int val) : val(val) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        int val;
};

class PUSHR : public Command
{
    public:
        PUSHR(const std::string& r) : reg(r) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        Register reg;
};

class POPR : public Command 
{
    public:
        POPR(const std::string& r) : reg(r) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        Register reg;
};

class JMP : public Command
{
    public:
        JMP(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class JEQ : public Command
{
    public:
        JEQ(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class JNE : public Command 
{
    public:
        JNE(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class JA : public Command
{
    public:
        JA(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class JAE : public Command
{
    public:
        JAE(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class JB : public Command 
{
    public:
        JB(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class JBE : public Command 
{
    public:
        JBE(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class CALL : public Command
{
    public:
        CALL(const std::string& label) : label(label) {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };

    private:
        std::string label;
        void check(State st) const;
};

class ST : public Command
{
    public: 
        ST() {}
        void run(State& state) const override;
        CMDTYPE type() const override { return CMDTYPE::DEFAULT; };
};