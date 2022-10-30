#include "dosingSystemCommon.h"

// RX interrupt handler
void dosingSystemModbusHandler() {

    while (uart_is_readable(MODBUS_UART1)) {
        dsModbusUartBuffer[dsModbusBuferOffset++] = uart_getc(MODBUS_UART1);
        if( dsModbusBuferOffset == MODBUS_BUFFER_SIZE)  dsModbusBuferOffset = 0;
    }
}

void dosingSystemLevelSensorHandler(uint gpio, uint32_t events){
    
}