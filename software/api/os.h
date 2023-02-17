
#ifndef _OS_H_
#define _OS_H_

/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include "standard.h"

/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

#define OS_TASK_MAX_PRIO		( 32 )
#define OS_MAIN_TASK_PRIO		( 5 )

#define OS_TASK_NAME_MAX_LEN	( 20 )

#define OS_CYCLE_RATE_HZ			( 2 )


/*****************************************************************************/
/* typedefs                                                                  */
/*****************************************************************************/

typedef void ( OS_TASK_FUNC )( void * pArg );


/*****************************************************************************/
/* enums                                                                     */
/*****************************************************************************/


/*****************************************************************************/
/* structs                                                                   */
/*****************************************************************************/


/*****************************************************************************/
/* public function declaration                                           	 */
/*****************************************************************************/

/*****************************************************************************/
/*		OS init                                                              */
/*****************************************************************************/

/*****************************************************************************/
/*!
 *	@brief	Initalises OS and calls main thread with arguments
 *
 *	@param	mainTask	Main task to run that will initialise all others
 *	@param	taskArgs	Pointer to arguments to pass into mainTask()
 *
 *	@return	ERROR		OS was not initialised successfully
 *						This function should not return
 *
 *	@notes	None
 */
/*****************************************************************************/
int os_init( OS_TASK_FUNC	mainTask,
			 void *			taskArgs );

/*****************************************************************************/
/*		OS task                                                              */
/*****************************************************************************/

/*****************************************************************************/
/*!
 *	@brief	Creates a new task and kicks it off imediately
 *
 *	@param	taskFunc	Task procedure
 *	@param	taskArgs	Arguments to pass to taskFunc
 *	@param	taskPrio	Task priority TODO
 *	@param	taskName	ASCII name of task (for debug)
 *
 *	@return	ERROR		Task not created
 *			OK			Task created and added to sceduler
 *
 *	@notes	None
 */
/*****************************************************************************/
int os_task_create( OS_TASK_FUNC	taskFunc,
					void *			taskArgs,
					int				taskPrio,
					const char *	taskName );


/*****************************************************************************/
/*		OS time                                                              */
/*****************************************************************************/

/*****************************************************************************/
/*!
 *	@brief	Sleeps for an allocated period of time (in ms)
 *
 *	@param	sleepMs		Duration to sleep (in ms)
 *
 *	@return	OK			Task slept for the requested duration
 *			ERROR		Task returned early
 *
 *	@notes	None
 */
/*****************************************************************************/
int os_sleep_ms( uint32	sleepMs );

/*****************************************************************************/
/*		OS mem                                                               */
/*****************************************************************************/

/*****************************************************************************/
/*!
 *	@brief	Allocates memory from the heap
 *
 *	@param	size		Number of bytes to allocate
 *
 *	@return	Pointer to the first address in the allocated memory
 *			Will be NULL if the memory was not allocated
 *
 *	@notes	None
 */
/*****************************************************************************/
void * os_mem_alloc( uint32 size );

/*****************************************************************************/
/*!
 *	@brief	Frees memory and releases it to the heap
 *
 *	@param	memory		Memory allocation to free
 *
 *	@return	None
 *
 *	@notes	None
 */
/*****************************************************************************/
void os_mem_free( void * memory );


#endif // _OS_H_

