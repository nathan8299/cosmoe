//------------------------------------------------------------------------------
//	Copyright (c) 2001-2002, OpenBeOS
//
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the "Software"),
//	to deal in the Software without restriction, including without limitation
//	the rights to use, copy, modify, merge, publish, distribute, sublicense,
//	and/or sell copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//	DEALINGS IN THE SOFTWARE.
//
//	File Name:		SupportDefs.h
//	Author:			Erik Jaesler (erik@cgsoftware.com)
//	Description:	Common type definitions.
//------------------------------------------------------------------------------

#ifndef _SUPPORT_DEFS_H
#define _SUPPORT_DEFS_H

/* this !must! be located before the include of sys/types.h */
#if !defined(_SYS_TYPES_H) && !defined(_SYS_TYPES_H_)
typedef unsigned long			ulong;
typedef unsigned int			uint;
typedef unsigned short			ushort;
#endif  // _SYS_TYPES_H / _SYS_TYPES_H_


// Standard Includes -----------------------------------------------------------

// System Includes -------------------------------------------------------------
#include <BeBuild.h>
#include <sys/types.h>
#include <Errors.h>

// Project Includes ------------------------------------------------------------

// Local Includes --------------------------------------------------------------

// Local Defines ---------------------------------------------------------------

// Globals ---------------------------------------------------------------------

// Shorthand type formats ------------------------------------------------------

typedef	signed char				int8;
typedef unsigned char			uint8;
typedef volatile signed char   	vint8;
typedef volatile unsigned char	vuint8;

typedef	short					int16;
typedef unsigned short			uint16;
typedef volatile short			vint16;
typedef volatile unsigned short	vuint16;

typedef	long					int32;
typedef unsigned long			uint32;
typedef volatile long			vint32;
typedef volatile unsigned long	vuint32;

typedef	long long					int64;
typedef unsigned long long			uint64;
typedef volatile long long			vint64;
typedef volatile unsigned long long	vuint64;

typedef volatile long			vlong;
typedef volatile int			vint;
typedef volatile short			vshort;
typedef volatile char			vchar;

typedef volatile unsigned long	vulong;
typedef volatile unsigned int	vuint;
typedef volatile unsigned short	vushort;
typedef volatile unsigned char	vuchar;

typedef unsigned char			uchar;
typedef unsigned short          unichar;


// Descriptive formats ---------------------------------------------------------
typedef int32					status_t;
typedef int64					bigtime_t;
typedef uint32					type_code;
typedef uint32					perform_code;
typedef unsigned long			addr_t;


// Empty string ("") -----------------------------------------------------------
#ifdef __cplusplus
extern _IMPEXP_BE const char *B_EMPTY_STRING;
#endif


// min and max comparisons -----------------------------------------------------
//	min() and max() won't work in C++
#define min_c(a,b) ((a)>(b)?(b):(a))
#define max_c(a,b) ((a)>(b)?(a):(b))

#ifndef __cplusplus
#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#endif 


// Grandfathering --------------------------------------------------------------

#ifndef __cplusplus
typedef unsigned char			bool;
#define false	0
#define true	1
#endif 

#ifndef NULL
#define NULL 	(0L)
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

//----- Atomic functions; old value is returned --------------------------------
extern _IMPEXP_ROOT int32	atomic_set(vint32 *value, int32 newValue);
extern _IMPEXP_ROOT int32	atomic_test_and_set(vint32 *value, int32 newValue, int32 testAgainst);
extern _IMPEXP_ROOT int32	atomic_add(vint32 *value, int32 addValue);
extern _IMPEXP_ROOT int32	atomic_and(vint32 *value, int32 andValue);
extern _IMPEXP_ROOT int32	atomic_or(vint32 *value, int32 orValue);	
extern _IMPEXP_ROOT int32	atomic_get(vint32 *value);

extern _IMPEXP_ROOT int64	atomic_set64(vint64 *value, int64 newValue);
extern _IMPEXP_ROOT int64	atomic_test_and_set64(vint64 *value, int64 newValue, int64 testAgainst);
extern _IMPEXP_ROOT int64	atomic_add64(vint64 *value, int64 addValue);
extern _IMPEXP_ROOT int64	atomic_and64(vint64 *value, int64 andValue);
extern _IMPEXP_ROOT int64	atomic_or64(vint64 *value, int64 orValue);	
extern _IMPEXP_ROOT int64	atomic_get64(vint64 *value);


// Other stuff -----------------------------------------------------------------
extern _IMPEXP_ROOT void *	get_stack_frame(void);

#ifdef __cplusplus
}
#endif

//-------- Obsolete or discouraged API -----------------------------------------

// use 'true' and 'false'
#ifndef FALSE
#define FALSE		0
#endif
#ifndef TRUE
#define TRUE		1
#endif


//------------------------------------------------------------------------------

#endif	// _SUPPORT_DEFS_H

/*
 * $Log $
 *
 * $Id  $
 *
 */

