/**
 * *****************************************************************************************************
 * * File           : Hal_GPIO.c
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : GPIO Driver Module
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 29 July,2023
 * *****************************************************************************************************
 */
/* __________________________  Include Section Beginning  __________________________ */
#include "Hal_GPIO.h"
/* __________________________ Include Section Ending __________________________ */

/**
 * Reference to Data Direction Control Registers
 * TRIS REGISTER is responsible for the direction of data ( Input : 0 or Output : 1)
 */
volatile uint8 *TRIS_REGISTER[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/**
 * Reference to Date Latch Regester ( Read and Write to Data Latch)
 * lAT REGISTER is responsible for Writing Logic on Pin ( High : 1 or Low : 0)
 */
volatile uint8 *LAT_REGISTER[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/**
 * Reference to Port Status Registers
 * PORT REGISTER is responsible for Reading logic of Pin ( High : 5V or Low :0V)
 */
volatile uint8 *PORT_REGISTER[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/* __________________________ Function Definition Section Beginning __________________________ */

#if GPIO_PIN_CONFIG==CONFIG_ENABLE

void gpio_pin_initialize_direction(const _pin_config_t *config_pin)
{
    switch (config_pin->direction)
    {
    case GPIO_DIRECTION_INPUT:
        SET_BIT(*TRIS_REGISTER[config_pin->port], config_pin->pin);
        break;
    case GPIO_DIRECTION_OUTPUT:
        CLEAR_BIT(*TRIS_REGISTER[config_pin->port], config_pin->pin);
        break;

    default:;
    }
};


void gpio_pin_get_direction_status(const _pin_config_t *config_pin, _direction_t *direction_status)
{
    *direction_status = READ_BIT(*TRIS_REGISTER[config_pin->port], config_pin->pin);
};


void gpio_pin_write_logic(const _pin_config_t *config_pin, _logic_t logic)
{
    switch (logic)
    {
    case GPIO_HIGH:
        SET_BIT(*LAT_REGISTER[config_pin->port], config_pin->pin);
        break;
    case GPIO_LOW:
        CLEAR_BIT(*LAT_REGISTER[config_pin->port], config_pin->pin);
        break;
    default:;
    }
};


void gpio_pin_read_logic(const _pin_config_t *config_pin, _logic_t *logic)
{
    *logic = READ_BIT(*PORT_REGISTER[config_pin->port], config_pin->pin);
};


void gpio_pin_toggle_logic(const _pin_config_t *config_pin)
{
    TOGGLE_BIT(*LAT_REGISTER[config_pin->port], config_pin->pin);
};


void gpio_pin_initialize(const _pin_config_t *config_pin)
{
    gpio_pin_initialize_direction(config_pin);
    gpio_pin_write_logic(config_pin, config_pin->logic);
};

#endif


#if GPIO_PORT_CONIG == CONFIG_ENABLE

void gpio_port_direction_initialize(_port_index_t port, uint8 direction)
{
    *TRIS_REGISTER[port] = direction;
};


void gpio_port_get_direction_status(_port_index_t port, uint8 *direction_status)
{
    *direction_status = *TRIS_REGISTER[port];
};


void gpio_port_write_logic(_port_index_t port, uint8 logic)
{
    *LAT_REGISTER[port] = logic;
};


void gpio_port_read_logic(_port_index_t port, uint8 *logic)
{
    *logic = *LAT_REGISTER[port];
};


void gpio_port_toggle_logic(_port_index_t port)
{
    *LAT_REGISTER[port] ^= PORT_MASK;
};
#endif
/* ******************************* Function Definition Section Ending ********************** */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            29 July,2023                         Writting Hal_GPIO.c
 */
