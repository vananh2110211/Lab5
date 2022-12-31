/*
 * command.h
 *
 *  Created on: Dec 21, 2022
 *      Author: ASUS
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include <stdint.h>


void command_parser_fsm () ;
unsigned char get_flag () ;
char * get_command () ;
void clear_command () ;
extern uint8_t temp ;

#endif /* INC_COMMAND_H_ */
