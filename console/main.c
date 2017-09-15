#include "wiced_rtos.h"
#include "RTOS/wwd_rtos_interface.h"
#include "RTOS/wiced_rtos_common.h"
#include "platform_init.h"
#include "internal/wiced_internal_api.h"
#include "FreeRTOSConfig.h"

#include "stringer_pal.h"

/******************************************************
 *                    Constants
 ******************************************************/

#ifndef APPLICATION_STACK_SIZE
#define APPLICATION_STACK_SIZE WICED_DEFAULT_APPLICATION_STACK_SIZE
#endif

#ifndef TIMER_THREAD_STACK_SIZE
#define TIMER_THREAD_STACK_SIZE      1024
#endif
#define TIMER_QUEUE_LENGTH  5

#define SYSTEM_MONITOR_THREAD_STACK_SIZE   512

static void application_thread_main( void *arg );
static TaskHandle_t  app_thread_handle;

static TaskHandle_t button_thread_handle;

#ifndef WICED_DISABLE_WATCHDOG
static TaskHandle_t  system_monitor_thread_handle;
#endif /* WICED_DISABLE_WATCHDOG */

/*
 * We're able to define main() here, in our own code, by adding the 
 * "-D ALTERNATE_MAIN" compile time flag tot he list of CFLAGS used 
 * in the makefile which builds the standard, "built-in" version
 * of main(): WICED-SDK-3.7.0-7/WICED/RTOS/FreeRTOS/WICED/WICED.mk.
 */

int main( void )
{

#if defined ( __IAR_SYSTEMS_ICC__ )
/* IAR allows init functions in __low_level_init(), but it is run before global
 * variables have been initialised, so the following init still needs to be done
 * When using GCC, this is done in crt0_GCC.c
 */
    platform_init_mcu_infrastructure( );
    platform_init_external_devices( );
#endif /* #elif defined ( __IAR_SYSTEMS_ICC__ ) */

#ifndef WICED_DISABLE_WATCHDOG
    /* Start the watchdog kicking thread */
    xTaskCreate( (TaskFunction_t) system_monitor_thread_main, "system monitor", SYSTEM_MONITOR_THREAD_STACK_SIZE/sizeof( portSTACK_TYPE ), NULL, RTOS_HIGHEST_PRIORITY, &system_monitor_thread_handle);
#endif /* WICED_DISABLE_WATCHDOG */
    /* Create an initial thread */
    xTaskCreate( application_thread_main, "app_thread", APPLICATION_STACK_SIZE/sizeof( portSTACK_TYPE ), NULL, WICED_PRIORITY_TO_NATIVE_PRIORITY(WICED_APPLICATION_PRIORITY), &app_thread_handle);
    /* Create an additional thread for the hell of it - something to watch the buttons */
    xTaskCreate( button_thread_main, "button_thread", APPLICATION_STACK_SIZE/sizeof( portSTACK_TYPE ), NULL, WICED_PRIORITY_TO_NATIVE_PRIORITY(WICED_APPLICATION_PRIORITY), &button_thread_handle);

    /* Start the FreeRTOS scheduler - this call should never return */
    vTaskStartScheduler( );

    /* Should never get here, unless there is an error in vTaskStartScheduler */
    return 0;
}

static void application_thread_main( void *arg )
{
    UNUSED_PARAMETER( arg );
    application_start( );

    malloc_leak_check(NULL, LEAK_CHECK_THREAD);
    vTaskDelete( NULL );
}


