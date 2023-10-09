/**
 * ***************************************************************************************************
 * * File           : ECU_chr_lcd.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : ECU character Source File
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 12 Augast,2023
 * ***************************************************************************************************
 */

/* _________________________  Include Section Beginning  _________________________ */
#include "ecu_chr_lcd.h"
/* _________________________  Include Section Ending  _________________________ */

/* _________________________ Healper Functions Declarations Section Beginning _________________________ */

static void lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static void lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static void lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn);
static void lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static void lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn);
/* _________________________ Healper Functions Declarations Section Ending _________________________ */

/**
 * @brief Initialize Character LCD 4 Bit Mode
 * @param lcd > Pointer to LCD Configraion
 */
void lcd_4bit_intialize(const chr_lcd_4bit_t *lcd)
{
    uint8 l_data_pins_counter = ZERO;

    gpio_pin_initialize(&(lcd->lcd_rs));
    gpio_pin_initialize(&(lcd->lcd_en));
    for (l_data_pins_counter = ZERO; l_data_pins_counter < 4; l_data_pins_counter++)
    {
        gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
    }
    __delay_ms(20);
    lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_ms(5);
    lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_us(150);
    lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    lcd_4bit_send_command(lcd, _LCD_CLEAR);
    lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
    lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
    lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
    lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
    lcd_4bit_send_command(lcd, 0x80);
}

/**
 * @brief Send Command For Character LCD 4 Bit Mode
 * @param lcd > Pointer to LCD Configraion
 * @param command > Command which will be sent to LCD
 */
void lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command)
{
    /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
    /* Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  */
    gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
    /* Send the Command through the (4-Pins" Data lines */
    lcd_send_4bits(lcd, command >> 4);
    /* Send the Enable Signal on the "E" Pin */
    lcd_4bit_send_enable_signal(lcd);
    /* Send the Command through the (4-Pins" Data lines */
    lcd_send_4bits(lcd, command);
    /* Send the Enable Signal on the "E" Pin */
    lcd_4bit_send_enable_signal(lcd);
}

/**
 * @brief Send Character Data To Character LCD 4 Bit Mode
 * @param lcd  > Pointer to LCD Configraion
 * @param data > Data which will be sent to LCD
 */
void lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data)
{
    /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
    /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
    gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
    /* Send the Data through the (4-Pins" Data lines */
    lcd_send_4bits(lcd, data >> 4);
    /* Send the Enable Signal on the "E" Pin */
    lcd_4bit_send_enable_signal(lcd);
    /* Send the Data through the (4-Pins" Data lines */
    lcd_send_4bits(lcd, data);
    /* Send the Enable Signal on the "E" Pin */
    lcd_4bit_send_enable_signal(lcd);
}

/**
 * @brief Send Character to specified  Postions on LCD
 * @param lcd > Pointer to LCD Configraion
 * @param row > Row Position
 * @param column > Column Position
 * @param data  > Data which will be sent to LCD
 */
void lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    lcd_4bit_set_cursor(lcd, row, column);
    lcd_4bit_send_char_data(lcd, data);
}

/**
 * @brief Send String To LCD
 * @param lcd > Pointer to LCD Configraion
 * @param str > String which will be sent to LCD
 */
void lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str)
{
    while (*str)
    {
        lcd_4bit_send_char_data(lcd, *str++);
    }
}

/**
 * @brief Send String to specified position on lCD
 * @param lcd > Pointer to LCD Configraion> Pointer to LCD Configraion
 * @param row > Row Position
 * @param column > Column Position
 * @param str > String which will be sent to LCD
 */
void lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    lcd_4bit_set_cursor(lcd, row, column);
    while (*str)
    {
        lcd_4bit_send_char_data(lcd, *str++);
    }
}

/**
 * @brief Send Custom Character so LCD
 * @param lcd > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > column Position
 * @param _chr > Character which will be sent to LCD
 * @param mem_pos > Memory Position
 */
void lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,
                               const uint8 _chr[], uint8 mem_pos)
{
    uint8 lcd_counter = ZERO;

    lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
    for (lcd_counter = 0; lcd_counter <= 7; ++lcd_counter)
    {
        lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
    }
    lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
}
/**
 * @brief Sending Number to LCD
 * @param led > Pointer to LCD Configration
 * @param number > Number which will be sent to LCD
 */
void lcd_4bit_send_number(const chr_lcd_4bit_t *lcd, uint32 number)
{
    uint8 NUM[10], l_counter1 = 0, l_counter2 = 0;

    if (number == 0)
    {
        lcd_4bit_send_char_data(lcd, '0');
    }
    else
    {
        while (number)
        {
            NUM[l_counter1] = (number % 10) + '0';
            number /= 10;
            l_counter1++;
        }
        for (l_counter2 = l_counter1; l_counter2 >= 0; l_counter2--)
             lcd_4bit_send_char_data(lcd, NUM[l_counter2 - 1]);
    }
}

/**
 * @brief Sending Number to Custom Position on LCD
 * @param led > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > Column Position
 * @param number > Number which will be sent to LCD
 */
void lcd_4bit_send_number_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 number)
{
    lcd_4bit_set_cursor(lcd, row, column);
    lcd_4bit_send_number(lcd, number);
}

/* _________________________       8 BIT MODE LCD         _________________________ */

/**
 * @brief Initialize Character LCD 8 Bit Mode
 * @param lcd > Pointer to LCD Configration
 */
void lcd_8bit_intialize(const chr_lcd_8bit_t *lcd)
{
    uint8 l_data_pins_counter = ZERO;

    gpio_pin_initialize(&(lcd->lcd_rs));
    gpio_pin_initialize(&(lcd->lcd_en));
    for (l_data_pins_counter = ZERO; l_data_pins_counter < 8; l_data_pins_counter++)
    {
        gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
    }
    __delay_ms(20);
    lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_ms(5);
    lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    __delay_us(150);
    lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

    lcd_8bit_send_command(lcd, _LCD_CLEAR);
    lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
    lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
    lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
    lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
    lcd_8bit_send_command(lcd, 0x80);
}

/**
 * @brief Send Command to LCD
 * @param lcd > Pointer to LCD Configration
 * @param command > Command which will sent to LCD
 */
void lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command)
{
    uint8 l_pin_counter = ZERO;
    /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
    /* Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  */
    gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
    /* Send the Command through the (8-Pins" Data lines */
    for (l_pin_counter = 0; l_pin_counter < 8; ++l_pin_counter)
    {
        gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (command >> l_pin_counter) & (uint8)0x01);
    }
    /* Send the Enable Signal on the "E" Pin */
    lcd_8bit_send_enable_signal(lcd);
}

/**
 * @brief Send Character to LCD
 * @param lcd > Pointer to LCD Configration
 * @param data > Data which will sent to LCD
 */
void lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data)
{
    uint8 l_pin_counter = ZERO;

    /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
    /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
    gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
    /* Send the Data through the (8-Pins" Data lines */
    for (l_pin_counter = 0; l_pin_counter < 8; ++l_pin_counter)
    {
        gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), (data >> l_pin_counter) & (uint8)0x01);
    }
    /* Send the Enable Signal on the "E" Pin */
    lcd_8bit_send_enable_signal(lcd);
}

/**
 * @brief Send Character to Specified Position on LCD
 * @param lcd > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > Colomn Position
 * @param data > Data which will be sent to LCD
 */
void lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data)
{
    lcd_8bit_set_cursor(lcd, row, column);
    lcd_8bit_send_char_data(lcd, data);
}

/**
 * @brief Send String to LCD
 * @param lcd > Pointer to LCD Configration
 * @param str > String which will be sent to LCD
 */
void lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str)
{
    while (*str)
    {
        lcd_8bit_send_char_data(lcd, *str++);
    }
}

/**
 * @brief Send String to Specified Position on LCD
 * @param lcd > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > Column Position
 * @param str > String which will be sent to LCD
 */
void lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str)
{
    lcd_8bit_set_cursor(lcd, row, column);
    lcd_8bit_send_string(lcd, str);
}

/**
 * @brief Send Cutom Character to LCD
 * @param lcd > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > Column Position
 * @param _chr > Character which will be sent to LCD
 * @param mem_pos > Postion of Character
 */
void lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,
                               const uint8 _chr[], uint8 mem_pos)
{
    uint8 lcd_counter = ZERO;

    lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos * 8)));
    for (lcd_counter = 0; lcd_counter <= 7; ++lcd_counter)
    {
        lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
    }
    lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
}

/**
 * @brief Sending Number to LCD
 * @param led > Pointer to LCD Configration
 * @param number > Number which will be sent to LCD
 */
void lcd_8bit_send_number(const chr_lcd_8bit_t *lcd, uint8 number)
{
    uint8 NUM[NUMBER_SIZE], l_counter1 = 0, l_counter2 = 0;

    if (number == 0)
    {
        lcd_8bit_send_char_data(lcd, '0');
    }
    else
    {
        while (number)
        {
            NUM[l_counter1] = (number % 10) + '0';
            number /= 10;
            l_counter1++;
        }
        for (l_counter2 = l_counter1; l_counter2 >= 0; l_counter2--)
             lcd_8bit_send_char_data(lcd, NUM[l_counter2 - 1]);
    }
}

/**
 * @brief Sending Number to Custom Position on LCD
 * @param led > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > Column Position
 * @param number > Number which will be sent to LCD
 */
void lcd_8bit_send_number_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 number)
{
    lcd_8bit_set_cursor(lcd, row, column);
    lcd_8bit_send_number(lcd, number);
}

/**
 * @brief Convert 1 byte to String
 * @param value > Value
 * @param str > Pointer to String
 */
void convert_uint8_to_string(uint8 value, uint8 *str)
{
    memset((char *)str, '\0', 4);
    sprintf(str, "%i", value);
}

/**
 * @brief Convert 2 byte to String
 * @param value > Value
 * @param str > Pointer to String
 */
void convert_uint16_to_string(uint16 value, uint8 *str)
{
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;

    memset(str, ' ', 5);
    str[5] = '\0';
    sprintf((char *)Temp_String, "%i", value);
    while (Temp_String[DataCounter] != '\0')
    {
        str[DataCounter] = Temp_String[DataCounter];
        DataCounter++;
    }
}

/**
 * @brief Convert 4 byte to String
 * @param value > Value
 * @param str > Pointer to String
 */
void convert_uint32_to_string(uint32 value, uint8 *str)
{
    memset((char *)str, '\0', 11);
    sprintf(str, "%i", value);
}

/* _________________________ Healper Functions Definition Section Beginning _________________________ */

/**
 * @brief Send 4 bit
 * @param lcd  > Pointer to LCD Configration
 * @param _data_command > Command or Data
 */
static void lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command)
{
    gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
    gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
    gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
    gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
}

/**
 * @brief Send Enable signal to 4 Bit mode LCD
 * @param lcd  > Pointer to LCD Configration
 */
static void lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd)
{
    gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
}

/**
 * @brief Send Enable signal to 4 Bit mode LCD
 * @param lcd > Pointer to LCD Configration
 */
static void lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd)
{
    gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
}

/**
 * @brief Setting the Curser of LCD 8 Bit Mode
 * @param lcd > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > Column Position
 */
static void lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column)
{
    --column;
    switch (row)
    {
    case ROW1:
        lcd_8bit_send_command(lcd, (0x80 + column));
        break; /* 0x00 -> Decimal : 0  */
    case ROW2:
        lcd_8bit_send_command(lcd, (0xc0 + column));
        break; /* 0x40 -> Decimal : 64 */
    case ROW3:
        lcd_8bit_send_command(lcd, (0x94 + column));
        break; /* 0x14 -> Decimal : 20 */
    case ROW4:
        lcd_8bit_send_command(lcd, (0xd4 + column));
        break; /* 0x54 -> Decimal : 84 */
    default:;
    }
}

/**
 * @brief Setting the Curser of LCD 4 Bit Mode
 * @param lcd > Pointer to LCD Configration
 * @param row > Row Position
 * @param column > Column Position
 */
static void lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column)
{

    column--;
    switch (row)
    {
    case ROW1:
        lcd_4bit_send_command(lcd, (0x80 + column));
        break;
    case ROW2:
        lcd_4bit_send_command(lcd, (0xc0 + column));
        break;
    case ROW3:
        lcd_4bit_send_command(lcd, (0x94 + column));
        break;
    case ROW4:
        lcd_4bit_send_command(lcd, (0xd4 + column));
        break;
    default:;
    }
}

/* _________________________ Healper Functions Definition Section Ending _________________________ */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali           12 Augast,2023                         Writting ECU_chr_lcd.c
 */