#include "wiced.h"
#include "stringer_pal.h"
#include <ctype.h>

char stringer_char_xform(char c)
{
    int input = (int )c;
    int output;

    output = ( isupper(input) ? tolower(input) : toupper(input));

    return (char )output;

}

void button_thread_main( void *arg )
{
    wiced_bool_t led1 = WICED_FALSE;
    wiced_bool_t led2 = WICED_FALSE;
    wiced_bool_t button1_pressed;
    wiced_bool_t button2_pressed;

    const static char* BUTTON1PRESSED = "\r\nButton 1 Pressed\r\n";
    const static char* BUTTON2PRESSED = "\r\nButton 2 Pressed\r\n";

    while(1)
    {
        /* Read the state of Button 1 */
        button1_pressed = wiced_gpio_input_get( WICED_BUTTON1 ) ? WICED_FALSE : WICED_TRUE;  /* The button has inverse logic */

        if ( button1_pressed == WICED_TRUE )
        {   /* Turn LED1 on */
            wiced_gpio_output_high( WICED_LED1 );
            wiced_uart_transmit_bytes( STDIO_UART, BUTTON1PRESSED, strlen(BUTTON1PRESSED) );
        }
        else
        {   /* Toggle LED1 */
            if ( led1 == WICED_TRUE )
            {
                wiced_gpio_output_low( WICED_LED1 );
                led1 = WICED_FALSE;
            }
            else
            {
                wiced_gpio_output_high( WICED_LED1 );
                led1 = WICED_TRUE;
            }
        }

        /* Read the state of Button 2 */
        button2_pressed = wiced_gpio_input_get( WICED_BUTTON2 ) ? WICED_FALSE : WICED_TRUE;  /* The button has inverse logic */

        if ( button2_pressed == WICED_TRUE )
        {   /* Turn LED2 on */
            wiced_gpio_output_high( WICED_LED2 );
            wiced_uart_transmit_bytes( STDIO_UART, BUTTON2PRESSED, strlen(BUTTON2PRESSED) );
        }
        else
        {   /* Toggle LED2 */
            if ( led2 == WICED_TRUE )
            {
                wiced_gpio_output_low( WICED_LED2 );
                led2 = WICED_FALSE;
            }
            else
            {
                wiced_gpio_output_high( WICED_LED2 );
                led2 = WICED_TRUE;
            }
        }

        wiced_rtos_delay_milliseconds( 250 );
    }
}

