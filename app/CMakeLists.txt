# ===========================================================================
# CMAKE PRINCIPAL APPELÉ PAR GRADLE
# ===========================================================================

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(main C CXX)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

#=========================================================================================================================
# APPLI
#=========================================================================================================================
set(PROJECT_SOURCES
    ${ROOT_DIR}/src/main.cpp
    ${ROOT_DIR}/src/gfx-engine.cpp
    ${ROOT_DIR}/src/gfx-engine.h
    ${ROOT_DIR}/src/motus.h
    ${ROOT_DIR}/src/motus.cpp
    ${ROOT_DIR}/src/motus-gui.h
    ${ROOT_DIR}/src/motus-gui.cpp
)

#=========================================================================================================================
# SDL2
#=========================================================================================================================
include(FetchContent)

FetchContent_Declare(
    sdl2_project
    URL      https://www.libsdl.org/release/SDL2-2.0.20.zip
)

FetchContent_GetProperties(sdl2_project)
if(NOT sdl2_project_POPULATED)
  FetchContent_Populate(sdl2_project)

  # Copy an additional/replacement file into the populated source
  # COPY_FILE is available from CMake 3.21 only
  #file(COPY_FILE ${sdl2_project_SOURCE_DIR}/include/SDL_config_android.h ${sdl2_project_SOURCE_DIR}/include/SDL_config.h)
  execute_process(COMMAND cp ${sdl2_project_SOURCE_DIR}/include/SDL_config_android.h ${sdl2_project_SOURCE_DIR}/include/SDL_config.h)
  message("Overwrite SDL_config.h with SDL_config_android.h")

endif()

FetchContent_MakeAvailable(sdl2_project)
add_subdirectory(${sdl2_project_SOURCE_DIR} SDL2)

set(SDL2_HEADERS
    ${sdl2_project_SOURCE_DIR}/include
)


#=========================================================================================================================
# IMGUI
#=========================================================================================================================
include(../libs/lib_imgui/imgui.cmake)
list(APPEND PROJECT_SOURCES ${IMGUI_SRCS})

#=========================================================================================================================
# TARGET
#=========================================================================================================================
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
# add_dependencies(${PROJECT_NAME} sdl2_project)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_HEADERS} ../assets/db ${IMGUI_HEADERS})
target_link_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

target_link_libraries(${PROJECT_NAME} PUBLIC dl GLESv1_CM GLESv2 OpenSLES log android SDL2)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wdocumentation -Wdocumentation-unknown-command -Wmissing-prototypes -Wunreachable-code-break -Wunneeded-internal-declaration -Wmissing-variable-declarations 
 -Wfloat-conversion -Wshorten-64-to-32 -Wunreachable-code-return -Wshift-sign-overflow -Wstrict-prototypes -Wkeyword-macro -Wno-unused-parameter -Wno-sign-compare)


