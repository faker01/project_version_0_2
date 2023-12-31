cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.

set(PROJECT_NAME Project)		 # имя проекта
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_definitions(-DSFML_STATIC)		 # дефайны

include_directories("ext/SFML/include/")	# добавляем директории
include_directories("inc/")
link_directories("ext/SFML/lib/")
add_executable("${PROJECT_NAME}" main.cpp
				func/game.h
                func/change_directory.h 
                func/logger.h)
target_link_libraries("${PROJECT_NAME}" sfml-graphics-s-d
        sfml-window-s-d
        sfml-system-s-d
        opengl32
        freetype
        winmm
        gdi32
        sfml-audio-s-d
        openal32
        flac
        vorbisenc
        vorbisfile
        vorbis
        ogg)
file(COPY "textures" DESTINATION "/")
file(COPY "Audio" DESTINATION "/")
file(COPY "openal32.dll" DESTINATION "/")
file(COPY "logs" DESTINATION "/")
