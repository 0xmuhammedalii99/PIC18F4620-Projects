/**
 * *****************************************************************************************************
 * * File           : Door_Locker.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Door Locker Project
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 6 October,2023
 * *****************************************************************************************************
 */

#ifndef DOOR_LOCKER_H
#define DOOR_LOCKER_H

/* ______________________________ Includes Section Beginning ______________________________ */
#include "MCAL_Layer/GPIO_Layer/Hal_GPIO.h"
#include "MCAL_Layer//EEPROM/MCAL_EEPROM.h"
#include "ECU_Layer/Keypad_Interface/ECU_keypad.h"
#include "ECU_Layer/Char_Lcd_Interface/ecu_chr_lcd.h"
#include "ECU_Layer/Dc_Motor_Interface/ECU_Dc_Motor.h"
#include "ECU_Layer/ECU_layer_init.h"
/* ______________________________ Includes Section Ending ______________________________ */

/* ______________________________ Data Typed Declarations Section Beginning ____________________*/

extern chr_lcd_4bit_t lcd;
extern _keypad_t keypad;
extern _dc_motor_t Motor_Room_1;
extern _dc_motor_t Motor_Room_2;
extern _led_t Room_1_Open_Led;
extern _led_t Room_1_Close_Led;
extern _led_t Room_2_Open_Led;
extern _led_t Room_2_Close_Led;
extern _led_t Check;
/* ______________________________ Data Typed Declarations Section Ending ____________________*/

/* _______________________ Function Declaration Section Beginning ___________________*/

/**
 * @brief Initialzie All Modules
 * @param Void
 * @return Void
 */
void Application_Initialize(void);
/**
 * @brief Returning Keypad Value
 * @param void > Void
 * @return KeyPad Value
 */
uint8 Keypad_Read_Value(void);
/**
 * @brief Setting The Password Of Door Locker
 * @param Void > Void
 * @return Void
 */
void Setting_Password(void);
/**
 * @brief Getting Password From User

 */
void Getting_Password(void);
/**
 * @brief Cheacking Password
 * @return (1 : True) or (0 : False)
 */
uint8 Cheacking_Password(void);
/**
 * @brief Select Room's Door Open
 * @param Open_Led > Pointer to Open's Room Led
 * @param Close_Led > Pointer to Close's Room Led
 * @param motor_obj > Pointer To Selected Motor's Room
 * @return Void
 */
void RoomDoorOpen(_led_t *Open_Led, _led_t *Close_Led, _dc_motor_t *motor_obj);
/* _______________________ Function Declaration Section Ending ___________________*/

#endif /* DOOR_LOCKER_H */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            6 October,2023                      Door_Locker.h
 */