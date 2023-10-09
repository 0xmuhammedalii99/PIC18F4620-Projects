/**
 * *****************************************************************************************************
 * * File           : ECU_Keypad.c
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Keypad Driver
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 29 July,2023
 * *****************************************************************************************************
 */

/* ____________________________  Include Section Beginning  ____________________________ */
#include "ECU_keypad.h"
/* ____________________________ Include Section Ending ____________________________ */

/* ____________________________ Data Type Declaration Section Beginning ____________________________ */

static const uint8 keypad_buttoms[KEYPAD_ROWS][KEYPAD_COLOUMS] = {
    {7, 8, 9, '/'},
    {4, 5, 6, '*'},
    {1, 2, 3, '-'},
    {'#', 0, '=', '+'}};

/* ____________________________ Data Type Declaration Section Ending ____________________________ */

/* ____________________________ Function Definition Section Beginning ____________________________ */

void keypad_initialize(const _keypad_t *keypad)
{
    uint8 row_counter = ZERO, columns_counter = ZERO;

    for (row_counter = ZERO; row_counter < KEYPAD_ROWS; row_counter++)
        gpio_pin_initialize(&(keypad->keypad_row_pins[row_counter]));
    for (columns_counter = ZERO; columns_counter < KEYPAD_COLOUMS; columns_counter++)
        gpio_pin_initialize_direction(&(keypad->keypad_column_pins[columns_counter]));
}

void keypad_get_value(const _keypad_t *_keypad_obj, uint8 *value)
{
    uint8 ROW_COUNTER = ZERO, COLUMN_COUNTER = ZERO, l_counter = ZERO;
    _logic_t column_logic = ZERO;

    for (ROW_COUNTER = ZERO; ROW_COUNTER < KEYPAD_ROWS; ROW_COUNTER++)
    {
        for (l_counter = ZERO; l_counter < KEYPAD_ROWS; l_counter++)
        {
            gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
        }
        gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[ROW_COUNTER]), GPIO_HIGH);
        for (COLUMN_COUNTER = ZERO; COLUMN_COUNTER < KEYPAD_COLOUMS; COLUMN_COUNTER++)
        {
            gpio_pin_read_logic(&(_keypad_obj->keypad_column_pins[COLUMN_COUNTER]), &column_logic);
            if (GPIO_HIGH == column_logic)
            {
                *value = keypad_buttoms[ROW_COUNTER][COLUMN_COUNTER];
            }
        }
    }
}

/* ____________________________ Function Definition Section Beginning ____________________________ */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            29 July,2023                         ECU_Keypad.c
 */