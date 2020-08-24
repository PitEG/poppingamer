cmake_minimum_required(VERSION 3.17)
project(PoppinGamer)

set(POPPIN_INC ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE FILEPATH "Popping Gamer include dir")

find_package(SFML 2.5 
    COMPONENTS 
    graphics audio 
    REQUIRED )


add_subdirectory(src)
add_subdirectory(sandbox)
