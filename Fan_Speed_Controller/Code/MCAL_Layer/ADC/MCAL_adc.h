/**
 * *****************************************************************************************************
 * * File           : MCAL_adc.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : ADC " Analog-Digital Converter "
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 3 September,2023
 * *****************************************************************************************************
 */

#ifndef MCAL_ADC_H
#define MCAL_ADC_H

/* ________________________________  Include Section Beginning  ________________________________ */
#include "../GPIO_Layer/Hal_GPIO.h"
#include "../Interrupt/MCAL_internal_interrupt.h"
#include "C:/Program Files/Microchip/xc8/v2.30/pic/include/proc/pic18f4620.h"
/* ________________________________  Include Section Ending  ________________________________ */

/* _________________________ Macro Declarations Section Beginning ____________________________ */

/*** @note Channel AD0 is Analog , Other Channels is Digital  */
#define ADC_AN0_ANALOG      0x0E
/*** @note Channel (AD0:AD1) is Analog , Other Channels is Digital  */
#define ADC_AN1_ANALOG      0x0D
/*** @note Channel (AD0:AD2) is Analog , Other Channels is Digital  */
#define ADC_AN2_ANALOG      0x0C
/*** @note Channel (AD0:AD3) is Analog , Other Channels is Digital  */
#define ADC_AN3_ANALOG      0x0B
/*** @note Channel (AD0:AD4) is Analog , Other Channels is Digital  */
#define ADC_AN4_ANALOG      0x0A
/*** @note Channel (AD0:AD5) is Analog , Other Channels is Digital  */
#define ADC_AN5_ANALOG      0x09
/*** @note Channel (AD0:AD6) is Analog , Other Channels is Digital  */
#define ADC_AN6_ANALOG      0x08
/*** @note Channel (AD0:AD7) is Analog , Other Channels is Digital  */
#define ADC_AN7_ANALOG      0x07
/*** @note Channel (AD0:AD8) is Analog , Other Channels is Digital  */
#define ADC_AN8_ANALOG      0x06
/*** @note Channel (AD0:AD9) is Analog , Other Channels is Digital  */
#define ADC_AN9_ANALOG      0x05
/*** @note Channel (AD0:AD10) is Analog , Other Channels is Digital  */
#define ADC_AN10_ANALOG     0x04
/*** @note Channel (AD0:AD11) is Analog , Other Channels is Digital  */
#define ADC_AN11_ANALOG     0x03
/*** @note Channel (AD0:AD12) is Analog , Other Channels is Digital  */
#define ADC_AN12_ANALOG     0x02
/*** @note All Channels is Digital Configrations */
#define ADC_ALL_DIGITAL     0x0F
/*** @note All Channels is Analog Configrations */
#define ADC_ALL_ANALOG      0x00

/* Enable Voltage Reference */
#define VOLTAGE_REFERENCE_ENABLE        0x01U
/* Disable Voltage Reference */
#define VOLTAGE_REFERENCE_DISABLE       0x00U
#define RESULT_FORMAT_RIGHT             0x01U
#define RESULT_FORMAT_LEFT              0x00U

/* ___________________________ Macro Declarations Section Ending ____________________________ */

/* ___________________________ Macro Funcion  Section Beginning ____________________________ */

/* Macro Function to Enable ADC Module */
#define ADC_MODULE_ENABLE() (ADCON0bits.ADON = 1)
/* Macro Function to Disable ADC Module */
#define ADC_MODULE_DISABLE() (ADCON0bits.ADON = 0)
/**
 * @brief Macro Function to Get Status of Conversion ( 1 --> conversion in progress , 0 --> conversion done )
 * @note This Function Return Status When 'ADON = 1 --> Enable ADC Module'
 */
#define ADC_CONVERSTION_STATUS() (ADCON0bits.GO_DONE)
#define ADC_START_CONVERSION() (ADCON0bits.GODONE = 1)
/**
 * @brief  Macro Functions to Enable Voltage Reference Configrations
 * @note Voltage Reference is VREF- (AN2) & VREF+ (AN3)
 * @note You Can't use 'AN2' & 'AN3' as Analog Inputs
 */
#define ADC_VOLTAGE_REFERENCE_ENABLE() \
    do                                 \
    {                                  \
        ADCON1bits.VCFG1 = 1;          \
        ADCON1bits.VCFG0 = 1;          \
    } while (0)
/**
 * Macro Functions to Disable Voltage Reference Configrations
 * @note Voltage Reference is VSS & VDD
 */
#define ADC_VOLTAGE_REFERENCE_DISABLE() \
    do                                  \
    {                                   \
        ADCON1bits.VCFG1 = 0;           \
        ADCON1bits.VCFG0 = 0;           \
    } while (0)

/*** @brief Analog-To-Digital Port Configuration Control*/
#define ADC_ANALOG_DIGITAL_PIN(_CONFIG) (ADCON1bits.PCFG = _CONFIG)
/*** @brief Macro Function To Select Channel*/
#define ADC_SELECT_CHANNEL(_CHANNEL) (ADCON0bits.CHS = _CHANNEL)
/*** @brief Macro Function To Select Acquisition Time*/
#define ADC_SELECT_ACQUISITION_TIME(_TIME) (ADCON2bits.ACQT = _TIME)
/*** @brief Macro Function To Select Conversion Clock*/
#define ADC_SELECT_CONVERSION_CLOCK(_CLOCK) (ADCON2bits.ADCS = _CLOCK)
/* Macro Function to Select Result Format Right*/
#define ADC_RESULT_FORMAT_SELECT_RIGHT() (ADCON2bits.ADFM = 1)
/* Macro Function to Select Result Format Left */
#define ADC_RESULT_FORMAT_SELECT_LEFT() (ADCON2bits.ADFM = 0)
/* ___________________________ Macro Funcion  Section Ending ______________________________ */

/* __________________________ Data Type Declarations Section Beginning _____________________ */

typedef enum
{
    ADC_CHANNEL0_AN0 = 0,
    ADC_CHANNEL1_AN1,
    ADC_CHANNEL2_AN2,
    ADC_CHANNEL3_AN3,
    ADC_CHANNEL4_AN4,
    ADC_CHANNEL5_AN5,
    ADC_CHANNEL6_AN6,
    ADC_CHANNEL7_AN7,
    ADC_CHANNEL8_AN8,
    ADC_CHANNEL9_AN9,
    ADC_CHANNEL10_AN10,
    ADC_CHANNEL11_AN11,
    ADC_CHANNEL12_AN12,
} _adc_channel_select_t;

typedef enum
{
    ADC_0_TD = 0,
    ADC_2_TD,
    ADC_4_TD,
    ADC_6_TD,
    ADC_8_TD,
    ADC_12_TD,
    ADC_16_TD,
    ADC_20_TD
} _acquistiton_time_t;
typedef enum
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
} _adc_conversion_clock_t;

typedef struct
{
#if ADC_INTERRUPT == INTERNEL_INTERRUPT_ENABLE
    void (*adc_Interrupt_Handler)(void);
    _interrupt_priority_cfg priority;
#endif
    _adc_channel_select_t channel;
    _acquistiton_time_t acquistition_time;
    _adc_conversion_clock_t conversion_clock;
    uint8 voltage_reference : 1;
    uint8 result_format : 1;
    uint8 reserved : 6;
} _adc_config_t;

/* ____________________________ Data Type Declarations Section Ending ____________________________ */

/* ____________________________ Function Declaration Section Beginning ____________________________ */

/**
 * @brief Initialize ADC Module
 * @param adc_obj > Pointer to ADC Configuration
 * @return Void
 */
void adc_initialize(_adc_config_t *adc_obj);

/**
 * @brief  Make All Operation ( Select Channel -  Conversion - Getting Result )
 * @param adc_obj > Pointer to ADC Configuration
 * @param channel_select > Selected Channel
 * @param conv_result > Pointer To Conversion Result
 * @return Void
 */
void adc_get_conversion_result_Blocking(_adc_config_t *adc_obj, _adc_channel_select_t channel_select,uint16 *conv_result);

/**
 * @brief Getting  the Conversion Result 
 * @param adc_obj > Pointer to ADC Configuration
 * @param conv_result > Pointer To Conversion Result
 * @return Void
 */
void adc_get_conversion_result(_adc_config_t *adc_result, uint16 *conversion_result);


#if ADC_INTERRUPT == INTERNEL_INTERRUPT_ENABLE
/**
 * @brief Start The Conversion Status Using Interrupt 
 * @note We Use Interrupt Feauture In This Function
 * @param adc_obj > Pointer to ADC Configuration
 * @param channel_select > Selected Channel
 * @return Void
 */
void adc_start_conversion_Interrupt(_adc_config_t *adc_obj, _adc_channel_select_t channel_select);
#endif

/* ____________________________ Function Declaration Section Ending ____________________________ */



#endif /* MCAL_ADC_H */
