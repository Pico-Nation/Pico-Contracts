add_contract(pico.msig pico.msig ${CMAKE_CURRENT_SOURCE_DIR}/src/pico.msig.cpp)

target_include_directories(pico.msig
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(pico.msig
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/pico.msig.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/pico.msig.contracts.md @ONLY )

target_compile_options( pico.msig PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
