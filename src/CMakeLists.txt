set(SRC
    poppingamer.cpp
   )

add_library(poppingamer SHARED ${SRC})
target_include_directories(poppingamer PUBLIC ${POPPIN_INC})
#target_precompile_headers(poppingamer PUBLIC pgpch.hpp)
