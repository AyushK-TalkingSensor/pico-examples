#ifndef __DOSING_SYSTEM_COMMON_H__
    #define __DOSING_SYSTEM_COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define MODBUS_BUFFER_SIZE                      64
#define MODBUS_PACKET_SIZE                      sizeof(dsCommModBusPkt_t)
#define MODBUS_RECV_WAIT                        (5 * 1000)

#define TRACE_UART0                             uart0
#define TRACE_UART0_TX_PIN                      0               
#define TRACE_UART0_RX_PIN                      1
#define TRACE_BAUD_RATE                         115200
#define TRACE_DATA_BITS                         8
#define TRACE_STOP_BITS                         1
#define TRACE_PARITY                            UART_PARITY_NONE

#define MODBUS_UART1                            uart1
#define MODBUS_UART1_TX_PIN                     4               
#define MODBUS_UART1_RX_PIN                     5
#define MODBUS_BAUD_RATE                        9600
#define MODBUS_DATA_BITS                        8
#define MODBUS_STOP_BITS                        1
#define MODBUS_PARITY                           UART_PARITY_NONE

#define LEVEL_SENSOR_GPIO2                      2
#define LEVEL_SENSOR_GPIO3                      3
#define PULSE_SENSOR_GPIO8                      8
#define PULSE_SENSOR_GPIO9                      9

#define MODE_SELECT_AUTO_GPIO10                 10        
#define MODE_SELECT_MANUAL_GPIO11               11       

#define CONTROL_M1                              15
#define CONTROL_M2                              16

#define LED_STATUS_M1_GPIO17                    17
#define LED_STATUS_M2_GPIO18                    18
#define LED_STATUS_MH1_GPIO19                   19
#define LED_STATUS_MH2_GPIO20                   20
#define LED_STATUS_T1_GPIO21                    21
#define LED_STATUS_T2_GPIO22                    22

#define DS_SLAVE_ADDR                           0x01
#define DS_FUNC_CODE_STATUS                     0x00
#define DS_FUNC_CODE_CONTROL                    0x01
#define DS_CRC_VALUE                            0xAABB 


typedef enum{ STATE_IDLE = 0, STATE_MANUAL, STATE_AUTO }dsStemState_t;
typedef enum{ STATUS_MODE_MANUAL = 0, STATUS_MODE_AUTO, STATUS_MODE_NONE, STATUS_MODE_INVALID, STATUS_SUCCESS, STATUS_FAILURE }dsModeStatus_t;
typedef enum{ CTRL_MOTOR1_OFF = 0x00, CTRL_MOTOR1_ON = 0x01, CTRL_MOTOR2_OFF = 0x10, CTRL_MOTOR2_ON = 0x11}dsMotorCtrl_t;

typedef struct{
    uint8_t slaveAddr;
    uint8_t functionCode;
    uint8_t dataMotorStatus;
    uint8_t dataLevelStatus;
    uint8_t dataHealthStatus;
    uint16_t crcValue;
    uint8_t tailByte;
}dsCommModBusPkt_t;

extern uint8_t dsModbusUartBuffer[MODBUS_BUFFER_SIZE];
extern int8_t dsModbusBuferOffset;
extern dsCommModBusPkt_t dsModbusCommPkt;

extern void dosingSystemTestApp(void);
extern void dosingSystemLevelSensorInit(void);
extern void dosingSystemPulseSensorInit(void);
extern void dosingSystemModbusCommInit(void);
extern void dosingSystemTraceInit(void);
extern void dosingSystemLedStatusInit(void);
extern void dosingSystemModeSelectInit(void);
extern void dosingSystemMotorCtrlInit(void);
extern void dosingSystemModbusHandler(void);
extern void dosingSystemLevelSensorHandler(uint gpio, uint32_t events);



#endif /* End of __DOSING_SYSTEM_COMMON_H__ */
