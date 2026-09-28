cmake_minimum_required(VERSION 3.12)

# 1. Set Pico Board & C/C++ Standards
set(PICO_BOARD pico_w)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

# 2. Set Kernel Path
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal/FreeRTOS-KernelV10.6.2)

# 3. Import SDK & FreeRTOS CMake setup
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# 4. Declare Project (Must come after imports, before targets)
project(Lab4 C CXX ASM)

# 5. Initialize Pico SDK
pico_sdk_init()

# 6. Add Executable & Sources
add_executable(${PROJECT_NAME}
        main.cpp
        src/GPIOPin.cpp
        incl/GPIOPin.h
        incl/GPIOPin.h
        src/LED.cpp
        incl/LED.h
        src/vPrintString.cpp
        incl/vPrintString.h
        src/LedTimer.cpp
        incl/LedTimer.h
        src/TimerInactivity.cpp
        incl/TimerInactivity.h
        Uart/PicoOsUart.h
        Uart/PicoOsUart.cpp
        src/InputProcessor.cpp
        incl/InputProcessor.h
        src/Controller.cpp
        incl/Controller.h
)

# 7. Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal
        ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal/src
        ${CMAKE_CURRENT_SOURCE_DIR}/rp2040-freertos-minimal/FreeRTOS-KernelV10.6.2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Uart
        ${CMAKE_CURRENT_SOURCE_DIR}/incl
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 8. Link Libraries
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        hardware_gpio
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)