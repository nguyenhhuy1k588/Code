#include "Valve.h"

extern VALVE_state_t VALVE_state;
extern VALVE_state_t VALVE_prestate;
//uint8_t flag_control = 0;
uint8_t flag_switching_relay = 0;
void VALVE_Init();

void VALVE_Handle()
{
	static uint32_t timer_relay = 0;
	uint8_t uIsClosed = 0, uIsOpened = 0;

	uIsClosed = HAL_GPIO_ReadPin(SIGNAL_CLOSE_GPIO_Port,SIGNAL_CLOSE_Pin);
	uIsOpened = HAL_GPIO_ReadPin(SIGNAL_OPEN_GPIO_Port, SIGNAL_OPEN_Pin);
	if((uIsClosed == 0) & (uIsOpened == 1))
		{
			VALVE_state = OPEN;
			if(VALVE_prestate == RUNNING)
			{
				HAL_GPIO_WritePin(ISOLATE_VALVE_GPIO_Port, ISOLATE_VALVE_Pin, GPIO_PIN_SET);
				flag_switching_relay = 1;
				timer_relay = HAL_GetTick();
			}
		}
	if((uIsClosed == 1) & (uIsOpened == 0))
		{
			VALVE_state = CLOSE;
			if(VALVE_prestate == RUNNING)
			{
				HAL_GPIO_WritePin(ISOLATE_VALVE_GPIO_Port, ISOLATE_VALVE_Pin, GPIO_PIN_SET);
				flag_switching_relay = 1;
				timer_relay = HAL_GetTick();
//				HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_RESET);
//				HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_RESET);
				//HAL_GPIO_WritePin(ISOLATE_VALVE_GPIO_Port, ISOLATE_VALVE_Pin, GPIO_PIN_SET);
			}
		}
	if((uIsClosed == 0) & (uIsOpened == 0)) VALVE_state = RUNNING;
	VALVE_prestate = VALVE_state;

	if(flag_switching_relay)
	{
		if(HAL_GetTick() - timer_relay > 500)
		{

			HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_RESET);
			//HAL_GPIO_WritePin(ISOLATE_VALVE_GPIO_Port, ISOLATE_VALVE_Pin, GPIO_PIN_RESET);


				//HAL_GPIO_WritePin(ISOLATE_VALVE_GPIO_Port, ISOLATE_VALVE_Pin, GPIO_PIN_RESET);
		}
		if(HAL_GetTick() - timer_relay >1000)
		{
			flag_switching_relay = 0;
			HAL_GPIO_WritePin(ISOLATE_VALVE_GPIO_Port, ISOLATE_VALVE_Pin, GPIO_PIN_RESET);
		}
	}

//	return ((!uIsClosed) & uIsOpened);
}

//void VALVE_Command()
//{
//
//	if(1)
//	{
//		//VALVE_prestate = VALVE_state;
//		//VALVE_state = VALVE_Read_Status();
//		//HAL_GPIO_WritePin(ISOLATE_VALVE_GPIO_Port, ISOLATE_VALVE_Pin, GPIO_PIN_RESET);
//		switch (VALVE_state)
//		{
//			case OPEN:
//				HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_RESET);
//				HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_SET);
//
//				//flag_control = 0;
//			break;
//			case CLOSE:
//				HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_RESET);
//				HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_SET);
//				//flag_control = 0;
//			break;
//			default:
//			break;
//		}
//	}
////	if(VALVE_prestate = RUNNING)
//
//}

void VALVE_Close()
{
	if(VALVE_state != CLOSE)
	{
		HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_SET);
	}
}

void VALVE_Open()
{
	if(VALVE_state != OPEN)
	{
		HAL_GPIO_WritePin(RELAY_CLOSE_GPIO_Port, RELAY_CLOSE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(RELAY_OPEN_GPIO_Port, RELAY_OPEN_Pin, GPIO_PIN_SET);

	}
}
