/**
 * *****************************************************************************************************
 * * File           : MCAL_EEPROM.H
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Main Project
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 28 August,2023
 * *****************************************************************************************************
 */

#include "MCAL_EEPROM.h"

/* __________________________ Function Defenition Section Beginning __________________________ */


void eeprom_write_byte(uint16 bADR, uint8 bDATA)
{
    /* Read the Global Interrupt Status " Enable - Disable "*/
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update The Address Registers */
    EEADRH = (uint8)((bADR >> 8) & 0x03); // Store MSB at EEADRH
    EEADR = (uint8)((bADR)&0xff);         // Store LSB at EEADRH
    /* Update Data Register  */
    EEDATA = bDATA;
    /* Select Access Data EEPROM Memory*/
    ACCESS_DATA_EEPROM_MEMORY();
    ACCESS_EEPROM_MEMORY();
    /* Allow Write Cycle */
    EEPROM_WRITE_CYCLE_ENABLE();
    /* Disable Global Interrupt*/
    GLOBAL_INTERRUPT_DISABLE();
    /* Initiate The Required Sequence */
    WRITE_0X55_ON_EECON2();
    WRITE_0XAA_ON_EECON2();
    /* Intitiate Date EEPROM Write/Erease */
    WRITE_CONTROL_BIT_SET();
    /* Wait unitl Write Proccess Complete */
    while (EECON1bits.WR == 1); //! Note : The Hardware Clear the bit After Writting Complete
    /* Inhipit Write Cycle */
    EEPROM_WRITE_CYCLE_DISABLE();
    /* Restore The Interrupt Status*/
    INTCONbits.GIE = Global_Interrupt_Status;
}


void eeprom_read_byte(uint16 bADR, uint8 *bDATA)
{
    /* Update The Address Registers */
    EEADRH = (uint8)((bADR >> 8) & 0x03); // Store MSB at EEADRH
    EEADR = (uint8)((bADR)&0xff);         // Store LSB at EEADRH
    /* Select Access Data EEPROM Memory*/
    ACCESS_DATA_EEPROM_MEMORY();
    ACCESS_EEPROM_MEMORY();
   /* Intitiate Date EEPROM Read */
   READ_CONTROL_BIT_SET();
   /* Delay time for High Frequency */
   NOP();
   NOP();
   /* Copy Data From EEDATA to Pointer*/
   *bDATA=EEDATA;
//    /* Wait unitl Read Proccess Complete */
//    while (EECON1bits.RD);  //! Note : The Hardware Clear the bit After Reading Complete
}

/* __________________________ Function Defenition Section Ending __________________________ */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali           28 Augast,2023                         Writting MCAL_EEPROM.c
 */