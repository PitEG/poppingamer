add_executable(main main.cpp) 
target_link_libraries(main poppingamer)

add_executable(test_objectpool test_objectpool)
target_link_libraries(test_objectpool poppingamer)
