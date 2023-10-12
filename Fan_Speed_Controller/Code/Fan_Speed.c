
/**
 * *****************************************************************************************************
 * * File           : Fan_Speed.c
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Fan Speed Temperature Controller Project
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 12 October , 2023
 * *****************************************************************************************************
 */

/* ________________________ Include Section Start ________________________ */
#include "Fan_Speed.h"
/* ________________________ Include Section End ________________________ */

/* ________________________ Variables Definition Start ________________________ */

_adc_config_t lm35_Sensor = {
    .adc_Interrupt_Handler = NULL,
    .acquistition_time = ADC_12_TD,
    .channel = ADC_CHANNEL0_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = RESULT_FORMAT_RIGHT,
    .voltage_reference = VOLTAGE_REFERENCE_DISABLE,
};
uint16 lm1_res; // Result From LM35 ( Room 1 )
uint16 lm2_res; // Result From LM35 ( Room 2 )
uint16 lm1_cel; // Store Result
uint16 lm2_cel; // Store Result
uint8 lm1_cel_txt[7];
uint8 lm2_cel_txt[7];

/* ________________________ Variables Definition End ________________________ */

/* ________________________ Main Application Start ________________________ */

int main()
{
    Application_Init();
    lcd_8bit_send_string_pos(&lcd_8bit, 1, 1, "Fan Speed Controller");
    lcd_8bit_send_string_pos(&lcd_8bit, 2, 1, " Room 1 Temp:");
    lcd_8bit_send_string_pos(&lcd_8bit, 3, 1, " Room 2 Temp:");
    while (1)
    {
        adc_get_conversion_result_Blocking(&lm35_Sensor, ADC_CHANNEL0_AN0, &lm1_res);
        adc_get_conversion_result_Blocking(&lm35_Sensor, ADC_CHANNEL1_AN1, &lm2_res);
        lm1_cel = (uint16)(lm1_res * 4.88f); /* 5000(mv) / 1024(10-Bit) => 4.88 */
        lm2_cel = (uint16)(lm2_res * 4.88f); /* 5000(mv) / 1024(10-Bit) => 4.88 */
        lm1_cel /= 10;                       /* The sensitivity of LM35 is 10 mV/degree Celsius */
        lm2_cel /= 10;                       /* The sensitivity of LM35 is 10 mV/degree Celsius */
        convert_uint16_to_string(lm1_cel, lm1_cel_txt);
        convert_uint16_to_string(lm2_cel, lm2_cel_txt);
        lcd_8bit_send_string_pos(&lcd_8bit, 2, 14, lm1_cel_txt);
        lcd_8bit_send_string_pos(&lcd_8bit, 3, 14, lm2_cel_txt);

        if (lm1_cel > 20)
        {
            dc_motor_turn_right(&Motor_Room_1);
        }
        else
        {
            dc_motor_stop(&Motor_Room_1);
        }
        if (lm2_cel > 20)
        {
            dc_motor_turn_right(&Motor_Room_2);
        }
        else
        {
            dc_motor_stop(&Motor_Room_2);
        }
    }
    return (EXIT_SUCCESS);
}

void Application_Init(void)
{
    Ecu_Layer_Init();
    adc_initialize(&lm35_Sensor);
}
/* ________________________ Main Application End ________________________ */

/* ________________________ Function Definition Start ________________________*/

/* ________________________ Function Definition End ________________________*/