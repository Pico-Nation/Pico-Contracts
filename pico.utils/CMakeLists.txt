add_contract(pico.utils pico.utils
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/validate_address.cpp
)

target_include_directories(pico.utils
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(pico.utils
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

target_compile_options( pico.utils PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian )
