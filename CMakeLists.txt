cmake_minimum_required( VERSION 3.5 )

project(TiaraCE-Dedicated)

###############################################################################
# Project Build Settings
###############################################################################
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

###############################################################################
# Directory Settings
###############################################################################
set(bin_output_dir "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_output_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${bin_output_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${bin_output_dir})

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${bin_output_dir})
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${bin_output_dir})
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${bin_output_dir})
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

###############################################################################
# 3rd Party Libraries
###############################################################################
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIRS})
	message(STATUS "SDL2 Include Dir: " ${SDL2_INCLUDE_DIRS})
endif()

###############################################################################
# Source Files
###############################################################################
set(src_files
    "src/eventLoop.cpp"
    "src/eventLoop.h"
    "src/gameLoop.cpp"
    "src/gameLoop.h"
    "src/main.cpp"
    "src/memoryManager.cpp"
    "src/memoryManager.h"
)

###############################################################################
# Library Files
###############################################################################
set(lib_files
    ${SDL2_LIBRARIES}
)

###############################################################################
# Compiler Flags
###############################################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nologo -Gm- -EHa- -Od -Oi -WX -W4 -wd4100 -wd4189")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -pedantic")
endif()

###############################################################################
# Compiler
###############################################################################
add_executable(${PROJECT_NAME} ${src_files})

###############################################################################
# Linker
###############################################################################
target_link_libraries(${PROJECT_NAME} ${lib_files})
