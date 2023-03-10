
/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include "standard.h"

#include "os.h"
#include "os_private.h"


/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

#define OUT    _OUT( "OS_SLEEP" )


/*****************************************************************************/
/* public function implementation                                            */
/*****************************************************************************/

/*!
 *    @brief    Sleeps for an allocated period of time (in ms)
 */
int os_sleep_ms( uint32    sleepMs )
{
    return os_scheduler_sleepTask( sleepMs );
}

