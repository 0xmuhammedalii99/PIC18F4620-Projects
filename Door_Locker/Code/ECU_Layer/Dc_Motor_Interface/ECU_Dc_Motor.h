/**
 * *****************************************************************************************************
 * * File           : ECU__Dc_Motor.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : DC Motor Driver
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 1 Augast,2023
 * *****************************************************************************************************
 */

#ifndef ECU_DC_MOTOR_H
#define ECU_DC_MOTOR_H
/* ********************************  Include Section Beginning  ********************************* */
#include "../../MCAL_Layer/GPIO_Layer/Hal_GPIO.h"
/* _________________________ Include Section Ending _________________________ */

/* _________________________ Data Type Declarations Section Beginning _________________________ */


/* _________________________ Macro Definition Section Beginning _________________________ */

#define MOTOR_PIN1      0X00
#define MOTOR_PIN2      0X01

#define MOTOR_OFF       0X00
#define MOTOR_ON        0X01
/* _________________________ Macro Definition Section Ending _________________________ */

typedef struct
{
    _pin_config_t dc_motor[2];
} _dc_motor_t;
/* _________________________ Data Type Declarations Section Ending _________________________ */



/* _________________________ Function Declaration Section Beginning _________________________ */

/**
 * @brief Initialize Dc Motor
 * @param dc_motor_config > Pointer to Dc Motor Configration
 */
void dc_motor_initialize (const _dc_motor_t *dc_motor_config);

/**
 * @brief Turning the Dc Motor Right
 * @param dc_motor_config
 */
void dc_motor_turn_right (const _dc_motor_t *dc_motor_config);

/**
 * @brief Turning The Dc Motor Left
 * @param dc_motor_config
 */
void dc_motor_turn_left (const _dc_motor_t *dc_motor_config);

/**
 * @brief Stopping The Dc Motor
 * @param dc_motor_config
 */
void dc_motor_stop (const _dc_motor_t *dc_motor_config);
/* ******************************* Function Declaration Section Ending ********************** */

#endif /* ECU_DC_MOTOR_H */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            30 July,2023                          Writting ECY_Dc_Motor.h
 */