add_contract(pico.auth pico.attr ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.attr.cpp)

target_include_directories(pico.attr
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(pico.attr
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")


configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/pico.attr.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/pico.attr.contracts.md @ONLY )

target_compile_options( pico.attr PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
