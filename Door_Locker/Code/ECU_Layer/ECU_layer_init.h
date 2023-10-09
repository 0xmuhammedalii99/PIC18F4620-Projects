/**
 * *****************************************************************************************************
 * * File           : ECU_layer.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Includes,Functions declaration.
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 12 August,2023
 * *****************************************************************************************************
 */


#ifndef ECU_LAUER_INIT_H
#define	ECU_LAUER_INIT_H

/* ********************************  Include Section Beginning  ********************************* */
#include "Button_Interface/ECU_Button.h"
#include "Char_Lcd_Interface/ecu_chr_lcd.h"
#include "Dc_Motor_Interface/ECU_Dc_Motor.h"
#include "Keypad_Interface/ECU_keypad.h"
#include "Led_Interface/ECU_Led.h"
#include "Relay_Interface/ECU_Relay.h"
#include "7_Segment_Interface/ECU_7_segment.h"
#include "../MCAL_Layer/GPIO_Layer/Hal_GPIO.h"
#include "../MCAL_Layer/Interrupt/MCAL_external_interrupt.h"
/* ___________________________  Include Section Ending  ___________________________ */


/* ___________________________ Functions Declaration Section Beginning ___________________________ */

/**
 * @brief Initiazlie ECU Prepherales 
 * @param void 
 * @return void
*/
void ECU_LAYER_INITIALIZE(void);
/* ___________________________ Functions Declaration Section Ending ___________________________ */



#endif	/* ECU_LAUER_INIT_H */



/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali           12 August,2023                         Writting ECU_layer_init.h
 */