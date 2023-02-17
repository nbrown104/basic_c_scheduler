
/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include <unistd.h>

#include "standard.h"
#include "print.h"

#include "os.h"
#include "os_private.h"


/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

#define OUT    _OUT( "OS_SCHEDULER" )

#define CS_ENTER    while( TRUE == csActive ) {}; csActive = TRUE
#define CS_EXIT        csActive = FALSE


/*****************************************************************************/
/* local variables                                                           */
/*****************************************************************************/

static sOS_PROFILE * pOS = NULL;

static int csActive = FALSE;

/*****************************************************************************/
/* private function declaration                                              */
/*****************************************************************************/

/*!
 *    @brief    Main scheduling behaviour
 *            Runs forever until OS is stopped
 *
 *    @param    None
 *
 *    @return    ERROR        if the scheduler returns at all
 *
 *    @notes    None
 *
 */
static int schedulerLoop( void );

/*!
 *    @brief    Execute the active task function
 *
 *    @param    None
 *
 *    @return    ERROR        if the task or scheduler are invalid
 *
 *    @notes    None
 */
static int executeActiveTask( void );


/*****************************************************************************/
/* public function implementation                                            */
/*****************************************************************************/

/*!
 *    @brief    Initalises OS scheduler and begins scheduling loop
 */
int os_scheduler_start( sOS_PROFILE * osProfile )
{
    /* sanity checks */
    NULL_CHECK( osProfile );
    /* sanity checks complete */
    
    int status = ERROR;

    pOS = osProfile;
    NULL_CHECK( pOS );

    OUT( "Starting scheduler\r\n" );

    schedulerLoop();
    /* should never get passed this */

    return status;
}

/*!
 *    @brief    Adds a newly created task to the scheduler
 */
int os_scheduler_addTask( sOS_TASK * newTask )
{
    /* sanity checks */
    NULL_CHECK( pOS );
    NULL_CHECK( pOS->taskList );
    NULL_CHECK( pOS->activeTask );
    NULL_CHECK( newTask );
    /* sanity checks complete */

    int status = ERROR;

    sOS_TASK * taskList = pOS->taskList;
    sOS_TASK * nextTask = NULL;
    while( NULL != taskList->nextTask )
    {
        nextTask = taskList->nextTask;
        /* new task can't be higher (<) priority than the first task */
        if( newTask->prio < nextTask->prio )
        {
            OUT( "Adding task %s before %s\r\n", newTask->name, nextTask->name );
            newTask->nextTask = nextTask;
            taskList->nextTask = newTask;
            break;
        }
        else
        {
            taskList = nextTask;
        }
    }

    if( NULL == taskList->nextTask )
    {
        OUT( "Adding task %s to the end, after %s\r\n", newTask->name, taskList->name );
        taskList->nextTask = newTask;
    }

    pOS->taskCount++;

    sOS_TASK * parentTask = pOS->activeTask;

    pOS->activeTask = newTask;
    status = executeActiveTask();
    pOS->activeTask = parentTask;

    return status;
}

/*!
 *    @brief    Tells the scheduler to put a task to sleep
 */
int os_scheduler_sleepTask( uint32 sleepMs )
{
    /* sanity checks */
    NULL_CHECK( pOS );
    NULL_CHECK( pOS->activeTask );
    /* sanity checks complete */

    int status = ERROR;

    OUT( "Putting %s to sleep for %ldms\r\n", pOS->activeTask->name, sleepMs );

    pOS->activeTask->state        = eOS_TASK_STATE_SLEEPING;
    pOS->activeTask->msToWake    = sleepMs;

    return status;    
}

/*****************************************************************************/
/* private function declaration                                              */
/*****************************************************************************/

static int schedulerLoop( void )
{
    /* sanity checks */
    NULL_CHECK( pOS );
    /* end of sanity checks */

    sOS_MEM_STATS memStats = { 0 };

    FOREVER
    {
        usleep( 1000000 / OS_CYCLE_RATE_HZ  ); /* simulates hw clk interrupt */

        pOS->cycleCount++;

        os_mem_getStats( &memStats );
        
        OUT( "=== Cycle start ========\r\n" );
        OUT( "Cycle count . : %lld\r\n",    pOS->cycleCount );
        OUT( "Tasks . . . . : %d\r\n",        pOS->taskCount );
        OUT( "Mallocs . . . : %ld\r\n",        memStats.numAllocs );
        OUT( "Frees . . . . : %ld\r\n",        memStats.numFrees  );
        
        pOS->activeTask = pOS->taskList;

        while( NULL != pOS->activeTask  )
        {
            switch( pOS->activeTask->state )
            {
            case eOS_TASK_STATE_IDLE:
                OUT( "%s is IDLE\r\n", pOS->activeTask->name );
                
                pOS->activeTask->state = eOS_TASK_STATE_RUNNING;
                
                /* intentional fallthrough to eOS_TASK_STATE_RUNNING */
            
            case eOS_TASK_STATE_RUNNING:
                OUT( "%s is RUNNING\r\n", pOS->activeTask->name );

                pOS->activeTask->msToWake = 0;
                executeActiveTask();
                
                break;
                    
            case eOS_TASK_STATE_BLOCKED:
                OUT( "%s is BLOCKED\r\n", pOS->activeTask->name );
                
                /* TODO */
                
                break;

            case eOS_TASK_STATE_SLEEPING:
                OUT( "%s is SLEEPING\r\n", pOS->activeTask->name );

                if( pOS->activeTask->msToWake )
                {
                    pOS->activeTask->msToWake--;
                }
                else
                {
                    pOS->activeTask->state = eOS_TASK_STATE_IDLE;
                }

                break;

            case eOS_TASK_STATE_SUSPENDED:                
                OUT( "%s is SUSPENDED\r\n", pOS->activeTask->name );
                
                /* TODO */
                
                break;

            case eOS_TASK_STATE_COMPLETE:
                OUT( "%s is COMPLETE\r\n", pOS->activeTask->name );
                break;

            default:
                break;
            }

            pOS->activeTask = pOS->activeTask->nextTask;
        }
        
        if( NULL != pOS->activeTask    )
        {
            OUT( "Active task . : %s\r\n", pOS->activeTask->name );
        }

        /* TODO #1    Decrement counters for all tasks BLOCKED on a sleep
         *                - if any sleeps expire, move those tasks from BLOCKED to IDLE
         */

        OUT( "=== Cycle complete =====\r\n\r\n" );
    }

    return ERROR;
}

/*!
 *    @brief    Execute the active task function
 */
static int executeActiveTask( void )
{
    /* sanity checks */
    NULL_CHECK( pOS );
    NULL_CHECK( pOS->activeTask );
    NULL_CHECK( pOS->activeTask->func );
    /* sanity checks complete */

    pOS->activeTask->func( pOS->activeTask->args );

    if( pOS->activeTask->state == eOS_TASK_STATE_RUNNING )
    {
        pOS->activeTask->state = eOS_TASK_STATE_COMPLETE;
    }
    

    OUT( "Active task is now %s\r\n", pOS->activeTask->name );
    
    return OK;
}

