/**
 ******************************************************************************
 * @file    sim800l.c
 * @author  Leroy Musa
 * @brief   SIM800L GSM module driver for STM32WB55 NUCLEO board.
 *          This file provides firmware functions to communicate with the
 *          SIM800L module, including sending AT commands, sending SMS, and
 *          handling UART communication.
 ******************************************************************************
 */

#include "sim800l.h"
#include <stdio.h> 			// fix for snprintf [0ct 9th 2024]
/**
  * @brief  				Buffer to hold incoming data from SIM800L.
  *         				This buffer is used to store the responses received from the SIM800L module.
  */
char sim800l_buffer[128]; 	// Define a buffer to store data from the module

/**
  * @brief  				Sends an AT command to the SIM800L module and waits for a response.
  *         				This function transmits the given AT command over UART and stores
  *         				the response in the sim800l_buffer.
  * @param  huart: 			Pointer to UART handler for communication.
  * @param  command: 		The AT command string to send to the SIM800L.
  * @retval None
  */
void SIM800L_SendATCommand(UART_HandleTypeDef *huart, char *command)
{
    HAL_UART_Transmit(huart, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);              // Transmit the command via UART
    HAL_UART_Receive(huart, (uint8_t *)sim800l_buffer, sizeof(sim800l_buffer), HAL_MAX_DELAY); // Receive the response from SIM800L
}

/**
  * @brief  				Initializes the SIM800L modem with necessary configurations.
  *         				Sends initial AT commands to ensure the SIM800L is ready for operation.
  * @param  huart: 			Pointer to UART handler for communication.
  * @retval None
  */
void SIM800L_Init(UART_HandleTypeDef *huart)
{
    SIM800L_SendATCommand(huart, AT_CMD_TEST);          // Send test command to verify SIM800L is responding
    SIM800L_SendATCommand(huart, AT_CMD_ECHO_OFF);      // Disable echo mode to prevent commands from being repeated in responses
    SIM800L_SendATCommand(huart, AT_CMD_SMS_TEXT_MODE); // Set SMS mode to text to enable sending human-readable messages
}

/**
  * @brief  				Sends an SMS using the SIM800L module.
  *         				This function sends an SMS to a specified phone number with the given message.
  * @param  huart: 			Pointer to UART handler for communication.
  * @param  phoneNumber: 	The recipient phone number (in international format).
  * @param  message: 		The SMS message content.
  * @retval None
  */
void SIM800L_SendSMS(UART_HandleTypeDef *huart, char *phoneNumber, char *message)
{
    char command[50]; // Create a buffer to hold the AT command

    // Format the AT+CMGS command to send the SMS to the specified phone number
    snprintf(command, sizeof(command), "%s%s\"\r\n", AT_CMD_SEND_SMS, phoneNumber);
    SIM800L_SendATCommand(huart, command);//Send the AT+CMGS=<PhoneNumber> command

    SIM800L_Delay(1000);//Wait for the SIM800L to process the command

    SIM800L_SendATCommand(huart, message);//Send the SMS content

    // Send the end-of-message character (Ctrl+Z) to complete the SMS
    char endMessage = 0x1A;                                              // Ctrl+Z ASCII code (End of SMS)
    HAL_UART_Transmit(huart, (uint8_t *)&endMessage, 1, HAL_MAX_DELAY);  // Transmit Ctrl+Z to confirm message completion
}

/**
  * @brief 					Requests the signal quality from the SIM800L module.
  *         				This function sends the AT+CSQ command to retrieve the signal quality.
  * @param  huart: 			Pointer to UART handler for communication.
  * @retval None
  */
void SIM800L_ReadSignalQuality(UART_HandleTypeDef *huart)
{
    SIM800L_SendATCommand(huart, AT_CMD_SIGNAL_QUALITY);//Send AT+CSQ to request the signal quality
}

/**
  * @brief  				Delay function for the SIM800L.
  *         				This function wraps the HAL_Delay function to introduce a delay in milliseconds.
  * @param  delay_ms: 		Duration of the delay in milliseconds.
  * @retval None
  */
void SIM800L_Delay(uint32_t delay_ms)
{
    HAL_Delay(delay_ms);//Use HAL_Delay to introduce a delay
}
