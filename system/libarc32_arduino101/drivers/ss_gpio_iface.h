/*
 * Copyright (c) 2015, Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SS_GPIO_IFACE_H_
#define SS_GPIO_IFACE_H_

/**
 * \addtogroup arc_driver
 * @{
 * \defgroup gpio_arc_driver GPIO: General Purpose Input/Output API
 * @{
 * \brief Definition of the structure and functions used by GPIO ARC Driver implementation.
 */

#include "data_type.h"
#include "gpio.h"
#include "platform.h"

#define SS_GPIO_8B0_BITS    (8)
#define SS_GPIO_8B1_BITS    (8)

/*!
 * Port list
 */
typedef enum {
    SS_GPIO_8B0=0,     /*!< GPIO port for pins from 0 to 7 */
    SS_GPIO_8B1,       /*!< GPIO port for pins from 8 to 15 */
    SS_PORT_COUNT      /*!< GPIO port count */
} SS_GPIO_PORT;

#ifdef __cplusplus
 extern "C" {
#endif

/*! \fn 
*
*  \brief   Function to deconfig a GPIO previously configured as an interrupt.
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to configure
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_deconfig(SS_GPIO_PORT port_id, uint8_t bit);

/*! \fn     DRIVER_API_RC ss_gpio_set_config(SS_GPIO_PORT port_id, uint8_t bit, gpio_cfg_data_t *config)
*
*  \brief   Function to configure specified GPIO bit in specified GPIO port
*           Configuration parameters must be valid or an error is returned - see return values below.
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to configure
*  \param   config          : pointer to configuration structure
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_INVALID_CONFIG               - if any configuration parameters are not valid\n
*           DRV_RC_CONTROLLER_IN_USE,             if port/bit is in use\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_set_config(SS_GPIO_PORT port_id, uint8_t bit, gpio_cfg_data_t *config);


/*! \fn     DRIVER_API_RC ss_gpio_enable(SS_GPIO_PORT port_id)
*
*  \brief   Function to enable the specified GPIO port
*           Upon success, the specified GPIO port is no longer clock gated in hardware, it is now
*           capable of reading and writing GPIO bits and of generating interrupts.
*
*  \param   port_id         : GPIO port identifier
*  \param   pin             : bit in port to configure
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_INVALID_CONFIG               - if any configuration parameters are not valid\n
*           DRV_RC_CONTROLLER_IN_USE,             if port/bit is in use\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_enable(SS_GPIO_PORT port_id);

/*! \fn     DRIVER_API_RC ss_gpio_disable(SS_GPIO_PORT port_id)
*
*  \brief   Function to disable the specified GPIO port
*           Upon success, the specified GPIO port is clock gated in hardware, it is now
*           incapable of reading, writing GPIO bits and of generating interrupts.
*
*  \param   port_id         : GPIO port identifier
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_INVALID_CONFIG               - if any configuration parameters are not valid\n
*           DRV_RC_CONTROLLER_IN_USE,             if port/bit is in use\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_disable(SS_GPIO_PORT port_id);

/*! \fn     DRIVER_API_RC ss_gpio_write(SS_GPIO_PORT port_id, uint8_t bit, boolean_t value)
*
*  \brief   Function to transmit a block of data to the specified SPI slave
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to configure
*  \param   value           : value to write to bit
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_write(SS_GPIO_PORT port_id, uint8_t bit, boolean_t value);


/*! \fn     DRIVER_API_RC ss_gpio_read(SS_GPIO_PORT port_id, uint8_t bit, boolean_t *value)
*
*  \brief   Function to read a GPIO bit
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to configure
*  \param   *value          : address to place read value
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_read(SS_GPIO_PORT port_id, uint8_t bit, boolean_t *value);

/*! \fn     DRIVER_API_RC ss_gpio_write_port(SS_GPIO_PORT port_id, uint32_t value)
*
*  \brief   Function to write to a value to a given port
*
*  \param   port_id         : GPIO port identifier
*  \param   value           : value to write to port
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_write_port(SS_GPIO_PORT port_id, uint32_t value);

/*! \fn     DRIVER_API_RC ss_gpio_read_port(SS_GPIO_PORT port_id, uint32_t *value)
*
*  \brief   Function to read a given port
*
*  \param   port_id         : GPIO port identifier
*  \param   *value          : location to store result
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC ss_gpio_read_port(SS_GPIO_PORT port_id, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif  /* SS_GPIO_IFACE_H_ */

/**@} @}*/
