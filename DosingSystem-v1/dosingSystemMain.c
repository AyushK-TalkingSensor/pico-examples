#include "dosingSystemCommon.h"

int main(void)
{
    dosingSystemTraceInit();
    dosingSystemLevelSensorInit();
    dosingSystemPulseSensorInit();
    dosingSystemModbusCommInit();
    dosingSystemLedStatusInit();
    dosingSystemModeSelectInit();
    dosingSystemMotorCtrlInit();

    uart_puts(TRACE_UART0, "\nInitilization Successfully Completed\n");

    dosingSystemTestApp();

    return 0;
}