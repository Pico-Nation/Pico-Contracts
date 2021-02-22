add_contract(pico.oracle pico.oracle ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.oracle.cpp)

target_include_directories(pico.oracle
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.system/include)

set_target_properties(pico.oracle
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

target_compile_options( pico.oracle PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian )
