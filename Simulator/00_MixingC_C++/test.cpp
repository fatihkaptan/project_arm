/**
 * @file test.cpp
 * @brief Test functions implementation
 * @details Contains test functions and extern global variable usage example
 * @author Fatih Kaptan
 * @date October 19, 2025
 */

#include <iostream>
using namespace std;

/** @brief Extern declaration for global variable from main.cpp */
extern const int my_global;

/**
 * @brief Print global variable test function
 */
void print_my_global(void)
{
    cout << "my_global = " << my_global << endl;
}
