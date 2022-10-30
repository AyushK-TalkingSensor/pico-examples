#include "dosingSystemCommon.h"

void dosingSystemLevelSensorInit(void){
    gpio_init(LEVEL_SENSOR_GPIO2 | LEVEL_SENSOR_GPIO3);
    gpio_pull_down(LEVEL_SENSOR_GPIO2 | LEVEL_SENSOR_GPIO3);
    gpio_set_irq_enabled_with_callback( (LEVEL_SENSOR_GPIO2 | LEVEL_SENSOR_GPIO3), GPIO_IRQ_EDGE_RISE, true, &dosingSystemLevelSensorHandler);
}

void dosingSystemPulseSensorInit(void){
    gpio_init(PULSE_SENSOR_GPIO8 | PULSE_SENSOR_GPIO9);
    gpio_set_dir((PULSE_SENSOR_GPIO8 | PULSE_SENSOR_GPIO9), GPIO_IN);
}

void dosingSystemLedStatusInit(void){
    gpio_init(LED_STATUS_M1_GPIO17 | LED_STATUS_M2_GPIO18 | LED_STATUS_MH1_GPIO19 | LED_STATUS_MH2_GPIO20 | LED_STATUS_T1_GPIO21 | LED_STATUS_T2_GPIO22);
    gpio_pull_down(LED_STATUS_M1_GPIO17 | LED_STATUS_M2_GPIO18 | LED_STATUS_MH1_GPIO19 | LED_STATUS_MH2_GPIO20 | LED_STATUS_T1_GPIO21 | LED_STATUS_T2_GPIO22);
    gpio_set_dir((LED_STATUS_M1_GPIO17 | LED_STATUS_M2_GPIO18 | LED_STATUS_MH1_GPIO19 | LED_STATUS_MH2_GPIO20 | LED_STATUS_T1_GPIO21 | LED_STATUS_T2_GPIO22), GPIO_OUT);
}

void dosingSystemModeSelectInit(void){
    gpio_init(MODE_SELECT_AUTO_GPIO10 | MODE_SELECT_MANUAL_GPIO11);
    gpio_pull_down(MODE_SELECT_AUTO_GPIO10 | MODE_SELECT_MANUAL_GPIO11);
    gpio_set_dir((MODE_SELECT_AUTO_GPIO10 | MODE_SELECT_MANUAL_GPIO11), GPIO_IN);
}

void dosingSystemMotorCtrlInit(void){
    gpio_init(CONTROL_M1 | CONTROL_M2);
    gpio_pull_down(CONTROL_M1 | CONTROL_M2);
    gpio_set_dir((CONTROL_M1 | CONTROL_M2), GPIO_OUT);
}

void dosingSystemModbusCommInit(void){
    // Set up our UART with a basic baud rate.
    uart_init(MODBUS_UART1, MODBUS_BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(MODBUS_UART1_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(MODBUS_UART1_RX_PIN, GPIO_FUNC_UART);

    // Actually, we want a different speed
    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    int __unused actual = uart_set_baudrate(MODBUS_UART1, MODBUS_BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(MODBUS_UART1, false, false);

    // Set our data format
    uart_set_format(MODBUS_UART1, MODBUS_DATA_BITS, MODBUS_STOP_BITS, MODBUS_PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(MODBUS_UART1, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = MODBUS_UART1 == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, &dosingSystemModbusHandler);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(MODBUS_UART1, true, false);
}

void dosingSystemTraceInit(void){
    // Set up our UART with a basic baud rate.
    uart_init(TRACE_UART0, TRACE_BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(TRACE_UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(TRACE_UART0_RX_PIN, GPIO_FUNC_UART);

    // Actually, we want a different speed
    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    int __unused actual = uart_set_baudrate(TRACE_UART0, TRACE_BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(TRACE_UART0, false, false);

    // Set our data format
    uart_set_format(TRACE_UART0, TRACE_DATA_BITS, TRACE_STOP_BITS, TRACE_PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(TRACE_UART0, false);
}