/*
 * core.c
 *
 *  Created on: Sep 19, 2025
 *      Author: Шарко
 */

#include "core.h"

float dead_zone_l = 0.45;
float dead_zone_h = 0.5;

volatile uint16_t rising_edge_time = 0;
volatile uint16_t falling_edge_time = 0;
volatile uint16_t input_period = 0;
volatile uint8_t flag = 0;
volatile uint16_t prev_rising_edge_time = 0;
volatile float duty_cycle = 0;

uint16_t GetDiff(uint16_t a, uint16_t b);

void setup (void) {

	return;
}

void update(void) {
	if(duty_cycle >= dead_zone_l && duty_cycle <= dead_zone_h) {
		HAL_GPIO_WritePin(GPIOA, R_SWITCH_Pin, 1);
	}
	else {
		HAL_GPIO_WritePin(GPIOA, R_SWITCH_Pin, 0);
	}
	return;
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == TIM1) {
		if(flag == 0) {
			prev_rising_edge_time = rising_edge_time;
			rising_edge_time = htim->Instance->CNT;
			input_period = GetDiff(rising_edge_time,prev_rising_edge_time);

		}

		if(flag == 1) {
			falling_edge_time = htim->Instance->CNT;
			if(input_period) {
				duty_cycle = GetDiff(falling_edge_time, rising_edge_time) / (float) input_period;
			}

		}

	}
}

uint16_t GetDiff(uint16_t a, uint16_t b) {
	if(a >= b) {
		return a - b;
	}
	else {
		return TIM1->ARR - b + a;
	}
}
