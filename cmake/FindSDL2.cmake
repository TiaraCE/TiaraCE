#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# CMake - Cross Platform Makefile Generator
# Copyright 2000-2014 Kitware, Inc.
# Copyright 2000-2011 Insight Software Consortium
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# * Neither the names of Kitware, Inc., the Insight Software Consortium,
# nor the names of their contributors may be used to endorse or promote
# products derived from this software without specific prior written
# permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
# License text for the above reference.)
#
# SDL2_FOUND - System has SDL2
# SDL2_INCLUDE_DIRS - The SDL2 include directories
# SDL2_LIBRARIES - The libraries needed to use SDL2

find_path(SDL2_INCLUDE_DIR SDL2/SDL.h
	HINTS
	${CMAKE_SOURCE_DIR}
	$ENV{SDL2_DIR}
	PATH_SUFFIXES 
	include/SDL2 
	include
	SDL2
	PATHS
	/usr/local
	/usr
	/opt
)

# 64 bit
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_LIBRARY SDL2
		HINTS
		${CMAKE_SOURCE_DIR}
		$ENV{SDL2_DIR}
		PATH_SUFFIXES 
		lib64 
		lib
		lib/x64
		PATHS
		/opt
	)
# 32 bit
else(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_LIBRARY SDL2
		HINTS
		${CMAKE_SOURCE_DIR}
		$ENV{SDL2_DIR}
		PATH_SUFFIXES 
		lib
		lib/x86
		PATHS
		/opt
	)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

# 64 bit
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_MAIN_LIBRARY SDL2main
		HINTS
		${CMAKE_SOURCE_DIR}
		$ENV{SDL2_DIR}
		PATH_SUFFIXES 
		lib64
		lib
		lib/x64
		PATHS
		/opt
		)
# 32 bit
else(CMAKE_SIZEOF_VOID_P EQUAL 8)
	FIND_LIBRARY(SDL2_MAIN_LIBRARY SDL2main
		HINTS
		${CMAKE_SOURCE_DIR}
		$ENV{SDL2_DIR}
		PATH_SUFFIXES 
		lib
		lib/x86
		PATHS
		/opt
		)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_LIBRARY SDL2_INCLUDE_DIR)

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY SDL2_MAIN_LIBRARY)

set(SDL2_LIBRARIES ${SDL2_LIBRARY} ${SDL2_MAIN_LIBRARY})
set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
