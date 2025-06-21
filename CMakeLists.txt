cmake_minimum_required(VERSION 3.21)
project(subsdk CXX C ASM)

if (NOT SWITCH)
    message(FATAL_ERROR "Not targeting switch, make sure to specify _DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake")
endif()

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(TITLE_ID 0100ECD018EBE000)
set(CONFIG_TITLE_ID 0x${TITLE_ID})
add_compile_definitions(EXL_PROGRAM_ID=${CONFIG_TITLE_ID} NNSDK=1)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/module/subsdk9.json.template ${CMAKE_CURRENT_BINARY_DIR}/subsdk9.json)

include_directories(${PROJECT_SOURCE_DIR}/Include)
include_directories(${PROJECT_SOURCE_DIR}/Vendor)
include_directories(${PROJECT_SOURCE_DIR}/Vendor/exlaunch)
include_directories(${PROJECT_SOURCE_DIR}/Vendor/exlaunch/lib)

# Program source files
file(GLOB_RECURSE SOURCES_HH
    ${PROJECT_SOURCE_DIR}/Include/*.hpp
    ${PROJECT_SOURCE_DIR}/Include/*.h
)

file(GLOB_RECURSE SOURCES_CXX
    ${PROJECT_SOURCE_DIR}/Source/*.cpp
    ${PROJECT_SOURCE_DIR}/Source/*.c
)

# Exlaunch source files
file(GLOB_RECURSE EXL_SOURCES
    ${PROJECT_SOURCE_DIR}/Vendor/exlaunch/*.cpp
    ${PROJECT_SOURCE_DIR}/Vendor/exlaunch/*.c
    ${PROJECT_SOURCE_DIR}/Vendor/exlaunch/*.hpp
    ${PROJECT_SOURCE_DIR}/Vendor/exlaunch/*.h
    ${PROJECT_SOURCE_DIR}/Vendor/exlaunch/*.s
)

include(${CMAKE_SOURCE_DIR}/cmake/SwitchTools.cmake)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_executable(subsdk9 ${SOURCES_CXX} ${SOURCES_HH} ${EXL_SOURCES})
add_compile_definitions(EXL_LOAD_KIND=Module EXL_LOAD_KIND_ENUM=EXL_LOAD_KIND_MODULE)


set(SUBSDK_LD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/module/subsdk9.ld)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/module/subsdk9.specs.template ${CMAKE_CURRENT_BINARY_DIR}/subsdk9.specs)

add_nso_target_subsdk(subsdk9)
set_target_properties(subsdk9 PROPERTIES CONFIG_JSON "${CMAKE_CURRENT_BINARY_DIR}/subsdk9.json")
__generate_npdm(subsdk9)
set_target_properties(subsdk9 PROPERTIES LINK_FLAGS "-specs ${CMAKE_BINARY_DIR}/subsdk9.specs -g3 ${ARCH} -nostartfiles")

add_custom_target(subsdk9_meta DEPENDS create_npdm subsdk9_nso)