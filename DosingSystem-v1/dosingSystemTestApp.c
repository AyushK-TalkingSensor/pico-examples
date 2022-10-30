#include "dosingSystemCommon.h"

void dosingSystemTestApp(void){

    int32_t retVal, state = STATE_IDLE;

    printf("System Application Start Running\n");

    while(true){
        switch(state){
            case STATE_IDLE: retVal = dosingSystemCheckCurMode();
                             if( STATUS_MODE_AUTO == retVal)            state = STATE_AUTO;
                             else if( STATUS_MODE_MANUAL == retVal )    state = STATE_MANUAL;
                             else if( STATUS_MODE_INVALID == retVal ){
                                printf("Invalid Mode Selected\n");
                                state = STATE_IDLE;
                             }
                             else state = STATE_IDLE;
            break;

            case STATE_MANUAL: if( dsModbusBuferOffset ){
                                    if( STATUS_SUCCESS == dosingSystemModbusReadData() ){
                                        if( STATUS_FAILURE == dosingSystemMotorCtrl() )
                                            printf("Invalid motor control command\n");
                                    }
                                    else    printf("Redeived data is invalid\n"); 
                                    memset( &dsModbusCommPkt, 0, MODBUS_PACKET_SIZE);
                                    dsModbusBuferOffset = 0;
                                    state = STATE_MANUAL;
                                }
                                else state = STATE_MANUAL;
            break;

            case STATE_AUTO: 
            break;

        }
    }
}

       
        