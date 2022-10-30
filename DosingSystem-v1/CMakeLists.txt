add_executable( dosingSystemMain 
            dosingSystemMain.c 
            dosingSystemTestApp.c 
            dosingSystemHandler.c 
            dosingSystemInit.c 
            dosingSystemModules.c
            dosingSystemMemAlloc.c
            )
#add_executable( dosingSystemApp dosingSystemApp.c )


# pull in common dependencies
target_link_libraries(dosingSystemMain pico_stdlib hardware_uart)

# create map/bin/hex file etc.
pico_add_extra_outputs(dosingSystemMain)

# add url via pico_set_program_url
example_auto_set_url(dosingSystemMain)
#add_executable(dosingSystemTestApp dosingSystemTestApp.c)
#add_executable(dosingSystemHandler dosingSystemHandler.c)
#add_executable(dosingSystemInit dosingSystemInit.c)
