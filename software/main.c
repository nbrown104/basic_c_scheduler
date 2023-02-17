
/*****************************************************************************/
/* includes                                                                  */
/*****************************************************************************/

#include <stdint.h>
#include <stdio.h>

#include "standard.h"
#include "print.h"

#include "os.h"

/*****************************************************************************/
/* defines                                                                   */
/*****************************************************************************/

#define OUT	_OUT( "MAIN" )

#define NUM_TEST_TASKS	( 3 )

/*****************************************************************************/
/* private function declaration                                              */
/*****************************************************************************/

/*****************************************************************************/
/*!
 *	@brief	main task to initialise others
 *
 *	@param	args	Pointer to arguments (unused)
 *
 *	@return	None
 *
 *	@notes	None
 */
/*****************************************************************************/
void mainTask( void * args );

/*****************************************************************************/
/*!
 *	@brief	Test task
 *
 *	@param	args	Pointer to arguments (the task ID, an int)
 *
 *	@return	None
 *
 *	@notes	None
 */
/*****************************************************************************/
void testTask( void * args );


/*****************************************************************************/
/* local variables                                                           */
/*****************************************************************************/

static int taskIDs[ NUM_TEST_TASKS ]	= { 0,  1,  2 };
static int taskPrios[ NUM_TEST_TASKS ]	= { 10, 20, 15 };


/*****************************************************************************/
/* public function implementation                                        	 */
/*****************************************************************************/

/*!
 *	@brief	Main entry point
 */
int main( void )
{
    int status = ERROR;

    OUT( "Starting...\r\n" );
    status = OK;

	status = os_init( &mainTask, NULL );

	OUT( "Done\r\n");
    return status;
}


/*****************************************************************************/
/* private function declaration                                              */
/*****************************************************************************/

/*!
 *	@brief	main task to initialise others
 */
void mainTask( void * args )
{
	static int created = FALSE;

	if( FALSE == created )
	{
		OUT( "Started main task\r\n" );

		if( OK == os_task_create( &testTask, ( void* )&taskIDs[0], taskPrios[0], "test_task_0" ) )
		{
			OUT( "Created new task\r\n" );
		}
		else
		{
			OUT( "Error creating task 0\r\n" );
		}

		if( OK == os_task_create( &testTask, ( void* )&taskIDs[1], taskPrios[1], "test_task_1" ) )
		{
			OUT( "Created new task\r\n" );
		}
		else
		{
			OUT( "Error creating task 1\r\n" );
		}

		if( OK == os_task_create( &testTask, ( void* )&taskIDs[2], taskPrios[2], "test_task_2" ) )
		{
			OUT( "Created new task\r\n" );
		}
		else
		{
			OUT( "Error creating task 2\r\n" );
		}

		created = TRUE;
	}
	else
	{
		OUT( "In main task\r\n" );
	}

	return;
}

/*!
 *	@brief	Test task
 */
void testTask( void * args )
{
	if( NULL != args )
	{
		int taskId = *( int* )args;
		OUT( "Started task %d\r\n", taskId );

		if( 1 == taskId )
		{
			OUT( "Task %d is going to sleep\r\n", taskId);
			os_sleep_ms( 20 );
		}
	}
	else
	{
		OUT( "Started task (no ID)\r\n" );
	}

	return;
}
