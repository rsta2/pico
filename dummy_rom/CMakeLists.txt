add_executable(dummy_rom dummy.c)

target_link_libraries (dummy_rom PRIVATE pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(dummy_rom)

# add url via pico_set_program_url
example_auto_set_url(dummy_rom)
