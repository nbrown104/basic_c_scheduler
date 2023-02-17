
/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include "standard.h"
#include "print.h"

#include "os.h"
#include "os_private.h"


/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

#define OUT    _OUT( "OS_INIT" )


/*****************************************************************************/
/* local variables                                                           */
/*****************************************************************************/

static sOS_PROFILE    osProfile =
{
    0,                    /* cycleCount */
    0,                    /* taskCount */
    NULL,                /* taskList */
    NULL,                /* activeTask */
};

static sOS_PROFILE * pOS = &osProfile;

static char * mainTaskName = "main_task";

/*****************************************************************************/
/* public function implementation                                            */
/*****************************************************************************/

/*!
 *    @brief    Initalises OS and calls main thread with arguments
 */
int os_init( OS_TASK_FUNC    mainTask,
             void *            taskArgs )
{
    /* sanity checks */
    NULL_CHECK( pOS );
    NULL_CHECK( mainTask );
    /* sanity checks complete */
    
    int status = ERROR;

    sOS_TASK *firstTask = ( sOS_TASK* )os_mem_alloc( sizeof( sOS_TASK ) );
    NULL_CHECK( firstTask );

    firstTask->name        = mainTaskName;
    firstTask->prio        = OS_MAIN_TASK_PRIO;
    firstTask->state    = eOS_TASK_STATE_IDLE;
    firstTask->func        = mainTask;
    firstTask->args        = taskArgs;
    firstTask->nextTask    = NULL;

    pOS->taskList  = firstTask;
    pOS->taskCount = 1;

    OUT( "Done - %d tasks\r\n", pOS->taskCount );
    
    os_scheduler_start( pOS );
    /* should never get passed this */
    
    os_mem_free( firstTask );

    return status;
}

