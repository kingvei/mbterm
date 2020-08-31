#pragma once

#include <stdint.h>

struct CRC
{
public:
	static uint16_t GetCRC16(uint8_t * pucFrame, uint16_t usLen);
};