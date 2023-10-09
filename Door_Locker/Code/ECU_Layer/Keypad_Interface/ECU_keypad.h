/**
 * *****************************************************************************************************
 * * File           : ECU_keypad.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Keypad Driver
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 29 July,2023
 * *****************************************************************************************************
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* _________________________  Include Section Beginning  _________________________ */
#include "../../MCAL_Layer/GPIO_Layer/Hal_GPIO.h"
/* _________________________ Include Section Ending _________________________ */


/* _________________________ Macro Definition Section Beginning _________________________ */

#define KEYPAD_ROWS                 4
#define KEYPAD_COLOUMS              4


#define KEYPAD_ROW1                 0
#define KEYPAD_ROW2                 1
#define KEYPAD_ROW3                 2
#define KEYPAD_ROW4                 3

#define KEYPAD_COLUMN1              0
#define KEYPAD_COLUMN2              1
#define KEYPAD_COLUMN3              2
#define KEYPAD_COLUMN4              3
/* _________________________ Macro Definition Section Ending _________________________ */


/* _________________________ Data Type Declarations Section Beginning _________________________ */

typedef struct 
{
    _pin_config_t keypad_row_pins[KEYPAD_ROWS];         /* @ref _pin_config_t*/
    _pin_config_t keypad_column_pins[KEYPAD_COLOUMS];  /* @ref _pin_config_t*/
}_keypad_t;

/* _________________________ Data Type Declarations Section Ending _________________________ */


/* _________________________ Function Declaration Section Beginning _________________________ */

/**
 * @brief Initialize Keypad
 * @param kwypad > Pointer to keypad Configration
 */
void keypad_initialize (const _keypad_t *keypad);

/**
 * @brief Getting The Number Pressed  
 * @param keypad > Pointer to keypad Configration
 * @param value > Pointer to Value of Button pressed in keypad
 */
void keypad_get_value(const _keypad_t *_keypad_obj, uint8 *value);
/* _________________________ Function Declaration Section Ending _________________________ */


#endif	/* ECU_KEYPAD_H */




/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            29 July,2023                         Writting Hal_GPIO.h
 */