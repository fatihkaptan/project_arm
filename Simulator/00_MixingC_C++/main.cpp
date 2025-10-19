/**
 * @file main.cpp
 * @brief C and C++ mixed programming example
 * @details Shows how to use C and C++ functions together with extern "C" linkage
 * @author Fatih Kaptan
 * @date October 19, 2025
 */

#include <cstdint>
#include <iostream>
using namespace std;

#include "cfunctions.h"
#include "cppfunctions.h"
/**
 * @class TEST
 * @brief Wrapper class for string display functions
 */
class TEST
{
public:
    /**
     * @brief Display uint8_t string
     * @param text String to display
     */
    void DisplayString(const uint8_t *text);
    
    /**
     * @brief Display char string
     * @param text String to display
     */
    void DisplayString(const char *text);
};

/** @brief Example uint8_t text */
static const uint8_t *u8_text = (uint8_t*)"C++ uint8_t text";

/** @brief Global variable example */
extern const int my_global = 23; 

/**
 * @brief Main program function
 * @return Program exit code
 */
int main()
{
    TEST TEST_CPP;
    
    // Call C function from C++ 
    // LCD_DisplayString needs C linkage
    // A cast is required
    C_DisplayString((uint8_t*)"To avoid this uint8_t cast, use C++ wrappers");

    // Use C++ wrappers instead
    TEST_CPP.DisplayString("C++ char text");
    TEST_CPP.DisplayString(u8_text);
    
    c_function(1,2);
    print_my_global();
    print_my_global_cpplib();
    return 0;
}

/**
 * @brief uint8_t version of DisplayString
 * @param text String to display
 */
void TEST::DisplayString(const uint8_t *text)
{
    cout << "[uint8_t]:: ";
    C_DisplayString(text); // Calls the C function (C linkage needed)
}

/**
 * @brief char version of DisplayString
 * @param text String to display
 */
void TEST::DisplayString(const char *text)
{
    cout << "[char]:: ";
    DisplayString((uint8_t*) text); // The cast is done here
}

/**
 * @brief C++ function with C linkage
 * @param a First parameter
 * @param b Second parameter
 */
void cpp_function(int a, int b)
{
    // This C++ function needs C linkage to be visible to C applications
    cout << "[cpp_function]: Hello from C++, i'm not a library" << endl;
}
