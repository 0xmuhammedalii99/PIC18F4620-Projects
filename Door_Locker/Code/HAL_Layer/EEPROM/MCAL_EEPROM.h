/**
 * *****************************************************************************************************
 * * File           : MCAL_EEPROM.H
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : EEPROM Driver Module 
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 28 August,2023
 * *****************************************************************************************************
 */

#ifndef MCAL_EEPROM_H
#define MCAL_EEPROM_H

/* ______________________________  Include Section Beginning  ______________________________ */
#include "../Interrupt/MCAL_internal_interrupt.h"
#include "C:/Program Files/Microchip/xc8/v2.30/pic/include/proc/pic18f4620.h"
#include "../MCAL_Std_Types.h"
/* ______________________________  Include Section Ending  ______________________________ */

/* _____________________ Macro Funcion Declarations Section Beginning _______________________ */

/* This Macro Function to Access Data EEPROM Memory */
#define ACCESS_DATA_EEPROM_MEMORY() (EECON1bits.EEPGD = 0)
/* This Macro Function to Access Flash Memory*/
#define ACCESS_EEPROM_MEMORY() (EECON1bits.CFGS = 0)
/* This Macro Function to Enable Write Cycles to Data EEPROM */
#define EEPROM_WRITE_CYCLE_ENABLE() (EECON1bits.WREN = 1)
/* This Macro Function to Disable Write Cycles to Data EEPROM */
#define EEPROM_WRITE_CYCLE_DISABLE() (EECON1bits.WREN = 0)
/* This Macro Function to Set Write Control Bit*/
#define WRITE_CONTROL_BIT_SET() (EECON1bits.WR = 1)
/* This Macro Function to Set Read Control Bit*/
#define READ_CONTROL_BIT_SET() (EECON1bits.RD = 1)
/* Macro Function to Write 0x55 on EECON2 Register For */
#define WRITE_0X55_ON_EECON2() (EECON2 = 0x55)
/* Macro Function to Write 0x0AA on EECON2 Register */
#define WRITE_0XAA_ON_EECON2() (EECON2 = 0xAA)
/* Enable Global Interrupt*/
#define GLOBAL_INTERRUPT_ENABLE() (INTCONbits.GIE = 1)
/* Disable Global Interrupt*/
#define GLOBAL_INTERRUPT_DISABLE() (INTCONbits.GIE = 0)

/* ______________________________ Function Declaration Section Beginning ______________________________ */

/**
 * @brief Writting Data To EEPROM
 * @param bADD > Address
 * @param bDATA > Data
 * @return Void
 */
void eeprom_write_byte(uint16 adress, uint8 data);

/**
 * @brief Read Data From EEPROM
 * @param bADR > Adrress of Data 
 * @param bDATA > Pointer to Data Your Read from EEPROM
 * @return void
*/
void eeprom_read_byte(uint16 adrdress, uint8 *data);
/* ______________________________ Function Declaration Section Ending ______________________________ */

#endif /* MCAL_EEPROM_H */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali           28 Augast,2023                         Writting MCAL_EEPROM.h
 */