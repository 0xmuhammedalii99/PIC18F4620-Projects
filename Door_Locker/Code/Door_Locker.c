/**
 * *****************************************************************************************************
 * * File           : Door_Locker.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : Door Locker Project
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 6 October,2023
 * *****************************************************************************************************
 */

/* ______________________________ Includes Section Beginning ______________________________ */
#include "Door_Locker.h"
/* ______________________________ Includes Section Endig ______________________________ */

/* ______________________ Data Types Declaration Section Beginning ________________________ */

static void LCD_CLEAR_DISPLAY(void);
static void PrintSelection(void);
uint8 KeyPad_Val;         // Store Keypad Value
uint8 g_Getting_Password; // To Get Password From user
uint8 string_val;         // To Store Number and Display it as Character on LCD
uint8 Cheack_pass;        // For Cheacking Password
uint8 Selection_Flag = 1; // To Return for Selection Option Menu

/* ______________________ Data Types Declaration Section Endig ________________________ */

/* ___________________________ Main Application Begenning _____________________________*/

int main()
{
    Application_Initialize(); // Application Initialize
    lcd_4bit_send_string_pos(&lcd, 1, 2, "Door Locker Project");
    __delay_ms(1000);
    LCD_CLEAR_DISPLAY();
    lcd_4bit_send_string_pos(&lcd, 1, 1, "Set Password:");
    Setting_Password(); // Setting Password For First Time
    LCD_CLEAR_DISPLAY();
    lcd_4bit_send_string_pos(&lcd, 1, 5, "Set Pass Done");
    __delay_ms(1000);
    LCD_CLEAR_DISPLAY();
    while (1)
    {
        g_Getting_Password = 0;
        lcd_4bit_send_string_pos(&lcd, 1, 1, "Enter Password:");
        Getting_Password();  
        Cheack_pass=0;               // Getting password From user
        Cheack_pass = Cheacking_Password(); // Cheacking Password
        /*________________________________________*/
        if (Cheack_pass)
        {
            lcd_4bit_send_string_pos(&lcd, 4, 1, "Correct Password");
            __delay_ms(1000);
            LCD_CLEAR_DISPLAY();
            Selection_Flag = 1;
            while (Selection_Flag)
            {
                PrintSelection(); // Print Selection Option For User
                KeyPad_Val = Keypad_Read_Value();
                switch (KeyPad_Val)
                {
                case 1:
                    LCD_CLEAR_DISPLAY();
                    lcd_4bit_send_string_pos(&lcd, 1, 1, "Door 1 is Open");
                    RoomDoorOpen(&Room_1_Open_Led, &Room_1_Close_Led, &Motor_Room_1);
                    lcd_4bit_send_string_pos(&lcd, 1, 1, "Door 1 is Closed");
                    __delay_ms(1000);
                    Selection_Flag = 1;
                    break;
                case 2:
                    LCD_CLEAR_DISPLAY();
                    lcd_4bit_send_string_pos(&lcd, 1, 1, "Door 2 is Open");
                    RoomDoorOpen(&Room_2_Open_Led, &Room_2_Close_Led, &Motor_Room_2);
                    lcd_4bit_send_string_pos(&lcd, 1, 1, "Door 2 is Closed");
                    __delay_ms(1000);
                    Selection_Flag = 1;
                    break;
                case 3:
                    LCD_CLEAR_DISPLAY();
                    lcd_4bit_send_string_pos(&lcd, 1, 1, "Enter New Pass:");
                    Setting_Password();
                    Selection_Flag = 0;
                    break;
                case 4:
                    LCD_CLEAR_DISPLAY();
                    lcd_4bit_send_string_pos(&lcd, 1, 1, "Exit");
                    __delay_ms(1000);
                    Selection_Flag = 0;

                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    LCD_CLEAR_DISPLAY();
                    lcd_4bit_send_string_pos(&lcd, 1, 1, "Invalid Option!!");
                    __delay_ms(1000);
                    LCD_CLEAR_DISPLAY();
                    Selection_Flag = 1;
                    break;
                }
            }
        }
        else
        {
            LCD_CLEAR_DISPLAY();
            lcd_4bit_send_string_pos(&lcd, 1, 1, " Wrong Password!!");
            LCD_CLEAR_DISPLAY();
        }
    }
    return (EXIT_SUCCESS);
}
/* ___________________________ Main Application Ending _____________________________*/

/* ____________________ Function Definition Section Beginning ___________________________*/
void Application_Initialize(void)
{
    ECU_LAYER_INITIALIZE();
};
uint8 Keypad_Read_Value(void)
{
    uint8 l_keyPad_val = 0;
    do
    {
        keypad_get_value(&keypad, &l_keyPad_val);
    } while (l_keyPad_val == '\0');
    __delay_ms(300);
    return l_keyPad_val;
};
void Setting_Password(void)
{
    uint8 l_keypad_val = 0;     // Local Keypad Value
    uint8 l_Password_Val = 0;   // Local Password Value
    uint8 l_coloum_counter = 1; // Local Coloumn Counter
    uint8 string_keypad_val;    // String to Display Keypad Values on LCD
    while (1)
    {
        l_keypad_val = Keypad_Read_Value();
        if ('#' == l_keypad_val)
        {
            l_keypad_val = 0;
            break;
        }
        else
        {
            convert_uint8_to_string(l_keypad_val, &string_keypad_val);
            lcd_4bit_send_char_data_pos(&lcd, 2, l_coloum_counter, string_keypad_val);
            __delay_ms(200);
            lcd_4bit_send_char_data_pos(&lcd, 2, l_coloum_counter, '*');
            l_coloum_counter++;
            l_Password_Val = (l_Password_Val * 10) + l_keypad_val;
            eeprom_write_byte(0x0030, 0x00);
            eeprom_write_byte(0x0030, l_Password_Val);
            
        }
    }
};
void Getting_Password(void)
{
    uint8 l_keypad_value = 0;   // Local Keypad Value
    uint8 l_coloum_counter = 1; // Local Coloumn Counter
    uint8 string_keypad_val;    // String For Keypad Values
    while (1)
    {
        l_keypad_value = Keypad_Read_Value();
        if ('#' == l_keypad_value)
        {
            l_keypad_value = 0;
            break;
        }
        else
        {
            convert_uint16_to_string(l_keypad_value, &string_keypad_val);
            lcd_4bit_send_char_data_pos(&lcd, 2, l_coloum_counter, string_keypad_val);
            __delay_ms(200);
            lcd_4bit_send_char_data_pos(&lcd, 2, l_coloum_counter, '*');
            l_coloum_counter++;
            g_Getting_Password = (g_Getting_Password * 10) + l_keypad_value;
            
        }
    }
};
uint8 Cheacking_Password(void)
{
    uint8 l_Read_eeprom = 0; // Local Read From EEPROM
    uint8 l_cheacking = 0;   // Local To Cheacking Password
    eeprom_read_byte(0x0030, &l_Read_eeprom);
    if (l_Read_eeprom == g_Getting_Password)
    {
        l_cheacking = 1;
    }
    else
    {
        l_cheacking = 0;
    }

    return l_cheacking;
}
void RoomDoorOpen(_led_t *Open_Led, _led_t *Close_Led, _dc_motor_t *motor_obj)
{
    dc_motor_turn_right(motor_obj); // Open The Door
    led_turn_off(Close_Led);        // Close Led Off
    led_turn_on(Open_Led);          // Open Led On
    __delay_ms(1000);
    dc_motor_stop(motor_obj); // Stop Motor For 1 Second
    __delay_ms(1000);
    dc_motor_turn_left(motor_obj); // Close Motor
    __delay_ms(1000);
    dc_motor_stop(motor_obj); // Stop Motor For
    led_turn_off(Open_Led);   // Open Led Off
    led_turn_on(Close_Led);   // Close Led On
}
static void LCD_CLEAR_DISPLAY(void)
{
    lcd_4bit_send_command(&lcd, _LCD_CLEAR);
    __delay_ms(20);
}
static void PrintSelection(void)
{
    lcd_4bit_send_string_pos(&lcd, 1, 1, "1- Open Room 1   ");
    lcd_4bit_send_string_pos(&lcd, 2, 1, "2- Open Room 2");
    lcd_4bit_send_string_pos(&lcd, 3, 1, "3- Set New Password");
    lcd_4bit_send_string_pos(&lcd, 4, 1, "4- Exit");
    lcd_4bit_send_string_pos(&lcd, 4, 11, "Select:");
}

/* ____________________ Function Definition Section Ending ___________________________*/