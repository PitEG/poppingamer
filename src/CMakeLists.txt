set(RNDR renderer)
set(RNDR_SRC
#${RNDR}/renderer.cpp
#${RNDR}/camera.cpp
#    ${RNDR}/sprite.cpp
   )

set(ECS_SRC
   ecs/scene.cpp
   ecs/objectpooler.cpp
#ecs/componentmanager.cpp
   )

set(SRC
    poppingamer.cpp
    ${RNDR_SRC}
    ${ECS_SRC}
   )

add_library(poppingamer SHARED ${SRC})

set(SFML_MODULES
    sfml-window
    sfml-graphics
    sfml-system
   )

target_link_libraries(poppingamer PUBLIC ${SFML_MODULES})
target_include_directories(poppingamer PUBLIC ${POPPIN_INC})
target_precompile_headers(poppingamer PUBLIC pgpch.hpp)
