add_contract(pico.swap pico.swap
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.swap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/system_info.cpp
)

target_include_directories(pico.swap
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.system/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.utils/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../pico.token/include
)

set_target_properties(pico.swap
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/pico.swap.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/pico.swap.contracts.md @ONLY )

target_compile_options( pico.swap PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
