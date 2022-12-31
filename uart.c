/*
 * uart.c
 *
 *  Created on: Dec 21, 2022
 *      Author: ASUS
 */

#include "uart.h"
#include "main.h"
#include "command.h"
#include "timer.h"

extern ADC_HandleTypeDef hadc1 ;
extern UART_HandleTypeDef huart2 ;

uint32_t ADC_value = 0;
char str [20];
enum state_uart { RESPONSE , REPEAT };
enum state_uart uartState = RESPONSE ;
void uart_communication_fsm () {
	 switch ( uartState ) {
	 case RESPONSE :
	 	 {
	 		 if (( get_flag () == 1) && ( strcmp ( get_command () , "RST ")== 0) ){
	 			 ADC_value = HAL_ADC_GetValue (& hadc1 ) ; // Get value of ADC_value variable
	 			 HAL_UART_Transmit (& huart2 , ( void *) str , sprintf ( str, "\r\n! ADC =%d#\r\n", ADC_value ) , 1000) ; // Print response
	 			 uartState = REPEAT ;
	 			 setTimer1 (3000) ;
	 		 }

	 		 if (( get_flag () == 1) && ( strcmp ( get_command () , "OK") == 0) ){
	 			 HAL_UART_Transmit (& huart2 , str , sprintf ( str , "\r\nEnd the communication \r\n") , 1000) ;
	 			 clear_command () ;
	 		 }
	 		 break ;
	 	 }
	 case REPEAT :
	 	 {
	 		 if (( timer1_flag == 1) && ( get_flag () == 1) && ( strcmp( get_command () , " RST ") == 0) ) {
	 			 ADC_value = HAL_ADC_GetValue (& hadc1 ) ;
	 			 HAL_UART_Transmit (& huart2 , ( void *) str , sprintf (str , "! ADC =%d#\r\n", ADC_value ) , 1000) ;
	 			 setTimer1 (3000) ; // Repeat transmit ! ADC = ADC_value #every 3 seconds
	 		 } else if( get_flag () == 0) { // When we enter a newcharacter = > Stop loop and wait to a new response
		 uartState = RESPONSE ;
	 		 }
	 }
	 default :
		 break ;
  }
}
