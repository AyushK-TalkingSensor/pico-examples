add_executable(Pin_irqwithUart
        Pin_irqwithUart.c
        )

# pull in common dependencies
target_link_libraries(Pin_irqwithUart pico_stdlib hardware_uart)

# create map/bin/hex file etc.
pico_add_extra_outputs(Pin_irqwithUart)

# add url via pico_set_program_url
example_auto_set_url(Pin_irqwithUart)
