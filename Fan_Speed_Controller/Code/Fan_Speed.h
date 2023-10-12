/**
 * *****************************************************************************************************
 * * File           : Fan_Speed.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Fan Speed Temperature Controller Project
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 12 October , 2023
 * *****************************************************************************************************
 */

#ifndef FAN_SPEED_H
#define FAN_SPEED_H

/* ________________________ Include Section Start ________________________ */
#include "MCAL_Layer/GPIO_Layer/Hal_GPIO.h"
#include "MCAL_Layer/ADC/MCAL_adc.h"
#include "MCAL_Layer/CCP1/MCAL_ccp1.h"
#include "ECU_Layer/ECU_layer_init.h"
/* ________________________ Include Section End ________________________ */

extern chr_lcd_8bit_t lcd_8bit;
extern _dc_motor_t Motor_Room_1;
extern _dc_motor_t Motor_Room_2;
/* ________________________ Function Declaration Start ________________________*/

void Application_Init(void);
/* ________________________ Function Declaration End ________________________*/
#endif /* FAN_SPEED_H */
