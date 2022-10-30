#include "dosingSystemCommon.h"

int32_t dosingSystemCheckCurMode(void){
    if( gpio_get(MODE_SELECT_AUTO_GPIO10) &&  gpio_get(MODE_SELECT_MANUAL_GPIO11) )     return STATUS_MODE_INVALID;
    else if( gpio_get(MODE_SELECT_AUTO_GPIO10) )                                        return  STATUS_MODE_AUTO;
    else if(gpio_get(MODE_SELECT_MANUAL_GPIO11))                                        return  STATUS_MODE_MANUAL;
    else                                                                                return STATUS_MODE_NONE;
}


int32_t dosingSystemModbusReadData(void){
    sleep_ms(MODBUS_RECV_WAIT);
    if( dsModbusBuferOffset >= MODBUS_PACKET_SIZE ){
        memcpy( &dsModbusCommPkt, dsModbusUartBuffer, MODBUS_PACKET_SIZE);
        if(  (DS_SLAVE_ADDR == dsModbusCommPkt.slaveAddr) && (DS_CRC_VALUE == dsModbusCommPkt.crcValue) ){
            if( DS_FUNC_CODE_CONTROL == dsModbusCommPkt.functionCode )  return STATUS_SUCCESS;
            else                                                        return STATUS_FAILURE;
        }
        else                                                            return STATUS_FAILURE;
    }
    else                                                                return STATUS_FAILURE;
}


int32_t dosingSystemMotorCtrl(void){
    if( CTRL_MOTOR1_OFF == dsModbusCommPkt.dataMotorStatus)       gpio_put(CONTROL_M1, false);         
    else if( CTRL_MOTOR1_ON == dsModbusCommPkt.dataMotorStatus ){
        gpio_put(CONTROL_M1, true); 
        gpio_put(CONTROL_M2, false); 
    }       
    else if( CTRL_MOTOR2_OFF == dsModbusCommPkt.dataMotorStatus )   gpio_put(CONTROL_M2, false);  
    else if( CTRL_MOTOR2_ON == dsModbusCommPkt.dataMotorStatus ){
        gpio_put(CONTROL_M2, true); 
        gpio_put(CONTROL_M1, false);   
    }
    else return STATUS_FAILURE;

    return STATUS_SUCCESS; 
}