/*
 * fsm.h
 *
 *  Created on: Oct 25, 2024
 *      Author: TruongThien
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"

extern int MODE;
extern int MODE_CHANGE;
extern int fsm_auto_stage;
extern int prev_mode_val;
extern int count_WE;
extern int count_NS;
extern int GREEN_TIME;
extern int YELLOW_TIME;
extern int RED_TIME;
extern int SEG1;
extern int SEG2;
extern int SEG_turn;

void fsm_setting();
void reset_fsm_auto();
void fsm_auto_timer();
void fsm_auto();
void fsm_manual();

#endif /* INC_FSM_H_ */
