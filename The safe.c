/*
 * The_safe.c
 *
 * Created: 12/2/2023 5:20:16 PM
 *  Author: VTE
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "button.h"
#include "keypad.h"
#include "button.h"

// Define EEPROM locations and maximum number of password tries
#define STATUS_LOCATION     0x30
#define PASSWORD_LOCATION1  0x31
#define PASSWORD_LOCATION2  0x32
#define PASSWORD_LOCATION3  0x33
#define PASSWORD_LOCATION4  0x34
#define MAX_TRIES 3

// Array to store entered password digits
char arr[4];

int main(void)
{
    char val = NOTPRESSED, i, flag = 0, try = MAX_TRIES;

    // Initialize pull-up resistor for the reset button
    DIO_vconnectpullup('B', 7, 1);

    // Initialize the reset button
    button_vInit('B', 7);

    // Initialize the LCD and keypad
    LCD_vInit();
    keypad_vInit();

LableA:
    // Check if the status indicates a new password needs to be set
    if (EEPROM_read(STATUS_LOCATION) == 0xff)
    {
		try=MAX_TRIES;
        LCD_clearscreen();
        LCD_vSend_string("Set Password of");
        LCD_movecursor(2, 1);
        LCD_vSend_string("4 digit:");

        // Loop to set a new 4-digit password
        for (i = 0; i < 4; i++)
        {
            do
            {
                val = keypad_u8check_press();
            } while (val == NOTPRESSED);

            LCD_vSend_char(val);
            _delay_ms(500);
            LCD_movecursor(2, 9 + i);
            LCD_vSend_char('*');
            EEPROM_write(PASSWORD_LOCATION1 + i, val);
        }

        // Mark the status as password set
        EEPROM_write(STATUS_LOCATION, 0x00);
    }

    // Main loop for checking the password and controlling the safe
    while (!flag)
    {
        LCD_clearscreen();

        // Check if the reset button is pressed
        if (button_u8read('B', 7) == 0)
        {
            arr[0] = arr[1] = arr[2] = arr[3] = NOTPRESSED;

            LCD_vSend_string("Check old Pass:");
            LCD_movecursor(2, 6);

            // Loop to enter the old password for reset
            for (i = 0; i < 4; i++)
            {
                do
                {
                    arr[i] = keypad_u8check_press();
                } while (arr[i] == NOTPRESSED);

                LCD_vSend_char(arr[i]);
                _delay_ms(500);
                LCD_movecursor(2, 6 + i);
                LCD_vSend_char('*');
            }

            // Check if the entered old password matches
            if (EEPROM_read(PASSWORD_LOCATION1) == arr[0] &&
                EEPROM_read(PASSWORD_LOCATION2) == arr[1] &&
                EEPROM_read(PASSWORD_LOCATION3) == arr[2] &&
                EEPROM_read(PASSWORD_LOCATION4) == arr[3])
            {
                // Mark the status as password reset and go back to setting a new password
                EEPROM_write(STATUS_LOCATION, 0xff);
                goto LableA;
            }
            else
            {
                // Display wrong password message and wait for a certain time
                LCD_clearscreen();
                LCD_vSend_string(" wrong password");
                _delay_ms(1000);
                LCD_clearscreen();
                LCD_vSend_string("Try again after");
                LCD_movecursor(2, 6);
                LCD_vSend_string(" seconds");

                // Countdown timer for waiting
                for (i = 30; i > 0; i--)
                {
                    LCD_movecursor(2, 4);
                    LCD_vSend_char((i / 10) + 48);
                    LCD_vSend_char((i % 10) + 48);
                    _delay_ms(1000);
                }
            }
        }

        // Reset password entry array
        arr[0] = arr[1] = arr[2] = arr[3] = NOTPRESSED;
        LCD_vSend_string("Check Password:");
        LCD_movecursor(2, 6);

        // Loop to enter the password for opening the safe
        for (i = 0; i < 4; i++)
        {
            do
            {
                arr[i] = keypad_u8check_press();
            } while (arr[i] == NOTPRESSED);

            LCD_vSend_char(arr[i]);
            _delay_ms(500);
            LCD_movecursor(2, 6 + i);
            LCD_vSend_char('*');
        }

        // Check if the entered password matches
        if (EEPROM_read(PASSWORD_LOCATION1) == arr[0] &&
            EEPROM_read(PASSWORD_LOCATION2) == arr[1] &&
            EEPROM_read(PASSWORD_LOCATION3) == arr[2] &&
            EEPROM_read(PASSWORD_LOCATION4) == arr[3])
        {
            // Display success message and set the flag to open the safe
            LCD_clearscreen();
            LCD_vSend_string(" right password");
            LCD_movecursor(2, 3);
            LCD_vSend_string("safe opened");
            flag = 1;
        }
        else
        {
            // Handle unsuccessful attempts to enter the correct password
            try--;

            if (try > 0)
            {
                // Display wrong password message and the number of remaining tries
                LCD_clearscreen();
                LCD_vSend_string(" wrong password");
                _delay_ms(1000);
                LCD_clearscreen();
                LCD_vSend_string(" You have only");
                LCD_movecursor(2, 4);
                LCD_vSend_char(try + 48);
                LCD_vSend_string(" tries");
                _delay_ms(1000);
            }
            else
            {
                // Display wrong password message and wait for a certain time
                LCD_clearscreen();
                LCD_vSend_string(" wrong password");
                _delay_ms(1000);
                LCD_clearscreen();
                LCD_vSend_string("Try again after");
                LCD_movecursor(2, 6);
                LCD_vSend_string(" seconds");

                // Countdown timer for waiting
                for (i = 30; i > 0; i--)
                {
                    LCD_movecursor(2, 4);
                    LCD_vSend_char((i / 10) + 48);
                    LCD_vSend_char((i % 10) + 48);
                    _delay_ms(1000);
                }
				try=MAX_TRIES;
            }
        }
    }
}
