# ===========================================================================
# ImGui CMAKE
# ===========================================================================

cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(imgui  C CXX)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(IMGUI_SRCS

    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_sdl.cpp
    imgui/backends/imgui_impl_sdlrenderer.cpp
)

add_library(imgui ${IMGUI_SRCS})

target_include_directories(imgui PUBLIC imgui imgui/backends ../lib_sdl2/include)

target_link_libraries(imgui PUBLIC dl GLESv1_CM GLESv2 OpenSLES log android SDL2)

