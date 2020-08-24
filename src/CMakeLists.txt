set(SRC
    poppingamer.cpp
   )

add_library(poppingamer SHARED ${SRC})

set(SFML_MODULES
    sfml-window
    sfml-graphics
   )

target_link_libraries(poppingamer PRIVATE ${SFML_MODULES})
target_include_directories(poppingamer PUBLIC ${POPPIN_INC})
target_precompile_headers(poppingamer PUBLIC pgpch.hpp)
