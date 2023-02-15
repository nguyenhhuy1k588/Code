#include "Sensor.h"
#include "checksum.h"

extern SENSOR_HandleTypedef Sensor_1;
extern SENSOR_HandleTypedef Sensor_2;


void Sensor_Init(SENSOR_HandleTypedef *p_SENSOR, UART_HandleTypeDef *p_huart, uint8_t p_ID)
{
	p_SENSOR->huart = p_huart;
	p_SENSOR->sensor_ID = p_ID;
}

void Sensor_Send_cmd(SENSOR_HandleTypedef *p_SENSOR)
{
	uint8_t tx_sensor_data[8];
	if(p_SENSOR->sensor_ID == SENSOR_1)
	{
		tx_sensor_data[0]= SENSOR_1;// slave ID
		//tx_sensor_data[7]=0x0B;
	}
	if(p_SENSOR->sensor_ID == SENSOR_2)
	{
		tx_sensor_data[0]= SENSOR_2;// slave ID
		//tx_sensor_data[7]=0x39;
	}
	tx_sensor_data[1]=0x03;//func code for read holding registers
	tx_sensor_data[2]=0x00;
	tx_sensor_data[3]=0x00;//
	tx_sensor_data[4]=0x00;
	tx_sensor_data[5]=0x02;//No.of registers
	//tx_sensor_data[6]=0xC4;
	uint16_t crc=crc_modbus(tx_sensor_data, 6);
	tx_sensor_data[6]=crc&0xFF;// CRC LOW
	tx_sensor_data[7]=(crc>>8)&0xFF;// CRC HIGH
	HAL_UART_Transmit(p_SENSOR->huart, tx_sensor_data, sizeof(tx_sensor_data), 1000);
}

void Sensor_Handle(uint8_t *state)
{
	switch (*state) {
		case Slave_1:
			Sensor_Send_cmd(&Sensor_1);
			*state = Idle;
			break;
		case Slave_2:
			Sensor_Send_cmd(&Sensor_2);
			*state = Idle;
			break;
		case Idle:

			break;
		default:
			break;
	}
}
