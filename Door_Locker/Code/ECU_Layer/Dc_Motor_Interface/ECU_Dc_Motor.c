/**
 * *****************************************************************************************************
 * * File           : ECU__Dc_Motor.c
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : DC Motor Driver
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 1 Augast,2023
 * *****************************************************************************************************
 */

/* _________________________  Include Section Beginning  _________________________ */
#include "ECU_Dc_Motor.h"
/* _________________________ Include Section Ending _________________________ */

/* _________________________ Function Definition Section Beginning ********************** */


void dc_motor_initialize(const _dc_motor_t *dc_motor_config)
{
    gpio_pin_initialize(&(dc_motor_config->dc_motor[MOTOR_PIN1]));
    gpio_pin_initialize(&(dc_motor_config->dc_motor[MOTOR_PIN2]));
}


void dc_motor_turn_right(const _dc_motor_t *dc_motor_config)
{
    gpio_pin_write_logic(&(dc_motor_config->dc_motor[MOTOR_PIN1]), GPIO_HIGH);
    gpio_pin_write_logic(&(dc_motor_config->dc_motor[MOTOR_PIN2]), GPIO_LOW);
}


void dc_motor_turn_left(const _dc_motor_t *dc_motor_config)
{
    gpio_pin_write_logic(&(dc_motor_config->dc_motor[MOTOR_PIN1]), GPIO_LOW);
    gpio_pin_write_logic(&(dc_motor_config->dc_motor[MOTOR_PIN2]), GPIO_HIGH);
}


void dc_motor_stop(const _dc_motor_t *dc_motor_config)
{
    gpio_pin_write_logic(&(dc_motor_config->dc_motor[MOTOR_PIN1]), GPIO_LOW);
    gpio_pin_write_logic(&(dc_motor_config->dc_motor[MOTOR_PIN2]), GPIO_LOW);
}
/* _________________________ Function Definition Section Beginning _________________________ */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            1 Augast,2023                        ECU_Dc_Motor.c
 */