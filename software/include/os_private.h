
#ifndef _OS_PRIVATE_H_
#define _OS_PRIVATE_H_

/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include "standard.h"
#include "os.h"

/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

#define OS_MAX_TASKS            ( OS_MAX_PRIO + 1 )


/*****************************************************************************/
/* typedefs                                                                  */
/*****************************************************************************/


/*****************************************************************************/
/* enums                                                                     */
/*****************************************************************************/

/*!
 *    @enum    eOS_TASK_STATE
 *    @brief    Current state of a task
 */
typedef enum eOS_TASK_STATE
{
    eOS_TASK_STATE_IDLE = 0,
    eOS_TASK_STATE_RUNNING,
    eOS_TASK_STATE_BLOCKED,
    eOS_TASK_STATE_SLEEPING,
    eOS_TASK_STATE_SUSPENDED,
    eOS_TASK_STATE_COMPLETE,

    MAX_OS_TASK_STATE

} eOS_TASK_STATE;


/*****************************************************************************/
/* structs                                                                   */
/*****************************************************************************/

/*!
 *    @struct    sOS_MEM_STATS
 *    @brief    Statistics of the current runtime memory stats
 */
typedef struct sOS_MEM_STATS
{
    uint32        numAllocs;
    uint32        numFrees;

} sOS_MEM_STATS;

/*!
 *    @struct    sOS_TASK
 *    @brief    Holds all info pertaining to a task
 */
typedef struct sOS_TASK
{
    char *            name;

    int                prio;
    eOS_TASK_STATE    state;
    uint32            msToWake;

    OS_TASK_FUNC *    func;
    void *            args;

    void *            nextTask;

} sOS_TASK;

/*!
 *    @struct    sOS_PROFILE
 *    @brief    Holds all info pertaining to the OS
 */
typedef struct sOS_PROFILE
{
    uint64            cycleCount;
    int                taskCount;
    sOS_TASK *        taskList;
    sOS_TASK *        activeTask;

} sOS_PROFILE;


/*****************************************************************************/
/* public function declaration                                               */
/*****************************************************************************/

/*****************************************************************************/
/*      OS init                                                              */
/*****************************************************************************/


/*****************************************************************************/
/*      OS scheduler                                                         */
/*****************************************************************************/

/*****************************************************************************/
/*!
 *    @brief    Initalises OS scheduler and begins scheduling loop
 *
 *    @param    osProfile    Pointer to the OS profile to run
 *
 *    @return    ERROR        Scheduler has not been started
 *                        This function should not return
 *
 *    @notes    None
 */
/*****************************************************************************/
int os_scheduler_start( sOS_PROFILE *osProfile );

/*****************************************************************************/
/*!
 *    @brief    Adds a newly created task to the scheduler
 *
 *    @param    newTask        Pointer to new task structure
 *
 *    @return    OK            Task has been successfully added to the scheduler
 *            ERROR        Task wasn't added to the scheduler and should be freed
 *
 *    @notes    None
 */
/*****************************************************************************/
int os_scheduler_addTask( sOS_TASK * newTask );

/*****************************************************************************/
/*!
 *    @brief    Tells the scheduler to put a task to sleep
 *
 *    @param    sleepMs        Duration (in ms) for task to sleep
 *
 *    @return    OK            Task will be put to sleep
 *            ERROR        Task has not been put to sleeo
 *
 *    @notes    None
 */
/*****************************************************************************/
int os_scheduler_sleepTask( uint32 sleepMs );

/*****************************************************************************/
/*      OS task                                                              */
/*****************************************************************************/

/*****************************************************************************/
/*      OS mem                                                               */
/*****************************************************************************/

/*****************************************************************************/
/*!
 *    @brief    Retrieves memory stats
 *
 *    @param    stats        Pointer to memory stats struct to populate
 *
 *    @return    None
 *
 *    @notes    None
 */
/*****************************************************************************/
void os_mem_getStats( sOS_MEM_STATS * stats );


#endif // _OS_PRIVATE_H_

