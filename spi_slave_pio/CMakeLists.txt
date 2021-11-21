add_executable (spi_slave_pio)

pico_generate_pio_header (spi_slave_pio ${CMAKE_CURRENT_LIST_DIR}/spi_slave.pio)

target_sources (spi_slave_pio PRIVATE spi_slave_pio.c)

target_link_libraries (spi_slave_pio PRIVATE pico_stdlib hardware_pio)

# Always build a RAM-only binary.
#pico_set_binary_type(spi_slave_pio no_flash)

pico_add_extra_outputs (spi_slave_pio)

example_auto_set_url (spi_slave_pio)
