cmake_minimum_required(VERSION 3.6)
project(AirWar__)

set(CMAKE_CXX_STANDARD 11)

#Include Allegro
INCLUDE_DIRECTORIES( usr/allegro5/include )
LINK_DIRECTORIES( usr/allegro5/include/lib )


#connect all the libraries you need
set(game_LIBS liballegro.so liballegro_image.so liballegro_audio.so liballegro_acodec.so liballegro_primitives.so liballegro_font.so liballegro_ttf.so)

set(SOURCE_FILES main.cpp Objects/Nave.cpp Objects/Nave.h Objects/Jugador.h Objects/Objects.h)
add_executable(AirWar__ ${SOURCE_FILES})

target_link_libraries(AirWar__ ${game_LIBS})





