add_contract(pico.token pico.token ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.token.cpp)

target_include_directories(pico.token
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(pico.token
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/pico.token.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/pico.token.contracts.md @ONLY )

target_compile_options( pico.token PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
