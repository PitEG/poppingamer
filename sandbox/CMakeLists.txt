add_executable(test_cm test_cm.cpp)
target_link_libraries(test_cm PUBLIC poppingamer)

add_executable(test_rend test_rend.cpp)
target_link_libraries(test_rend PUBLIC poppingamer)

add_executable(test_view test_view.cpp)
target_link_libraries(test_view PUBLIC sfml-window sfml-graphics)
