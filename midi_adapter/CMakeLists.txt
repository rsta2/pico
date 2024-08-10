cmake_minimum_required(VERSION 3.5)

include(${PICO_SDK_PATH}/lib/tinyusb/hw/bsp/family_support.cmake)

# gets PROJECT name for the example (e.g. <BOARD>-<DIR_NAME>)
family_get_project_name(PROJECT ${CMAKE_CURRENT_LIST_DIR})

project(${PROJECT})

# Checks this example is valid for the family and initializes the project
family_initialize_project(${PROJECT} ${CMAKE_CURRENT_LIST_DIR})

add_executable(${PROJECT})

# Example source
target_sources(${PROJECT} PRIVATE
        main.c
        usb_descriptors.c
        )

# Example include
target_include_directories(${PROJECT} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.0.0")
        # Configure compilation flags and libraries for the example... see the corresponding function
        # in hw/bsp/FAMILY/family.cmake for details.
        family_configure_device_example(${PROJECT})
else()
        # In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
        # for TinyUSB device support and tinyusb_board for the additional board support library used by the example
        target_link_libraries(${PROJECT} PRIVATE
                pico_stdlib
                tinyusb_device
                tinyusb_board
                )
endif()

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT})

example_auto_set_url (${PROJECT})
