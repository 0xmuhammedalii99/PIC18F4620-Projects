/**
 * *****************************************************************************************************
 * * File           : MCAL_adc.c
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : ADC " Analog - Digital Converter"
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 3 September,2023
 * *****************************************************************************************************
 */

/* _____________________________  Include Section Beginning  ________________________________ */
#include "MCAL_adc.h"
/* _____________________________  Include Section Ending  ___________________________________ */

static void adc_input_channel_config(_adc_channel_select_t channel);
static void adc_select_voltage_reference(_adc_config_t *adc_voltref);
static void adc_select_result_format(_adc_config_t *adc_resforma);
static void adc_start_conversion(void);
static void adc_is_conversion_done(_adc_config_t *adc_obj, uint8 *conversion_status);
static void adc_select_channel(_adc_channel_select_t channel_select);

#if ADC_INTERRUPT == INTERNEL_INTERRUPT_ENABLE
static void (*ADC_Interrurpt_Internel_Handler)(void) = NULL;
void ADC_ISR(void)
{
    ADC_CLEAR_FLAG(); // Clear ADC Interrupt Flag
    if (ADC_Interrurpt_Internel_Handler)
    {
        ADC_Interrurpt_Internel_Handler();
    }
}
#endif

/* ____________________________ Function Definition Section Beginning ____________________________ */

void adc_initialize(_adc_config_t *adc_obj)
{
    /* Disable ADC Module */
    ADC_MODULE_DISABLE();
    /*  Channel Configuration */
    ADC_SELECT_CHANNEL(adc_obj->channel);       // Select Channel
    adc_input_channel_config(adc_obj->channel); // Configure Selected Channel as Input
    /* Select Voltage Reference */
    adc_select_voltage_reference(adc_obj);
    /* Select Aquisition Time */
    ADC_SELECT_ACQUISITION_TIME(adc_obj->acquistition_time);
    /* Select Conversion Clock */
    ADC_SELECT_CONVERSION_CLOCK(adc_obj->conversion_clock);
    /* Select Result Format*/
    adc_select_result_format(adc_obj);
/* _________________Interrupt Configration_________________ */
#if ADC_INTERRUPT == INTERNEL_INTERRUPT_ENABLE
    ADC_Interrurpt_Internel_Handler = adc_obj->adc_Interrupt_Handler;
    ADC_INTERRUPT_FEATUER_ENABLE(); // Enable ADC Interrupt
    ADC_CLEAR_FLAG();               // Clear Flag
/* Check Priority */
#if INTERRUPT_PRIORITY_LEVEL == PRIORITY_LEVELS_ENABLE
    switch (adc_obj->priority)
    {
    case INTERRUPT_LOW_PRIORITY:
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_GLOBAL_INTERRUPT_LowPriority_ENABLE();
        ADC_INTERRUPT_LOW_PRIORITY();
        break;
    case INTERRUPT_HIGH_PRIORITY:
        INTERRUPT_PRIORITY_ENABLE();
        INTERRUPT_GLOBAL_INTERRUPT_LowPriority_ENABLE();
        ADC_INTERRUPT_HIGH_PRIORITY();
        break;
    default:
        /*Nothing*/
        break;
    }
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
    /* Enable ADC Module */
    ADC_MODULE_ENABLE();
}

void adc_get_conversion_result_Blocking(_adc_config_t *adc_obj, _adc_channel_select_t channel_select,
                                        uint16 *conv_result)
{
    adc_select_channel(channel_select);
    adc_start_conversion();
    while (ADCON0bits.GO_nDONE)
        ;
    adc_get_conversion_result(adc_obj, conv_result);
}

void adc_get_conversion_result(_adc_config_t *adc_result, uint16 *conversion_result)
{
    switch (adc_result->result_format)
    {
    case RESULT_FORMAT_RIGHT:
        *conversion_result = (uint16)(ADRESL + (ADRESH << 8));
        break;
    case RESULT_FORMAT_LEFT:
        *conversion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        break;
    default:
        *conversion_result = (uint16)(ADRESL + (ADRESH << 8));
        break;
    }
}
#if ADC_INTERRUPT == INTERNEL_INTERRUPT_ENABLE
void adc_start_conversion_Interrupt(_adc_config_t *adc_obj, _adc_channel_select_t channel_select)
{
    adc_select_channel(channel_select);
    adc_start_conversion();
}
#endif

/* ________________________ Helper Function Definition Section Beginning _________________________ */

static void adc_input_channel_config(_adc_channel_select_t channel)
{
    switch (channel)
    {
    case ADC_CHANNEL0_AN0:
        SET_BIT(TRISA, _TRISA_RA0_POSITION);
        break;
    case ADC_CHANNEL1_AN1:
        SET_BIT(TRISA, _TRISA_RA1_POSITION);
        break;
    case ADC_CHANNEL2_AN2:
        SET_BIT(TRISA, _TRISA_RA2_POSITION);
        break;
    case ADC_CHANNEL3_AN3:
        SET_BIT(TRISA, _TRISA_RA3_POSITION);
        break;
    case ADC_CHANNEL4_AN4:
        SET_BIT(TRISA, _TRISA_RA5_POSITION);
        break;
    case ADC_CHANNEL5_AN5:
        SET_BIT(TRISE, _TRISE_RE0_POSITION);
        break;
    case ADC_CHANNEL6_AN6:
        SET_BIT(TRISE, _TRISE_RE1_POSITION);
        break;
    case ADC_CHANNEL7_AN7:
        SET_BIT(TRISE, _TRISE_RE2_POSITION);
        break;
    case ADC_CHANNEL8_AN8:
        SET_BIT(TRISB, _TRISB_RB2_POSITION);
        break;
    case ADC_CHANNEL9_AN9:
        SET_BIT(TRISB, _TRISB_RB3_POSITION);
        break;
    case ADC_CHANNEL10_AN10:
        SET_BIT(TRISB, _TRISB_RB1_POSITION);
        break;
    case ADC_CHANNEL11_AN11:
        SET_BIT(TRISB, _TRISB_RB4_POSITION);
        break;
    case ADC_CHANNEL12_AN12:
        SET_BIT(TRISB, _TRISB_RB0_POSITION);
        break;
    }
}

static void adc_select_voltage_reference(_adc_config_t *adc_voltref)
{
    switch (adc_voltref->voltage_reference)
    {
    case VOLTAGE_REFERENCE_ENABLE:
        ADC_VOLTAGE_REFERENCE_ENABLE();
        break;
    case VOLTAGE_REFERENCE_DISABLE:
        ADC_VOLTAGE_REFERENCE_DISABLE();
        break;
    }
}

static void adc_select_result_format(_adc_config_t *adc_resforma)
{
    switch (adc_resforma->result_format)
    {
    case RESULT_FORMAT_RIGHT:
        ADC_RESULT_FORMAT_SELECT_RIGHT();
        break;
    case RESULT_FORMAT_LEFT:
        ADC_RESULT_FORMAT_SELECT_LEFT();
        break;
    }
}

static void adc_select_channel(_adc_channel_select_t channel_select)
{
    ADC_SELECT_CHANNEL(channel_select);       // Select Channel
    adc_input_channel_config(channel_select); // Configure Selected Channel as Input
}

static void adc_start_conversion(void)
{
    ADC_START_CONVERSION();
}

static void adc_is_conversion_done(_adc_config_t *adc_obj, uint8 *conversion_status)
{
    *conversion_status = (uint8)(!(ADC_CONVERSTION_STATUS()));
}
/* __________________________ Helper Function Definition Section Ending ___________________________ */