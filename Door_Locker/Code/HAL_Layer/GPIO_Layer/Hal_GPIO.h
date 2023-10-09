/**
 * *****************************************************************************************************
 * * File           : Hal_GPIO.h
 * * Auther         : Muhammed Ali Ibrahim Ahmed
 * * Details        : GPIO Driver Module
 * * Linkedin       : https://www.linkedin.com/in/muhammedalii9/
 * * Date Created   : 29 July,2023
 * *****************************************************************************************************
 */
#ifndef HAL_GPIO_H
#define HAL_GPIO_H
/* __________________________  Include Section Beginning  __________________________ */

#include "C:/Program Files/Microchip/xc8/v2.30/pic/include/proc/pic18f4620.h"
#include "../MCAL_Std_Types.h"
#include "../Device_Config.h"
#include "Hal_GPIO.h"
#include "Hal_GPIO_cfg.h"

/* __________________________ Include Section Ending __________________________ */

/* __________________________ Macro Definition Section Beginning __________________________ */

#define BIT_MASK                (uint8)1
#define PORT_PINS_MAX_NUMBER    8
#define PORT_MAX_NUMBER         5
#define PORT_MASK               0XFF

/* __________________________ Macro Definition Section Ending __________________________ */

/* __________________________ Macro Funcion Declarations Section Beginning __________________________ */

/* Macro Function to Set Address for Register */
#define HWREG8(_x)                  (*((volatile uint8 *)(_x)))
/**
 * @brief Macro Function to SET Bit 
 * @param REG > Register 
 * @param BIT_POS > Bit Position
*/
#define SET_BIT(REG, BIT_POS)       (REG |= (BIT_MASK << BIT_POS))
/**
 * @brief Macro Function to CLEAR Bit 
 * @param REG > Register 
 * @param BIT_POS > Bit Position
*/
#define CLEAR_BIT(REG, BIT_POS)     (REG &= ~(BIT_MASK << BIT_POS))
/**
 * @brief Macro Function to TOGGLE Bit 
 * @param REG > Register 
 * @param BIT_POS > Bit Position
*/
#define TOGGLE_BIT(REG, BIT_POS)    (REG ^= (BIT_MASK << BIT_POS))
/**
 * @brief Macro Function to READ Bit 
 * @param REG > Register 
 * @param BIT_POS > Bit Position
*/
#define READ_BIT(REG, BIT_POS)      ((REG >> BIT_POS) & BIT_MASK)


/* __________________________ Macro Funcion Declarations Section Ending __________________________ */

/* __________________________ Data Type Declarations Section Beginning __________________________ */

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH

} _logic_t;

typedef enum
{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
} _direction_t;
typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
} _pin_index_t;

typedef enum
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX

} _port_index_t;

typedef struct
{
    uint8 port          : 3;        /* @ref _port_index_t */
    uint8 pin           : 3;        /* @ref _pin_index_t */
    uint8 direction     : 1;        /* @ref _direction_t */
    uint8 logic         : 1;        /* @ref _logic_t */

} _pin_config_t;
/* __________________________ Data Type Declarations Section Ending __________________________ */

/* __________________________ Function Declaration Section Beginning __________________________ */

/**
 * @brief Initialize The Direction of Pin by Writing on [TRIS Register]
 * @param _pin_config > Pointer to the configration
 * @return  (E_OK): Done successfully .... (E_NOT_OK): Failed to Implement
 */
void gpio_pin_initialize_direction(const _pin_config_t *config_pin);

/**
 * @brief Getting The Direction of Bit by knowin the Logic at [TRIS Register]
 * @param config_pin > Pointer to the configration
 * @param direction_status > Pointer to the direction
 */
void gpio_pin_get_direction_status(const _pin_config_t *config_pin, _direction_t *direction_status);

/**
 * @brief Write The Logic of Pin by writting on [LAT Register]
 * @param config_pin > Pointer to the configration
 * @param logic > Logic that will write on Pin
 */
void gpio_pin_write_logic(const _pin_config_t *config_pin, _logic_t logic);

/**
 * @brief Read The Logic of Pin by Reading [Port REGISTER]
 * @param config_pin > Pointer to the configration
 * @param logic > Pointer to the Logic Status
 */
void gpio_pin_read_logic(const _pin_config_t *config_pin, _logic_t *logic);

/**
 * @brief  Toggle The Logic of Pin by Toggling [LAT REGISTER]
 * @param config_pin > Pointer to the configration
 */
void gpio_pin_toggle_logic(const _pin_config_t *config_pin);

/**
 * @brief Initialize Pin
 * @param config_pin > Pointer to the configration
 */
void gpio_pin_initialize(const _pin_config_t *config_pin);

/**
 * @brief Initialize The Direction of Port by Writting on [TRIS REGISTER]
 * @param port
 * @param direction
 */
#if GPIO_PORT_CONIG == CONFIG_ENABLE
void gpio_port_direction_initialize(_port_index_t port, uint8 direction);

/**
 * @brief Getting The Direcion of Port by knowing the Logic at [TRIS REGISTER]
 * @param port
 * @param direction_status > Pointer to direction Status
 */
void gpio_port_get_direction_status(_port_index_t port, uint8 *direction_status);

/**
 * @brief Writing The Logic of Port By Writing on [LAT REGISTER]
 * @param port > Prot Name
 * @param logic > Logic 
 */
void gpio_port_write_logic(_port_index_t port, uint8 logic);

/**
 * @brief Reading The logic of Port By Reading the [LAT REGISTER]
 * @param port > Prot Name
 * @param logic > Logic 
 */
void gpio_port_read_logic(_port_index_t port, uint8 *logic);

/**
 * @brief Toggle The Logic of Port By Toggling [LAT REGISTER]
 * @param port
 */
void gpio_port_toggle_logic(_port_index_t port);

#endif
/* ______________________ Function Declaration Section Ending ______________________ */

#endif /* HAL_GPIO_H */

/**
 * ******************************************************************************************************
 * *      User                   Date                                 Brief
 * ******************************************************************************************************
 * *     Muhammed Ali            29 July,2023                         Writting Hal_GPIO.h
 */