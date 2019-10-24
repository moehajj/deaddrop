add_library (util util.c)
target_include_directories (util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library (util_duplex util.c)
target_include_directories (util_duplex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(util_duplex PRIVATE DUPLEX_MODE=1)
