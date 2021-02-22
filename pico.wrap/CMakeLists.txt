add_contract(pico.wrap pico.wrap ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.wrap.cpp)

target_include_directories(pico.wrap
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(pico.wrap
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/pico.wrap.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/pico.wrap.contracts.md @ONLY )

target_compile_options( pico.wrap PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
