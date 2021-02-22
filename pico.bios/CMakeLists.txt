add_contract(pico.bios pico.bios ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.bios.cpp)

target_include_directories(pico.bios
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(pico.bios
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/pico.bios.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/pico.bios.contracts.md @ONLY )

target_compile_options( pico.bios PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
