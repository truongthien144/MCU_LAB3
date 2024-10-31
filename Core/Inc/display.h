/*
 * display.h
 *
 *  Created on: Oct 25, 2024
 *      Author: TruongThien
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "fsm.h"
#include "main.h"
#include "software_timer.h"

void display7SEG(int num1, int num2);
void update7SEG(int turn);
void toggle7SEG(int turn);
void turnOff7SEG();
void allLEDOff();
void displayOutput();
void setting_stage();

#endif /* INC_DISPLAY_H_ */
