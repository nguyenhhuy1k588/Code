#ifndef VALVE_H
#define VALVE_H

#include "main.h"
#include <stdint.h>
#include "button.h"
typedef enum
{
	RUNNING,
	CLOSE,
	OPEN
} VALVE_state_t;
//typedef struct
//{
//	VALVE_state_t valve_state;
////	GPIO_TypeDef *GPIO_CLOSEx;
////	uint16_t GPIO_CLOSE_Pin;
//	BUTTON_HandleTypedef OPEN_SIGNAL;
//	BUTTON_HandleTypedef CLOSE_SIGNAL;
//} VALVE_Handle_Typedef;
void VALVE_Init();
void VALVE_Command();
void VALVE_Handle();
void VALVE_Close();
void VALVE_Open();
#endif /*VALVE_H*/
