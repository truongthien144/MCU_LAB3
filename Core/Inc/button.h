/*
 * button.h
 *
 *  Created on: Oct 25, 2024
 *      Author: TruongThien
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET
#define BTN_NUM 3
#define LONG_PRESSED_TIME 200


extern int button_flag[BTN_NUM];
extern int button_long_flag[BTN_NUM];

void initButton();
void getKeyInput();
int isButtonPressed(int btn_num);

#endif /* INC_BUTTON_H_ */
