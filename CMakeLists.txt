cmake_minimum_required (VERSION 3.1)

# Set name of the project
project(Snake)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall 
        -Wextra 
        -Wpedantic 
        -Werror=return-type 
        -Werror=parentheses 
        -Werror=vla 
        -Werror=array-bounds 
        -Wcast-qual 
        -Wmaybe-uninitialized
    )
endif()

# Windows specific config
# You can change it if you install SFML in different directory (or have different version of it)
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/lib/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ELSEIF (UNIX AND NOT APPLE)
    # Linux-specific config:
    # Linux system-installed SFML (e.g., via apt) installs CMake files into standard 
    # paths (/usr/lib/x86_64-linux-gnu/cmake/SFML or /usr/lib/cmake/SFML).
    # CMake finds it automatically—no SFML_DIR variable needed!
ENDIF()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Snake
        main.cpp
        SnakeLogic.h
        SnakeLogic.cpp
        SNSFMLView.h
        SNSFMLView.cpp
        Menu.cpp
        Menu.h
        SNSFMLController.cpp
        SNSFMLController.h)

target_link_libraries(Snake sfml-graphics)

file(COPY ${CMAKE_SOURCE_DIR}/Press_Start_2P/PressStart2P-Regular.ttf DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/fruit.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/grass.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/snake.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/wall.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/pngs/snakeHead.png DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/scores.txt DESTINATION ${CMAKE_BINARY_DIR})
