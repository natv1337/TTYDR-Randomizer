# Adapted from https://github.com/vbe0201/switch-cmake

if(NOT SWITCH)
    message(FATAL_ERROR "This helper can only be used when cross-compiling for the Switch")
endif()

# The directory of this file, which is needed to generate bin2s header files.
set(__SWITCH_TOOLS_DIR ${PROJECT_SOURCE_DIR}/cmake)

## A macro to find tools that come with devkitPro which are
## used for working with Switch file formats.
macro(find_tool tool)
    if(NOT ${tool})
        find_program(${tool} ${tool})
        if (${tool})
            message(STATUS "${tool} - found")
        else()
            message(WARNING "${tool} - not found")
        endif()
    endif()
endmacro()

## elf2nso
find_tool(elf2nso)

## npdmtool
find_tool(npdmtool)

## bin2s
find_tool(bin2s)

## A macro to specify the NPDM JSON configuration for a system module.
## If a path was given, it will validate it and use the file.
## If the file doesn't exist, the project root will be checked for an
## config.json that can be used.
macro(set_app_json file)
    if(EXISTS ${file})
        set(__HOMEBREW_JSON_CONFIG ${file})
    elseif(EXISTS ${PROJECT_SOURCE_DIR}/config.json)
        set(__HOMEBREW_JSON_CONFIG ${PROJECT_SOURCE_DIR}/config.json)
    else()
        # Purposefully don't set `__HOMEBREW_JSON_CONFIG` to anything.
        message(WARNING "Failed to resolve the JSON config")
    endif()
endmacro()

## Adds a binary library target with the supplied name.
## The macro takes a variable amount of binary files
## within ARGN and passes them to bin2s to create
## a library target from binary files that can be linked.
macro(__add_binary_library target)
    if(NOT ${ARGC} GREATER 1)
        message(FATAL_ERROR "No input files provided")
    endif()

    # Check if ASM is an enabled project language.
    get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
    if(NOT ENABLED_LANGUAGES MATCHES ".*ASM.*")
        message(FATAL_ERROR "To use this macro, call enable_language(ASM) first")
    endif()

    # Generate the bin2s header files.
    foreach(__file ${ARGN})
        # Extract and compose the file name for the header.
        get_filename_component(__file_name ${__file} NAME)
        string(REGEX REPLACE "^([0-9])" "_\\1" __BINARY_FILE ${__file_name})
        string(REGEX REPLACE "[-./]" "_" __BINARY_FILE ${__BINARY_FILE})

        # Generate the header.
        configure_file(${__SWITCH_TOOLS_DIR}/bin2s_header.h.in ${CMAKE_CURRENT_BINARY_DIR}/bin2s_include/${__BINARY_FILE}.h)
    endforeach()

    # Build the Assembly file.
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin2s_lib)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bin2s_lib/${target}.s
            COMMAND ${bin2s} ${ARGN} > ${CMAKE_CURRENT_BINARY_DIR}/bin2s_lib/${target}.s
            DEPENDS ${ARGN}
            WORKING_DIRECTORY ..
    )

    # Add the respective library target.
    add_library(${target} ${CMAKE_CURRENT_BINARY_DIR}/bin2s_lib/${target}.s)
    target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/bin2s_include)
endmacro()

## Embeds binary files into a given target.
## The function takes a variable amount of binary files
## within ARGN, which will be passed to bin2s to create
## a library target which will be linked against the
## `target` argument.
function(target_embed_binaries target)
    if(NOT ${ARGC} GREATER 1)
        message(FATAL_ERROR "No input files provided")
    endif()

    get_filename_component(__1st_bin_file ${ARGV1} NAME)
    __add_binary_library(__${target}_embed_${__1st_bin_file} ${ARGN})
    target_link_libraries(${target} __${target}_embed_${__1st_bin_file})
endfunction()

## Generates a .npdm file from a given target.
##
## NPDMs are found in Switch ExeFS and contain various metadata,
## related to how sysmodules get executed.
##
## It tries to extract a `CONFIG_JSON` property from the supplied
## target, which is required to acquire all the configuration
## mappings that are needed to construct the format.
function(__generate_npdm target)
    get_filename_component(target_we ${target} NAME_WE)

    # Extract and validate metadata from the target.
    get_target_property(config_json ${target} "CONFIG_JSON")

    set_app_json(${config_json})

    # The JSON configuration is crucial, we cannot continue without it.
    if(NOT __HOMEBREW_JSON_CONFIG)
        message(FATAL_ERROR "Cannot generate a NPDM file without the \"CONFIG_JSON\" property being set for the target")
    endif()

    # Build the NPDM file.
    add_custom_target(create_npdm ALL
            COMMAND ${npdmtool} ${__HOMEBREW_JSON_CONFIG} ${CMAKE_CURRENT_BINARY_DIR}/main.npdm
            DEPENDS ${target} ${__HOMEBREW_JSON_CONFIG}
            VERBATIM
    )
endfunction()

## Builds a .nso file from a given target.
##
## NSOs are the main executable format on the Switch, however
## rarely used outside of NSPs where they represent an important
## component of the ExeFS.
function(add_nso_target target)
    # Build the NSO file.
    add_custom_command(
            OUTPUT ${CMAKE_BINARY_DIR}/${target}.nso
            COMMAND ${elf2nso} $<TARGET_FILE:${target}> ${CMAKE_CURRENT_BINARY_DIR}/${target}.nso
            DEPENDS ${target}
            VERBATIM
    )

    # Add the respective NSO target and set the required linker flags for the original target.
    add_custom_target(${target}_nso ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${target}.nso)
    set_target_properties(${target} PROPERTIES LINK_FLAGS "-specs=${LIBNX}/switch.specs")
endfunction()

## Builds a .nso file from a given target (subsdk).
##
## NSOs are the main executable format on the Switch, however
## rarely used outside of NSPs where they represent an important
## component of the ExeFS.
function(add_nso_target_subsdk target)
    # Build the NSO file.
    add_custom_command(
            OUTPUT ${CMAKE_BINARY_DIR}/${target}
            COMMAND ${elf2nso} $<TARGET_FILE:${target}> ${CMAKE_CURRENT_BINARY_DIR}/${target}
            DEPENDS ${target}
            VERBATIM
    )

    # Add the respective NSO target and set the required linker flags for the original target.
    add_custom_target(${target}_nso ALL SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${target})
    set_target_properties(${target} PROPERTIES LINK_FLAGS "-specs=${LIBNX}/switch.specs")
endfunction()
