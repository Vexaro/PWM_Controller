/*
 * core.c
 *
 *  Created on: Sep 19, 2025
 *      Author: Шарко
 */

#include "core.h"

uint16_t dead_zone_l = 45;
uint16_t dead_zone_h = 50;

volatile uint16_t rising_edge_time = 0;
volatile uint16_t falling_edge_time = 0;
volatile uint16_t input_period = 0;


void setup (void) {

	return;
}

void update(void) {
	return;
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == TIM1) {

	}
}
