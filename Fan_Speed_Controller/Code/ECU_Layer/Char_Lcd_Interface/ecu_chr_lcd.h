/**
 * *****************************************************************************************************
 * * File           : ECU_chr_lcd.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : ECU character Header File
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 12 Augast,2023
 * *****************************************************************************************************
 */
#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* _________________________  Include Section Beginning  _________________________ */
#include "../../MCAL_Layer/GPIO_Layer/Hal_GPIO.h"
/* _________________________  Include Section Ending  _________________________ */


/* _________________________ Macro Definition Section Beginning _________________________ */


/* _____ LCD Commands ______*/

#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28

/* ________ CGRAM Configration ________ */
#define _LCD_CGRAM_START            0x40
#define _LCD_DDRAM_START            0x80

/* ________ ROWS ________ */

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/* ________ 4-BIT Mode PINS ________*/

#define LCD_4BIT_PIN_D4     0
#define LCD_4BIT_PIN_D5     1
#define LCD_4BIT_PIN_D6     2
#define LCD_4BIT_PIN_D7     3

/* ________ 8-BIT Mode PINS ________*/

#define LCD_8BIT_PIN_D0     0
#define LCD_8BIT_PIN_D1     1
#define LCD_8BIT_PIN_D2     2
#define LCD_8BIT_PIN_D3     3
#define LCD_8BIT_PIN_D4     4
#define LCD_8BIT_PIN_D5     5
#define LCD_8BIT_PIN_D6     6
#define LCD_8BIT_PIN_D7     7

#define NUMBER_SIZE         10
/* _________________________ Macro Definition Section Ending _________________________ */

/* _________________________ Data Type Declarations Section Beginning _________________________ */

typedef struct{
    _pin_config_t lcd_rs;           /* @ref _pin_config_t */
    _pin_config_t lcd_en;           /* @ref _pin_config_t */
    _pin_config_t lcd_data[4];      /* @ref _pin_config_t */
}chr_lcd_4bit_t;

typedef struct{
    _pin_config_t lcd_rs;           /* @ref _pin_config_t */
    _pin_config_t lcd_en;           /* @ref _pin_config_t */
    _pin_config_t lcd_data[8];      /* @ref _pin_config_t */
}chr_lcd_8bit_t;
/* _________________________ Data Type Declarations Section Ending _________________________ */



/* _________________________ Functions Declarations  Section Beginning _________________________ */

void lcd_4bit_intialize(const chr_lcd_4bit_t *lcd);
void lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command);
void lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data);
void lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column, uint8 data);
void lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str);
void lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
void lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos);
void lcd_4bit_send_number_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 number);
void lcd_4bit_send_number(const chr_lcd_4bit_t *lcd, uint32 number);
                                        

void lcd_8bit_intialize(const chr_lcd_8bit_t *lcd);
void lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);
void lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);
void lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column, uint8 data);
void lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str);
void lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
void lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,const uint8 _chr[], uint8 mem_pos);
void lcd_8bit_send_number(const chr_lcd_8bit_t *lcd, uint8 number);
void lcd_8bit_send_number_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 number);

void convert_uint8_to_string(uint8 value, uint8 *str);
void convert_uint16_to_string(uint16 value, uint8 *str);
void convert_uint32_to_string(uint32 value, uint8 *str);

/* _________________________ Functions Declarations  Section Beginning _________________________ */


#endif	/* ECU_CHR_LCD_H */


/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            12 Augast,2023                       Writting ECU_chr_lcd.h
 */