add_executable(dummy_flash dummy.c)

target_link_libraries (dummy_flash PRIVATE pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(dummy_flash)

# add url via pico_set_program_url
example_auto_set_url(dummy_flash)
