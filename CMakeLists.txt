add_library(INA260-Pico INTERFACE)

target_sources(INA260-Pico INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/INA260.cpp
)

target_link_libraries(INA260-Pico INTERFACE
    pico_stdlib
    hardware_i2c
)