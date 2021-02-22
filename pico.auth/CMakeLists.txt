add_contract(pico.auth pico.auth
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.auth.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.attr/src/pico.attr.cpp
)

target_include_directories(pico.auth
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.system/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.oracle/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.swap/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.token/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.attr/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.swap/src
)

set_target_properties(pico.auth
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

target_compile_options( pico.auth PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian )
