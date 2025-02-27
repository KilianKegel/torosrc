/*++

    toro C Library
    https://github.com/KilianKegel/toro-C-Library#toro-c-library-formerly-known-as-torito-c-library

    Copyright (c) 2017-2025, Kilian Kegel. All rights reserved.
    SPDX-License-Identifier: GNU General Public License v3.0

Module Name:

    exp.c

Abstract:

    Implementation of the Standard C function.
    Calculates the exponential of a floating-point value.

Author:

    Kilian Kegel

--*/
#include <CdeServices.h>

extern const double __cdeLOG2E;
extern double modf(double, double*);
extern double __cde80387F2XM1(double);

/**

Synopsis
    #include <math.h>
    double exp(double);
Description
    https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/exp-expf
Parameters
    https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/exp-expf#parameters
Returns
    https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/exp-expf#return-value

         d    d*ld(e)
        e  = 2       

            dxlde         == d*ld(e)    --> ld() logarithmus dualis

                              intgr(dxlde)
            twoPowerIntgr == 2            
        
                              fract(dxlde)
            twoPowerFract == 2

             d    intgr(dxlde)     fract(dxlde)
        --> e  = 2              * 2

             d
        --> e  = twoPowerIntgr * twoPowerFract
                                                           x
    NOTE:   80387's only exponential function is F2XM1 -> 2  - 1 in the range -1 <= x <= + 1
            
**/
double exp(double d)
{
    double intgr, fract;
    double dxlde = d * __cdeLOG2E;  // product of d and ld(e)
    double twoPowerFract = 0.0;
    double twoPowerIntgr = 0.0;
    CDEDOUBLE* ptwoPowerIntgr = (void*) &twoPowerIntgr;

    fract = modf(dxlde, &intgr);
    
    twoPowerFract = 1.0 + __cde80387F2XM1(fract);

    if (intgr > -1023)  // deal with normalized doubles
        ptwoPowerIntgr->member.exp = 1023/*bias*/ + (uint64_t)intgr;
    else        // deal with subnormals
    {
        // -1023 -> (1 << 51)
        // -1024 -> (1 << 50)
        // ...
        // -1074 -> (1 <<  0)
        if(((int64_t)intgr + 1023 + 51) >= 0)
		    ptwoPowerIntgr->member.mant = 1ULL << ((int64_t)intgr + 1023 + 51);
    }
    return twoPowerIntgr * twoPowerFract;

}