add_executable(test_style
  test_main.cc
  test_tears_in_rain.cc
)

target_include_directories(test_style PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(test_style
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

target_link_libraries(test_style PRIVATE style)
