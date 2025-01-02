/*++

    toro C Library
    https://github.com/KilianKegel/toro-C-Library#toro-c-library-formerly-known-as-torito-c-library

    Copyright (c) 2017-2025, Kilian Kegel. All rights reserved.
    SPDX-License-Identifier: GNU General Public License v3.0

Module Name:

    WcsNCmpCDEABI.c

Abstract:

    Import Library version

    Implementation of the Standard C function.
    Appends characters of a wide string.

Author:

    Kilian Kegel

--*/
#include <CdeServices.h>

static ROMPARM_MEMSTRXCMP ROMPARM = {
    /*fForceToDataSeg*/ 1 , \
    /*fCountIsParm*/    1,  \
    /*fCaseSensitive*/  1,  \
    /*fBreakOnZero*/    1,  \
    /*fAjustDifference*/1,  \
    /*fWide*/           1 };

/**
Synopsis
    #include <wchar.h>
    int wcsncmp(const wchar_t* pszDst, const wchar_t* pszSrc, size_t count);
Description
    https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strncmp-wcsncmp-mbsncmp-mbsncmp-l?view=msvc-160
Parameters
    https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strncmp-wcsncmp-mbsncmp-mbsncmp-l?view=msvc-160#parameters
Returns
    https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strncmp-wcsncmp-mbsncmp-mbsncmp-l?view=msvc-160#return-value
**/
static int wcsncmpCDEABI(const wchar_t* pszDst, const wchar_t* pszSrc, size_t count) {
    CDE_APP_IF* pCdeAppIf = __cdeGetAppIf();

    return pCdeAppIf->pCdeServices->pMemStrxCmp(&ROMPARM, (void*)pszDst, (void*)pszSrc, count);

}

MKCDEABI(wcsncmp);