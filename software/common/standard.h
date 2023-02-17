
#ifndef _STANDARD_H_
#define _STANDARD_H_

/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

#include "print.h"

/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

/* return statuses */

#ifndef OK
#define OK				( 0 )
#endif

#ifndef ERROR
#define ERROR			( -1 )
#endif

/* boolean */

#ifndef TRUE
#define TRUE			( 1 )
#endif

#ifndef FALSE
#define FALSE			( 0 )
#endif

/* sanity checks */
#define NULL_CHECK( p )		if( NULL == p ){ _PRINTF( "%s::%d - %s is NULL\r\n", __FILE__, __LINE__,  #p ); return ERROR; }
#define MAX_CHECK( p, m )	if( p > m ){ _PRINTF( "%s::%d - %s > %s\r\n", __FILE__, __LINE__,  #p, #m ); return ERROR; }
#define MIN_CHECK( p, m )	if( p < m ){ _PRINTF( "%s::%d - %s < %s\r\n", __FILE__, __LINE__,  #p, #m ); return ERROR; }

/* misc */
#define FOREVER			while(1)

/*****************************************************************************/
/* typedefs                                                                  */
/*****************************************************************************/

typedef char                sint8;
typedef unsigned char       uint8;
typedef short               sint16;
typedef unsigned short      uint16;
typedef long                sint32;
typedef unsigned long       uint32;
typedef long long           sint64;
typedef unsigned long long  uint64;

#endif // _STANDARD_H_

