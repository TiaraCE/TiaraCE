project(core)

###############################################################################
# Source Files
###############################################################################
set(core_src_files
"event_loop.cpp"
"event_loop.h"
"game_loop.cpp"
"game_loop.h"
"memory_manager.cpp"
"memory_manager.h"
)

set(server_src_files
"server.cpp"
)
###############################################################################
# Library Files
###############################################################################
set(lib_files
${SDL2_LIBRARIES}
)

###############################################################################
# Compiler
###############################################################################
add_library(core SHARED ${core_src_files})
add_executable(tiarace-dedicated ${server_src_files})

###############################################################################
# Linker
###############################################################################
target_link_libraries(core ${lib_files})
target_link_libraries(tiarace-dedicated core)
