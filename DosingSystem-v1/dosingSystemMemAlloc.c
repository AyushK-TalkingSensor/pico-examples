#include "dosingSystemCommon.h"

uint8_t dsModbusUartBuffer[MODBUS_BUFFER_SIZE];
int8_t dsModbusBuferOffset = 0;
dsCommModBusPkt_t dsModbusCommPkt;