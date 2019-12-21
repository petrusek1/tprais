/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_UART0RXSRC_UART_RX 0x00u /*!<@brief UART0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART0 transmit data source select: UART0_TX pin */

/*! @name PORTA2 (number 28), J1[4]/D1/UART0_TX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_TX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                                /* @} */

/*! @name PORTA1 (number 27), J1[2]/D0/UART0_RX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_RX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                                /* @} */

/*! @name PORTE24 (number 24), U7[4]/I2C0_SCL
  @{ */
#define BOARD_INITPINS_ACCEL_SCL_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_ACCEL_SCL_PIN 24U    /*!<@brief PORTE pin index: 24 */
                                            /* @} */

/*! @name PORTE25 (number 25), U7[6]/I2C0_SDA
  @{ */
#define BOARD_INITPINS_ACCEL_SDA_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_ACCEL_SDA_PIN 25U    /*!<@brief PORTE pin index: 25 */
                                            /* @} */

/*! @name PORTD1 (number 74), J2[12]/D3[3]/D13/LEDRGB_BLUE
  @{ */
#define BOARD_INITPINS_LED_BLUE_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LED_BLUE_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LED_BLUE_PIN 1U     /*!<@brief PORTD pin index: 1 */
                                           /* @} */

/*! @name PORTB19 (number 54), D3[4]/LEDRGB_GREEN
  @{ */
#define BOARD_INITPINS_LED_GREEN_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_LED_GREEN_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_GREEN_PIN 19U    /*!<@brief PORTB pin index: 19 */
                                            /* @} */

/*! @name PORTB18 (number 53), D3[1]/LEDRGB_RED
  @{ */
#define BOARD_INITPINS_LED_RED_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_LED_RED_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_RED_PIN 18U    /*!<@brief PORTB pin index: 18 */
                                          /* @} */


void BOARD_InitBootPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
