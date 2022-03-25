# ===========================================================================
# SDL2 CMAKE
# ===========================================================================

cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(main  C CXX ASM)

add_subdirectory(../libs/lib_sdl2 SDL2)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(MAIN_SRCS
    main.c
)


add_library(main ${MAIN_SRCS})

target_include_directories(main PUBLIC ../libs/lib_sdl2/SDL/include ../libs/lib_sdl2_image/SDL2_image)

#target_compile_definitions(main PUBLIC GL_GLEXT_PROTOTYPES)

target_link_libraries(main PUBLIC dl GLESv1_CM GLESv2 OpenSLES log android SDL2)

target_compile_options(main PUBLIC -Wall -Wextra -Wdocumentation -Wdocumentation-unknown-command -Wmissing-prototypes -Wunreachable-code-break -Wunneeded-internal-declaration -Wmissing-variable-declarations 
 -Wfloat-conversion -Wshorten-64-to-32 -Wunreachable-code-return -Wshift-sign-overflow -Wstrict-prototypes -Wkeyword-macro -Wno-unused-parameter -Wno-sign-compare)


