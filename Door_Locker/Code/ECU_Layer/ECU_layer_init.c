/**
 * *****************************************************************************************************
 * * File           : ECU_layer.c
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Prepherales definations , funcions definations .
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 12 August,2023
 * *****************************************************************************************************
 */

/* ___________________________  Include Section Beginning  ___________________________ */
#include "ECU_layer_init.h"
/* ___________________________  Include Section Ending  ___________________________ */

/* ___________________________ Prepherales Definition Section Beginning ___________________________ */

chr_lcd_8bit_t lcd_8bit = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,

    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D0].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D0].pin = GPIO_PIN0,
    .lcd_data[LCD_8BIT_PIN_D0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D0].logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D1].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D1].pin = GPIO_PIN1,
    .lcd_data[LCD_8BIT_PIN_D1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D1].logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D2].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D2].pin = GPIO_PIN2,
    .lcd_data[LCD_8BIT_PIN_D2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D2].logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D3].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D3].pin = GPIO_PIN3,
    .lcd_data[LCD_8BIT_PIN_D3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D3].logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D4].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D4].pin = GPIO_PIN4,
    .lcd_data[LCD_8BIT_PIN_D4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D4].logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D5].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D5].pin = GPIO_PIN5,
    .lcd_data[LCD_8BIT_PIN_D5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D5].logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D6].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D6].pin = GPIO_PIN6,
    .lcd_data[LCD_8BIT_PIN_D6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D6].logic = GPIO_LOW,

    .lcd_data[LCD_8BIT_PIN_D7].port = PORTD_INDEX,
    .lcd_data[LCD_8BIT_PIN_D7].pin = GPIO_PIN7,
    .lcd_data[LCD_8BIT_PIN_D7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_8BIT_PIN_D7].logic = GPIO_LOW};
chr_lcd_4bit_t lcd = {
    /* RS Pin Configuration */
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN4,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    /* E Pin Configuration */
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN5,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    /* Pins Configuration */
    .lcd_data[LCD_4BIT_PIN_D4].port = PORTC_INDEX,
    .lcd_data[LCD_4BIT_PIN_D4].pin = GPIO_PIN0,
    .lcd_data[LCD_4BIT_PIN_D4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_4BIT_PIN_D4].logic = GPIO_LOW,

    .lcd_data[LCD_4BIT_PIN_D5].port = PORTC_INDEX,
    .lcd_data[LCD_4BIT_PIN_D5].pin = GPIO_PIN1,
    .lcd_data[LCD_4BIT_PIN_D5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_4BIT_PIN_D5].logic = GPIO_LOW,

    .lcd_data[LCD_4BIT_PIN_D6].port = PORTC_INDEX,
    .lcd_data[LCD_4BIT_PIN_D6].pin = GPIO_PIN2,
    .lcd_data[LCD_4BIT_PIN_D6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_4BIT_PIN_D6].logic = GPIO_LOW,

    .lcd_data[LCD_4BIT_PIN_D7].port = PORTC_INDEX,
    .lcd_data[LCD_4BIT_PIN_D7].pin = GPIO_PIN3,
    .lcd_data[LCD_4BIT_PIN_D7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[LCD_4BIT_PIN_D7].logic = GPIO_LOW,
};
_keypad_t keypad = {
    .keypad_row_pins[KEYPAD_ROW1].port = PORTD_INDEX,
    .keypad_row_pins[KEYPAD_ROW1].pin = GPIO_PIN0,
    .keypad_row_pins[KEYPAD_ROW1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[KEYPAD_ROW1].logic = GPIO_LOW,

    .keypad_row_pins[KEYPAD_ROW2].port = PORTD_INDEX,
    .keypad_row_pins[KEYPAD_ROW2].pin = GPIO_PIN1,
    .keypad_row_pins[KEYPAD_ROW2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[KEYPAD_ROW2].logic = GPIO_LOW,

    .keypad_row_pins[KEYPAD_ROW3].port = PORTD_INDEX,
    .keypad_row_pins[KEYPAD_ROW3].pin = GPIO_PIN2,
    .keypad_row_pins[KEYPAD_ROW3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[KEYPAD_ROW3].logic = GPIO_LOW,

    .keypad_row_pins[KEYPAD_ROW4].port = PORTD_INDEX,
    .keypad_row_pins[KEYPAD_ROW4].pin = GPIO_PIN3,
    .keypad_row_pins[KEYPAD_ROW4].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[KEYPAD_ROW4].logic = GPIO_LOW,

    .keypad_column_pins[KEYPAD_COLUMN1].port = PORTD_INDEX,
    .keypad_column_pins[KEYPAD_COLUMN1].pin = GPIO_PIN4,
    .keypad_column_pins[KEYPAD_COLUMN1].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[KEYPAD_COLUMN1].logic = GPIO_LOW,

    .keypad_column_pins[KEYPAD_COLUMN2].port = PORTD_INDEX,
    .keypad_column_pins[KEYPAD_COLUMN2].pin = GPIO_PIN5,
    .keypad_column_pins[KEYPAD_COLUMN2].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[KEYPAD_COLUMN2].logic = GPIO_LOW,

    .keypad_column_pins[KEYPAD_COLUMN3].port = PORTD_INDEX,
    .keypad_column_pins[KEYPAD_COLUMN3].pin = GPIO_PIN6,
    .keypad_column_pins[KEYPAD_COLUMN3].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[KEYPAD_COLUMN3].logic = GPIO_LOW,

    .keypad_column_pins[KEYPAD_COLUMN4].port = PORTD_INDEX,
    .keypad_column_pins[KEYPAD_COLUMN4].pin = GPIO_PIN7,
    .keypad_column_pins[KEYPAD_COLUMN4].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[KEYPAD_COLUMN4].logic = GPIO_LOW};
_dc_motor_t Motor_Room_1 = {
    .dc_motor[MOTOR_PIN1].port = PORTA_INDEX,
    .dc_motor[MOTOR_PIN1].pin = GPIO_PIN0,
    .dc_motor[MOTOR_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[MOTOR_PIN1].logic = MOTOR_OFF,

    .dc_motor[MOTOR_PIN2].port = PORTA_INDEX,
    .dc_motor[MOTOR_PIN2].pin = GPIO_PIN1,
    .dc_motor[MOTOR_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[MOTOR_PIN2].logic = MOTOR_OFF};
_dc_motor_t Motor_Room_2 = {
    .dc_motor[MOTOR_PIN1].port = PORTA_INDEX,
    .dc_motor[MOTOR_PIN1].pin = GPIO_PIN2,
    .dc_motor[MOTOR_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[MOTOR_PIN1].logic = MOTOR_OFF,

    .dc_motor[MOTOR_PIN2].port = PORTA_INDEX,
    .dc_motor[MOTOR_PIN2].pin = GPIO_PIN3,
    .dc_motor[MOTOR_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[MOTOR_PIN2].logic = MOTOR_OFF};

_led_t Room_1_Open_Led = {
    .led_pin.port = PORTB_INDEX,
    .led_pin.pin = GPIO_PIN0,
    .led_pin.direction = GPIO_DIRECTION_OUTPUT,
    .led_pin.logic = GPIO_LOW,
};
_led_t Room_1_Close_Led = {
    .led_pin.port = PORTB_INDEX,
    .led_pin.pin = GPIO_PIN1,
    .led_pin.direction = GPIO_DIRECTION_OUTPUT,
    .led_pin.logic = GPIO_HIGH,
};
_led_t Room_2_Open_Led = {
    .led_pin.port = PORTB_INDEX,
    .led_pin.pin = GPIO_PIN2,
    .led_pin.direction = GPIO_DIRECTION_OUTPUT,
    .led_pin.logic = GPIO_LOW,
};
_led_t Room_2_Close_Led = {
    .led_pin.port = PORTB_INDEX,
    .led_pin.pin = GPIO_PIN3,
    .led_pin.direction = GPIO_DIRECTION_OUTPUT,
    .led_pin.logic = GPIO_HIGH,
};


/* ___________________________ Prepherales Definition Section Ending ___________________________ */

/* ___________________________ Functions Definition Section Beginning ___________________________ */

void
ECU_LAYER_INITIALIZE(void)
{
    lcd_4bit_intialize(&lcd);
    keypad_initialize(&keypad);
    dc_motor_initialize(&Motor_Room_1);
    dc_motor_initialize(&Motor_Room_2);
    led_initializ_direction(&Room_1_Open_Led);
    led_initializ_direction(&Room_1_Close_Led);
    led_initializ_direction(&Room_2_Open_Led);
    led_initializ_direction(&Room_2_Close_Led);
    
}

/* ___________________________ Functions Definition Section Ending ___________________________ */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali           12 August,2023                         Writting ECU_layer_init.c
 */