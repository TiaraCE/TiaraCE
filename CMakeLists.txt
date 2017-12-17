cmake_minimum_required( VERSION 3.5 )

project(tiarace)

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
# Compiler Configuration
###############################################################################

# Checks if the compiler is 32-bit
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	message(FATAL_ERROR "TiaraCE ONLY supports 64-bit, please use a 64-bit compiler. Aborting")
endif()

set(unix_shared_compiler_flags "-std=c++14 -Werror -pedantic")

if(UNIX) #Linux, OS X, CygWin
	message(STATUS "Compiling on " ${CMAKE_SYSTEM})
	if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
		message(STATUS "Compiler is GCC")
		set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${unix_shared_compiler_flags})
	elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
		message(STATUS "Compiler is Clang")
		set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${unix_shared_compiler_flags})
	else() #Unsupported compiler?
		message(FATAL_ERROR "Compiler is " ${CMAKE_CXX_COMPILER_ID} " which is unsupported, please submit a new issue on github!")
	endif()
elseif(WIN32)
	message(STATUS "Compiling on " ${CMAKE_SYSTEM})
	if(MSVC)
		message(STATUS "Compiler is MSVC")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nologo -Gm- -EHa- -Od -Oi -WX -wd4100 -wd4189")
		add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	elseif(MINGW)
		message(STATUS "Compiler is MinGW")
		set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${unix_shared_compiler_flags})
	elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
		message(STATUS "Compiler is Clang")
		set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${unix_shared_compiler_flags})
	else() #Unsupported compiler?
		message(FATAL_ERROR "Compiler is " ${CMAKE_CXX_COMPILER_ID} " which is unsupported, please submit a new issue on github!")
	endif()
else() #Unsupported platform?
	message(FATAL_ERROR "Compiling on " ${CMAKE_SYSTEM} " which is unsupported, please submit a new issue on github!")
endif()

###############################################################################
# 3rd Party Libraries
###############################################################################
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIRS})
	message(STATUS "SDL2 Include Dir: " ${SDL2_INCLUDE_DIRS})
endif()

###############################################################################
# Source Directory
###############################################################################
add_subdirectory(src)
