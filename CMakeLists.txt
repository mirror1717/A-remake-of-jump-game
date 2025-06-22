cmake_minimum_required(VERSION 3.26)
project(jumpjump C)

set(CMAKE_C_STANDARD 99)

include_directories("F:/envs/SDL2/SDL2/mingw(CLion+VSC)/SDL2-2.26.0-allinone/x86_64-w64-mingw32/include")
link_directories("F:/envs/SDL2/SDL2/mingw(CLion+VSC)/SDL2-2.26.0-allinone/x86_64-w64-mingw32/lib")
add_subdirectory(src)
include_directories(include)
target_link_libraries(jumpjump PRIVATE
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)