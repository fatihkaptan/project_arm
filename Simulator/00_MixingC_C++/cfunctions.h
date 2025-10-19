/**
 * @file cfunctions.h
 * @brief C functions header file
 * @details Contains extern "C" declarations for C functions to be called from C++
 * @author Fatih Kaptan
 * @date October 19, 2025
 */

#ifndef _CFUNCTIONS_H_
#define _CFUNCTIONS_H_


/**
 * @brief C linkage block start
 */
#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief String display function
     * @param text String to display
     */
    void C_DisplayString(const uint8_t *text);
    
    /**
     * @brief C library function example
     * @param a First parameter
     * @param b Second parameter
     */
    void c_function(int a, int b);
        
/**
 * @brief C linkage block end
 */
#ifdef __cplusplus
}
#endif


#endif
