/*
 * timer.h
 *
 *  Created on: Dec 21, 2022
 *      Author: ASUS
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define TIMER_CYCLE 10;
static int timer0_counter ;
static int timer0_flag ;

static int timer1_counter ;
static int timer1_flag ;
void setTimer0 (int duration ) ;
void setTimer1 (int duration ) ;
void timer_run () ;
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim );

#endif /* INC_TIMER_H_ */
