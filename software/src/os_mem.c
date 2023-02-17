

/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include "standard.h"
#include "print.h"

#include "os.h"
#include "os_private.h"


/*****************************************************************************/
/* local variables                                                           */
/*****************************************************************************/

static sOS_MEM_STATS memStats =
{
	0,			/* numAllocs */
	0,			/* numFrees */
};

static sOS_MEM_STATS * pMemStats = &memStats;


/*****************************************************************************/
/* public function implementation                                            */
/*****************************************************************************/

/*!
 *	@brief	Allocates memory from the heap
 */
void * os_mem_alloc( uint32 size )
{
	void * newAlloc = malloc( size );

	if( NULL != newAlloc );
	{
		pMemStats->numAllocs++;
	}

	return newAlloc;
}

/*!
 *	@brief	Frees memory and releases it to the heap
 */
void os_mem_free( void * memory )
{
	if( NULL != memory )
	{
		free( memory );
		pMemStats->numFrees++;
	}
}

/*!
 *	@brief	Retrieves memory stats
 */
void os_mem_getStats( sOS_MEM_STATS * stats )
{
	if( NULL != stats )
	{
		*stats = *pMemStats;
	}
}
