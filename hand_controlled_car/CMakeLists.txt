cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Project)

pico_sdk_init()

add_executable(Project)

pico_generate_pio_header(Project ${CMAKE_CURRENT_LIST_DIR}/SPIPIO.pio)

target_sources(Project PRIVATE 
    
    
    test.c
    
    
    )

target_link_libraries(Project PRIVATE 
    pico_stdlib 
    hardware_adc 
    hardware_spi
    hardware_gpio hardware_pio 
    hardware_irq  
    hardware_pwm  
    pico_bootsel_via_double_reset
    )

pico_add_extra_outputs(Project)






