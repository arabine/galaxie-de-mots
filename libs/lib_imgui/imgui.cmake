# ===========================================================================
# ImGui CMAKE
# ===========================================================================
set(IMGUI_SRCS

    ${ROOT_DIR}/libs/lib_imgui/imgui/imgui.cpp
    ${ROOT_DIR}/libs/lib_imgui/imgui/imgui_draw.cpp
    ${ROOT_DIR}/libs/lib_imgui/imgui/imgui_tables.cpp
    ${ROOT_DIR}/libs/lib_imgui/imgui/imgui_widgets.cpp
    ${ROOT_DIR}/libs/lib_imgui/imgui/backends/imgui_impl_sdl.cpp
    ${ROOT_DIR}/libs/lib_imgui/imgui/backends/imgui_impl_sdlrenderer.cpp
)

set(IMGUI_HEADERS
    ${ROOT_DIR}/libs/lib_imgui/imgui
    ${ROOT_DIR}/libs/lib_imgui/imgui/backends
)
