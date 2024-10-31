/*
 * button.c
 *
 *  Created on: Oct 25, 2024
 *      Author: TruongThien
 */
#include "button.h"

int KeyReg0[BTN_NUM];
int KeyReg1[BTN_NUM];
int KeyReg2[BTN_NUM];
int KeyReg3[BTN_NUM];

int TimeForKeyPress[BTN_NUM];
int button_flag[BTN_NUM];
int button_long_flag[BTN_NUM];

void initButton(){
	for (int i = 0; i < BTN_NUM; i++){
		KeyReg0[i] = NORMAL_STATE;
		KeyReg1[i] = NORMAL_STATE;
		KeyReg2[i] = NORMAL_STATE;
		KeyReg3[i] = NORMAL_STATE;
		TimeForKeyPress[i] = LONG_PRESSED_TIME;
		button_flag[i] = 0;
		button_long_flag[i] = 0;
	}
}

int isButtonPressed(int btn_num){
	if(button_flag[btn_num] == 1){
		button_flag[btn_num] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int btn_num){
	if(button_long_flag[btn_num] == 1){
		button_long_flag[btn_num] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	for (int i = 0; i < BTN_NUM; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
	}

	KeyReg0[0] = HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin);
	KeyReg0[1] = HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin);
	KeyReg0[2] = HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin);

	for (int i = 0; i < BTN_NUM; i++){
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg2[i] != KeyReg3[i]){
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg3[i] == PRESSED_STATE){
					button_flag[i] = 1;
					TimeForKeyPress[i] = LONG_PRESSED_TIME;
				}
			}
			else{
				TimeForKeyPress[i] --;
				if (TimeForKeyPress[i] == 0){
					TimeForKeyPress[i] = LONG_PRESSED_TIME;
					if (KeyReg3[i] == PRESSED_STATE){
						button_long_flag[i] = 1;
					}
				}
			}
		}
	}
}
