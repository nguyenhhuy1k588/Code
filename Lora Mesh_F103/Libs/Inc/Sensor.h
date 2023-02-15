#ifndef SENSOR_H
#define SENSOR_H

#include "main.h"
#include "stdint.h"
#define SENSOR_1     0x01
#define SENSOR_2     0X02

typedef struct
{
	uint8_t sensor_ID;
	int16_t temperature;
	int16_t humidty;
	UART_HandleTypeDef *huart;
} SENSOR_HandleTypedef;

typedef enum
{
	Idle,
	Slave_1,
	Slave_2
} SENSOR_state_t;

void Sensor_Init(SENSOR_HandleTypedef *p_SENSOR, UART_HandleTypeDef *p_huart, uint8_t p_ID);
void Sensor_Send_cmd(SENSOR_HandleTypedef *p_SENSOR);
void Sensor_Handle(uint8_t *state);

#endif
