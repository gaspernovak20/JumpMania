cmake_minimum_required(VERSION 3.16)
project(JumpMania CXX)

set(CMAKE_CXX_STANDARD 17)

# Lokacija Homebrew (za Apple Silicon)
set(RAYLIB_INCLUDE_DIR /opt/homebrew/include)
set(RAYLIB_LIBRARY /opt/homebrew/lib/libraylib.a)

# ---- RAYLIB PATHS ----
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(game
    main.cpp
    Level.cpp
    UI.cpp  
    Anemy.cpp
    Player.cpp
    Background.cpp
    GameController.cpp
)

target_include_directories(game PRIVATE ${RAYLIB_INCLUDE_DIR})
target_link_libraries(game
    raylib
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)
