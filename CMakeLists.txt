cmake_minimum_required(VERSION 3.14)
project(GaugeQt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Find Qt (prefer Qt6, fall back to Qt5)
if(LINUX)
    find_package(Qt6 COMPONENTS Core Widgets WaylandClient)
endif()
if(NOT Qt6_FOUND)
    find_package(Qt6 COMPONENTS Core Widgets)
endif()
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
    set(QT_VERSION_MAJOR 5)
endif()

# Library sources
add_subdirectory(src)

# Examples
option(BUILD_EXAMPLES "Build example applications" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Install headers
install(DIRECTORY include/GaugeQt
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# CMake package config
include(CMakePackageConfigHelpers)
configure_package_config_file(
    cmake/GaugeQtConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/GaugeQtConfig.cmake
    INSTALL_DESTINATION lib/cmake/GaugeQt
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/GaugeQtConfig.cmake
    DESTINATION lib/cmake/GaugeQt
)
