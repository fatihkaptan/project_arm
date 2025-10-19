/**
 * @file cppfunctions.cpp
 * @brief C++ library functions implementation
 * @details Contains C++ library functions and extern global variable usage
 * @author Fatih Kaptan
 * @date October 19, 2025
 */

#include <iostream>
using namespace std;

/** @brief Extern declaration for global variable from main.cpp */
extern const int my_global;

/**
 * @brief Print global variable from C++ library
 */
void print_my_global_cpplib(void)
{
    cout << "my_global (fromm cpp lib) = " << my_global << endl;
}
