/**
 * @file cppfunctions.h
 * @brief C++ functions header file
 * @details Contains extern "C" declarations for C++ functions and normal C++ functions
 * @author Fatih Kaptan
 * @date October 19, 2025
 */

#ifndef _CPPFUNCTIONS_H_
#define _CPPFUNCTIONS_H_


/**
 * @brief C linkage block for C++ functions callable from C
 */
#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     * @brief C++ function with C linkage
     * @param a First parameter
     * @param b Second parameter
     */
    void cpp_function(int a, int b);
    
#ifdef __cplusplus
}
#endif

/**
 * @brief Print global variable function
 */
void print_my_global(void);

/**
 * @brief Print global variable from C++ library
 */
void print_my_global_cpplib(void);
#endif
