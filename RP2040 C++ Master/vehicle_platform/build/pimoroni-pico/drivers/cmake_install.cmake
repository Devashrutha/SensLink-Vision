# Install script for directory: /Users/m1/Documents/C++/pico/vehicle_platform/pimoroni-pico/drivers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/homebrew/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/analog/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/analogmux/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/esp32spi/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/ioexpander/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/ltp305/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/ltr559/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pmw3901/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/sgp30/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/st7735/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/st7789/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/msa301/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/rv3028/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/trackball/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/vl53l1x/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/is31fl3731/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/fatfs/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/sdcard/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/as7262/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/bh1745/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/bme68x/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/bmp280/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/bme280/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/button/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pid/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/plasma/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/rgbled/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/icp10125/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/scd4x/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/hub75/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/hub75_legacy/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/uc8151/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/uc8159/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/uc8151_legacy/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pwm/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/servo/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/encoder/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/motor/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/vl53l5cx/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pcf85063a/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pms5003/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/sh1107/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/st7567/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/psram_display/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/inky73/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/shiftregister/cmake_install.cmake")
  include("/Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/mlx90640/cmake_install.cmake")

endif()
