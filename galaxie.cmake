set(PROJECT_SOURCES
    ${ROOT_DIR}/src/main.cpp

    # ----------------  GFX ENGINE  ----------------
    ${ROOT_DIR}/src/gfx-engine/stb_image.h
    ${ROOT_DIR}/src/gfx-engine/SDL2_gfxPrimitives.c
    ${ROOT_DIR}/src/gfx-engine/SDL2_gfxPrimitives.h
    ${ROOT_DIR}/src/gfx-engine/SDL2_rotozoom.c
    ${ROOT_DIR}/src/gfx-engine/SDL2_rotozoom.h
    ${ROOT_DIR}/src/gfx-engine/gfx-engine.cpp
    ${ROOT_DIR}/src/gfx-engine/gfx-engine.h
    ${ROOT_DIR}/src/gfx-engine/entity.h
    ${ROOT_DIR}/src/gfx-engine/entity.cpp
    ${ROOT_DIR}/src/gfx-engine/image.h
    ${ROOT_DIR}/src/gfx-engine/image.cpp
    ${ROOT_DIR}/src/gfx-engine/common.h
    ${ROOT_DIR}/src/gfx-engine/common.cpp

    # ----------------  MOTUS GAME  ----------------
    ${ROOT_DIR}/src/activities/motus/motus.h
    ${ROOT_DIR}/src/activities/motus/motus.cpp
    ${ROOT_DIR}/src/activities/motus/motus-gui.h
    ${ROOT_DIR}/src/activities/motus/motus-gui.cpp
    ${ROOT_DIR}/src/activities/motus/motus-grid.h
    ${ROOT_DIR}/src/activities/motus/motus-grid.cpp

    # ----------------  TOPPING GAME  ----------------
    ${ROOT_DIR}/src/activities/topping/topping-scene.h
    ${ROOT_DIR}/src/activities/topping/topping-scene.cpp

    # ----------------  HOME SCENE  ----------------
    ${ROOT_DIR}/src/home-scene.h
    ${ROOT_DIR}/src/home-scene.cpp

    # ----------------  COMMON  ----------------
    ${ROOT_DIR}/src/letter.h
    ${ROOT_DIR}/src/letter.cpp
    ${ROOT_DIR}/src/keyboard.h
    ${ROOT_DIR}/src/keyboard.cpp
    ${ROOT_DIR}/src/database.cpp
    ${ROOT_DIR}/src/database.h
    ${ROOT_DIR}/src/sqlite3.c
    ${ROOT_DIR}/src/sqlite3.h
    ${ROOT_DIR}/src/application.h
    ${ROOT_DIR}/src/application.cpp
    ${ROOT_DIR}/src/i_application.h
)

set(GALAXIE_INCLUDES
    ${ROOT_DIR}/src
    ${ROOT_DIR}/assets/db
    ${ROOT_DIR}/src/gfx-engine
    ${ROOT_DIR}/libs/nanosvg/src
    ${ROOT_DIR}/src/activities/motus
)
 
