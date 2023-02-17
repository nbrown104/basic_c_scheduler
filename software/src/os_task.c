
/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include <string.h>

#include "standard.h"
#include "print.h"

#include "os_private.h"


/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

#define OUT	_OUT( "OS_TASK" )


/*****************************************************************************/
/* local variables                                                           */
/*****************************************************************************/


/*****************************************************************************/
/* public function implementation                                            */
/*****************************************************************************/

/*!
 *	@brief	Creates a new task and kicks it off imediately
 */
int os_task_create( OS_TASK_FUNC	taskFunc,
					void *			taskArgs,
					int				taskPrio,
					const char *	taskName )
{
	/* sanity checks */
	NULL_CHECK( taskFunc );
	MAX_CHECK( taskPrio, OS_TASK_MAX_PRIO );
	NULL_CHECK( taskName );
	/* sanity checks complete */
	
	int status = ERROR;

	sOS_TASK *newTask = ( sOS_TASK* )os_mem_alloc( sizeof( sOS_TASK ) );
	NULL_CHECK( newTask );

	newTask->name = ( char* )malloc( OS_TASK_NAME_MAX_LEN );
	NULL_CHECK( newTask );

	strncpy( newTask->name, taskName, OS_TASK_NAME_MAX_LEN );
	newTask->prio		= taskPrio;
	newTask->state		= eOS_TASK_STATE_IDLE;
	newTask->msToWake	= 0;
	newTask->func		= taskFunc;
	newTask->args		= taskArgs;
	newTask->nextTask	= NULL;

	if( OK != os_scheduler_addTask( newTask ) )
	{
		os_mem_free( newTask );
	}
	else
	{
		status = OK;
	}

	return status;
}

