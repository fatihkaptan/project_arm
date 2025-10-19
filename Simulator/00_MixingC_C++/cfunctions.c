/**
 * @file cfunctions.c
 * @brief C functions implementation
 * @details Contains C functions and shows how to call C++ functions from C
 * @author Fatih Kaptan
 * @date October 19, 2025
 */

#include <stdint.h>
#include <stdio.h>
#include "cfunctions.h"
#include "cppfunctions.h"

/**
 * @brief String display function implementation
 * @param text String to display
 */
void C_DisplayString(const uint8_t *text)
{
    printf("%s\n", text);
}

/**
 * @brief C library function implementation
 * @param a First parameter (unused)
 * @param b Second parameter (unused)
 */
void c_function(int a, int b)
{
    printf("[c_function]: Hello fromm C, i'm a library :) \n");
    
    // Call C++ function from C.
    // C-linkage on "cpp_function" is required.
    cpp_function(a, b);
}
