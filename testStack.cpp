#include <iostream>
#include <cassert>
#include "stack.hpp"

#define _ASSERT(op, str) { \
    if (!(op)) { \
        std::cout << "\033[31m" << "TEST FAILED: " << str << "\033[0m" << std::endl; \
    } else { \
        std::cout << "\033[32m" << "TEST PASSED: " << str << "\033[0m" << std::endl; \
    } \
} \

#define _START_TEST(name) \
        std::cout << "START TEST " << name << std::endl; \

void defaultConstructorTest() 
{
    _START_TEST("Default constructor")
    
    stack::Stack<int> sti;
    _ASSERT(sti.empty(), "1");
    
    stack::Stack<std::string> sts;
    _ASSERT(sts.empty(), "2");
}

void copyConstructorTest() 
{
    _START_TEST("Copy constructor");
    stack::Stack<int> st1;
    for (int i = 0; i < 11; i++) { st1.push(i); }

    stack::Stack<int> st2(st1);
    for (int i = 0; i < 11; i++) { _ASSERT(st2.pop() == 10 - i, "val"); }
    _ASSERT(st2.size() == 0, "size");
}

void copyMoveContructor() 
{
    _START_TEST("Copy move constructor");
    stack::Stack<int> st1;
    for (size_t i = 0; i < 11; i++) { st1.push(i); }

    stack::Stack<int> st2(std::move(st1));
    for (size_t i = 0; i < 11; i++) { _ASSERT(st2.pop() == 10 - i, "val"); }
    _ASSERT(st2.size() == 0, "size");
    try {
        st1.top();
        _ASSERT(false, "try top");
    }
    catch (std::runtime_error&) {
        _ASSERT(true, "try top");
    }
}

void operatorAssigment()
{
    _START_TEST("Assigment operator");
    stack::Stack<int> st1;
    for (size_t i = 0; i < 11; i++) { st1.push(i); }

    stack::Stack<int> st2 = st1;
    for (size_t i = 0; i < 11; i++) { _ASSERT(st2.pop() == 10 - i, "val"); }
    _ASSERT(st2.size() == 0, "size");
}

void operatorMoveAssigment()
{
    _START_TEST("Assigment move operator");
    stack::Stack<int> st1;
    for (size_t i = 0; i < 11; i++) { st1.push(i); }

    stack::Stack<int> st2 = std::move(st1);
    for (size_t i = 0; i < 11; i++) { _ASSERT(st2.pop() == 10 - i, "val"); }
    _ASSERT(st2.size() == 0, "size");
    try {
        st1.top();
        _ASSERT(false, "try top");
  }
    catch (std::runtime_error&) {
        _ASSERT(true, "try top");
    }
}

void topFunction()
{
    _START_TEST("Top function");
    stack::Stack<int> st1;
    for (size_t i = 0; i < 11; i++) 
    { 
        st1.push(i); 
        _ASSERT(st1.top() == i, "");
    }
}

void pushFunction()
{
    _START_TEST("Push function");
    stack::Stack<int> st1;
    for (size_t i = 0; i < 11; i++)
    {
        _ASSERT(st1.push(i) == i, "push");
    }
}

void pushMoveFinction()
{
    std::string str = "str";
    _START_TEST("Push move function");
    stack::Stack<std::string> st1;
    _ASSERT(st1.push(std::move(str)) == "str", "");
}

void popFunction()
{
    _START_TEST("Pop function");
    stack::Stack<int> st1;
    for (size_t i = 0; i < 2; i++)
    {
        st1.push(i);
        _ASSERT(st1.pop() == i, "pop");
    }

    _ASSERT(st1.size() == 0, "size");
}

void emptyFunction()
{
    _START_TEST("Empty function");
    stack::Stack<int> st1;
    st1.push(1);
    _ASSERT(st1.size() == 1, "after push");
    st1.pop();
    _ASSERT(st1.size() == 0, "after pop");
}

int main()
{
    defaultConstructorTest();
    copyConstructorTest();
    copyMoveContructor();
    operatorAssigment();
    operatorMoveAssigment();
    topFunction();
    popFunction();
    pushFunction();
    pushMoveFinction();
    emptyFunction();
}