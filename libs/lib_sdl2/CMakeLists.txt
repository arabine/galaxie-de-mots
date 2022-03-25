# ===========================================================================
# SDL2 CMAKE
# ===========================================================================

cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(SDL2  C CXX ASM)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

file(GLOB
    SDL_SRCS

    
    src/*.c
	src/audio/*.c
	src/audio/android/*.c
	src/audio/dummy/*.c
	src/audio/aaudio/*.c
	src/audio/openslES/*.c
	src/core/android/*.c
	src/cpuinfo/*.c
	src/dynapi/*.c
	src/events/*.c
	src/file/*.c
	src/haptic/*.c
	src/haptic/android/*.c
	src/hidapi/*.c
	src/hidapi/android/*.cpp
	src/joystick/*.c
	src/joystick/android/*.c
	src/joystick/hidapi/*.c
	src/joystick/virtual/*.c
	src/loadso/dlopen/*.c
	src/locale/*.c
	src/locale/android/*.c
	src/misc/*.c
	src/misc/android/*.c
	src/power/*.c
	src/power/android/*.c
	src/filesystem/android/*.c
	src/sensor/*.c
	src/sensor/android/*.c
	src/render/*.c
	src/render/*/*.c
	src/stdlib/*.c
	src/thread/*.c
	src/thread/pthread/*.c
	src/timer/*.c
	src/timer/unix/*.c
	src/video/*.c
	src/video/android/*.c
	src/video/yuv2rgb/*.c
	src/test/*.c
)

list(APPEND SDL_SRCS
	src/atomic/SDL_atomic.c
	src/atomic/SDL_spinlock.c
)

add_library(SDL2 ${SDL_SRCS})

target_include_directories(SDL2 PUBLIC include)

target_compile_definitions(SDL2 PUBLIC GL_GLEXT_PROTOTYPES)

target_link_libraries(SDL2 PUBLIC dl GLESv1_CM GLESv2 OpenSLES log android)

target_compile_options(SDL2 PUBLIC -Wall -Wextra -Wdocumentation -Wdocumentation-unknown-command -Wmissing-prototypes -Wunreachable-code-break -Wunneeded-internal-declaration -Wmissing-variable-declarations 
 -Wfloat-conversion -Wshorten-64-to-32 -Wunreachable-code-return -Wshift-sign-overflow -Wstrict-prototypes -Wkeyword-macro -Wno-unused-parameter -Wno-sign-compare)


