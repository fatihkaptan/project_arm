/**********************************************************************************************************************
 * File Name    : r_typedefs.h
 * Description  : Typedefs for portability.
 *********************************************************************************************************************/

/***********************************************************************************************************************
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

#include <stddef.h>
#include <stdint.h>
#include <math.h>

#ifndef RENESAS_APPLICATION_SYSTEM_INC_R_TYPEDEFS_H_
    #define RENESAS_APPLICATION_SYSTEM_INC_R_TYPEDEFS_H_

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/


/* in case <stdio.h> has defined it. */
#ifndef NULL
#define NULL 0
#endif

/******************************************************************************
Macro definitions
******************************************************************************/
#if !defined(__bool_true_false_are_defined) && !defined(__cplusplus)

#define     false 0
#define     true  1

#endif

/* Avoid unused parameter warning in code */
#define     UNUSED_PARAM(param)             (void)(param)

/* Avoid unused variable warning in code */
#define     UNUSED_VARIABLE(param)          (void)(param)

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef char                char_t;
typedef unsigned int        bool_t;
typedef int                 int_t;
typedef int                 ssize_t;

/* typedef signed char         int8_t;   defined stdint.h */
/* typedef signed short        int16_t;  defined stdint.h */
/* typedef signed long         int32_t;  defined stdint.h */
/* typedef signed long long    int64_t;  defined stdint.h */

typedef unsigned int        uint_t;

/* typedef unsigned char       uint8_t;   defined stdint.h */
/* typedef unsigned short      uint16_t;  defined stdint.h */
/* typedef unsigned long       uint32_t;  defined stdint.h */
/* typedef unsigned long long  uint64_t;  defined stdint.h */

typedef float               float32_t;
typedef double              float64_t;
typedef long double         float128_t;


/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif /* RENESAS_APPLICATION_SYSTEM_INC_R_TYPEDEFS_H_ */
