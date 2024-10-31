/*
 * display.c
 *
 *  Created on: Oct 25, 2024
 *      Author: TruongThien
 */
#include "display.h"

void display7SEG(int num1, int num2){
	const uint8_t segmentPatterns[10] = {
	        0b11000000, // 0
	        0b11111001, // 1
	        0b10100100, // 2
	        0b10110000, // 3
	        0b10011001, // 4
	        0b10010010, // 5
	        0b10000010, // 6
	        0b11111000, // 7
	        0b10000000, // 8
	        0b10010000  // 9
	};

	if (num1 < 0 || num1 > 9 || num2 < 0 || num2 > 9){
		return;// Handle invalid input
	}

	uint8_t segments1 = segmentPatterns[num1];
	uint8_t segments2 = segmentPatterns[num2];


	// Set the GPIO pins according to the 7-segment pattern for the digit
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, (segments1 & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, (segments1 & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, (segments1 & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, (segments1 & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, (segments1 & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, (segments1 & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, (segments1 & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(SEG0A_GPIO_Port, SEG0A_Pin, (segments2 & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG1A_GPIO_Port, SEG1A_Pin, (segments2 & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG2A_GPIO_Port, SEG2A_Pin, (segments2 & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG3A_GPIO_Port, SEG3A_Pin, (segments2 & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG4A_GPIO_Port, SEG4A_Pin, (segments2 & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG5A_GPIO_Port, SEG5A_Pin, (segments2 & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEG6A_GPIO_Port, SEG6A_Pin, (segments2 & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void toggle7SEG(int turn){
	if (turn == 1){
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		return;
	}
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
}

void turnOff7SEG(){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
}

void update7SEG(int turn){
	if (turn == 1){
		display7SEG(SEG1 / 10, SEG1 % 10);
		return;
	}
	display7SEG(SEG2 / 10, SEG2 % 10);
}

void DISPLAY_OUTPUT(){
	turnOff7SEG();
	toggle7SEG(SEG_turn);
	SEG_turn = 1 - SEG_turn;
}

void ALL_LED_OFF(){
    HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, SET);
    HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, SET);
    HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
    HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
}

void setting_stage(){
	if (MODE_CHANGE == 1){
		ALL_LED_OFF();
		MODE_CHANGE = 0;
	}
	if (timer2_flag == 1){
		//For red LEDs
		if (MODE == 1){
			HAL_GPIO_TogglePin(D0_GPIO_Port, D0_Pin);
			HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
		}
		//For yellow LEDs
		if (MODE == 2){
			HAL_GPIO_TogglePin(D1_GPIO_Port, D1_Pin);
			HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
		}
		//For green LEDs
		if (MODE == 3){
			HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
			HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
		}
		setTimer2(25); //Blinking in 2Hz
	}
}
