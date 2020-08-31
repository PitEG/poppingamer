cmake_minimum_required(VERSION 3.17)
project(PoppinGamer)

set(POPPIN_INC ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE FILEPATH "Popping Gamer include dir")

find_package(SFML 2.5.1 COMPONENTS graphics audio system REQUIRED )

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(src)
add_subdirectory(sandbox)
