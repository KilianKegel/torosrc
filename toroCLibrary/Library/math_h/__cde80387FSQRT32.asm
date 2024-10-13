;/*++
;
;    toro C Library
;    https://github.com/KilianKegel/toro-C-Library#toro-c-library-formerly-known-as-torito-c-library
;
;    Copyright (c) 2017-2024, Kilian Kegel. All rights reserved.
;    SPDX-License-Identifier: GNU General Public License v3.0
;
;Module Name:
;
;    __cde80387FSQRT32.asm
;
;Abstract:
;
;    CDE internal math 80387 instruction FSQRT to calculate square root.
;
;		double __cde80387FSQRT(double x)
;
;Author:
;
;    Kilian Kegel
;
;--*/
	.model flat
.code
__cde80387FSQRT proc C public float64:QWORD
	
	fld float64

	FSQRT

	ret

__cde80387FSQRT endp
end