add_executable(serialIRQ
        serialIRQ.c
        )

# pull in common dependencies
target_link_libraries(serialIRQ pico_stdlib hardware_uart)

# create map/bin/hex file etc.
pico_add_extra_outputs(serialIRQ)

# add url via pico_set_program_url
example_auto_set_url(serialIRQ)
