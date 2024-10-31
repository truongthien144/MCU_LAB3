/*
 * fsm.c
 *
 *  Created on: Oct 25, 2024
 *      Author: TruongThien
 */
#include <fsm.h>
#include "button.h"

int SEG1 = 12, SEG2 = 34;
int SEG_turn = 1;
int MODE = 0;
int MODE_CHANGE = 1;
int fsm_auto_stage = 4;
int prev_mode_val = 0;
int count_WE = -1;
int count_NS = -1;
int GREEN_TIME = 600;
int YELLOW_TIME = 300;
int RED_TIME = 900;

void fsm_setting(){
	if (isButtonPressed(0) == 1){
		MODE++;
		MODE_CHANGE = 1;
		if (MODE == 1){
			prev_mode_val = RED_TIME;
		}
		if (MODE == 2){
			prev_mode_val = YELLOW_TIME;
		}
		if (MODE == 3){
			prev_mode_val = GREEN_TIME;
		}
		if (MODE > 3){
			MODE = 0;
		}
	}
}

void reset_fsm_auto(){
	fsm_auto_stage = 4;
	count_WE = -1;
	count_NS = -1;
	MODE_CHANGE = 0;
}

void fsm_auto_timer(){
    count_WE = count_WE - 1;
    count_NS = count_NS - 1;
}

void fsm_auto(){
    if (fsm_auto_stage == 1){
        if (count_WE <= 0){
            count_WE = YELLOW_TIME;
            fsm_auto_stage = 2;
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, RESET); // Turn on yellow 1
            HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET); // Turn off green 1
        }
    }
    if (fsm_auto_stage == 2){
        if (count_WE <= 0){
            count_WE = RED_TIME;
            count_NS = GREEN_TIME;
            fsm_auto_stage = 3;
            HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, RESET); // Turn on red 1
            HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET); // Turn on green 2
            HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET); // Turn off red 2
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, SET); // Turn off yellow 1
        }
    }
    if (fsm_auto_stage == 3){
        if (count_NS <= 0){
            count_NS = YELLOW_TIME;
            fsm_auto_stage = 4;
            HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET); // Turn off green 2
            HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET); // Turn on yellow 2
        }
    }
    if (fsm_auto_stage == 4){
        if (count_WE <= 0){
            count_WE = GREEN_TIME;
            count_NS = RED_TIME;
            fsm_auto_stage = 1;
            HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, SET);
            HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, SET);
            HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
            HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
            HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
            HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
        }
    }
    SEG1 = count_WE/100 + 1;
    SEG2 = count_NS/100 + 1;
}

void fsm_manual(){
	SEG1 = prev_mode_val / 100;
	SEG2 = MODE + 1;
	if (isButtonPressed(1) == 1){
		prev_mode_val += 100;
		if (prev_mode_val > 9900){
			prev_mode_val = 100;
		}
	}
	if (isButtonPressed(2) == 1){
		if (MODE == 1){
			RED_TIME = prev_mode_val;
			GREEN_TIME = RED_TIME - YELLOW_TIME; //increase green time whenever red time was increased
		}
		if (MODE == 2){
			YELLOW_TIME = prev_mode_val;
			RED_TIME = GREEN_TIME + YELLOW_TIME; //increase red time whenever yellow time was increased
		}
		if (MODE == 3){
			GREEN_TIME = prev_mode_val;
			RED_TIME = GREEN_TIME + YELLOW_TIME; //increase red time whenever green time was increased
		}
		MODE = 0; //back to auto mode when time was set
		MODE_CHANGE = 1;
	}
}

