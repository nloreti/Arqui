#ifndef _asmihandler_
#define _asmihandler_

#include "defs.h"

void _int_0_hand();	/* Zero Divide */

void _int_01_hand();	/* Debug Exceptions */

void _int_02_hand();	/* Nonmaskable interrput */

void _int_03_hand();	/* Breakpoint */

void _int_04_hand();	/* Overflow */

void _int_05_hand();	/* Bounds check */

void _int_06_hand();	/* Invalid Opcode */

void _int_07_hand();	/* Coprocessor not available */

void _int_08_hand();	/* Double fault */

void _int_09_hand();	/* Overflow coprocessor segment */

void _int_10_hand();	/* Invalid TSS */

void _int_11_hand();	/* Segment not present */

void _int_12_hand();	/* Stack exception */

void _int_13_hand();	/* General protection */

void _int_14_hand();	/* Page Fault */

void _int_16_hand();	/* Coprocessor error */

void _int_20_hand();

void _int_21_hand();

void _int_32_hand();

void _int_80_hand();

#endif
