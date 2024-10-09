/**
 ******************************************************************************
 * @file    sim800l.h
 * @author  Leroy Musa
 * @brief   Header file for SIM800L GSM module driver for STM32WB55 NUCLEO board.
 *          This file provides the function declarations, macros, and essential 
 *          AT command constants used for interfacing with the SIM800L GSM module.
 *
 ******************************************************************************
 * @attention
 *
 * This software component is licensed by Leroy Musa under BSD 3-Clause license.
 * 
 ******************************************************************************
 */

#ifndef SIM800L_H
#define SIM800L_H

#include "stm32wbxx_hal.h"
#include <string.h>

/**
  * @defgroup 				SIM800L_Constants SIM800L AT Command Constants
  * @brief    				AT Commands used to communicate with the SIM800L module.
  * @{
  */
#define AT_CMD_TEST             "AT\r\n"                 /*!< Command to test SIM800L communication */
#define AT_CMD_ECHO_OFF         "ATE0\r\n"               /*!< Command to disable command echo */
#define AT_CMD_SMS_TEXT_MODE    "AT+CMGF=1\r\n"          /*!< Set the SMS format to text mode */
#define AT_CMD_SIGNAL_QUALITY   "AT+CSQ\r\n"             /*!< Query the signal quality from the SIM800L */
#define AT_CMD_SEND_SMS         "AT+CMGS=\""             /*!< Command to initiate sending an SMS */
/**
  * @}
  */

/** 
  * @defgroup 				SIM800L_Functions SIM800L Exported Functions
  * @brief    				Function declarations for interfacing with the SIM800L module.
  * @{
  */

/**
  * @brief  				Initializes the SIM800L module.
  *         				This function sets up UART communication, disables echo, and
  *         				ensures the module is ready for operation.
  * @param  huart: 			Pointer to the UART handler used for communication.
  * @retval None
  */
void SIM800L_Init(UART_HandleTypeDef *huart);

/**
  * @brief  				Sends a generic AT command to the SIM800L module.
  *         				This function is used to send AT commands to the module via UART.
  * @param  huart: 			Pointer to the UART handler used for communication.
  * @param  command: 		The AT command string to be sent to the SIM800L module.
  * @retval None
  */
void SIM800L_SendATCommand(UART_HandleTypeDef *huart, char *command);

/**
  * @brief  				Sends an SMS message using the SIM800L module.
  *         				This function initiates the sending of an SMS to a specified phone number.
  * @param  huart: 			Pointer to the UART handler used for communication.
  * @param  phoneNumber: 	The phone number to send the SMS to (in international format).
  * @param  message: 		The message content to be sent.
  * @retval None
  */
void SIM800L_SendSMS(UART_HandleTypeDef *huart, char *phoneNumber, char *message);

/**
  * @brief  				Reads the signal quality from the SIM800L module.
  *         				This function queries the signal strength and quality using the AT+CSQ command.
  * @param  huart: 			Pointer to the UART handler used for communication.
  * @retval None
  */
void SIM800L_ReadSignalQuality(UART_HandleTypeDef *huart);

/**
  * @brief  				Custom delay function for the SIM800L module.
  *         				This function introduces a delay in milliseconds, useful for ensuring
  *         				proper timing when sending AT commands.
  * @param  delay_ms: 		The duration of the delay in milliseconds.
  * @retval None
  */
void SIM800L_Delay(uint32_t delay_ms);

/**
  * @}
  */

#endif /* SIM800L_H */
