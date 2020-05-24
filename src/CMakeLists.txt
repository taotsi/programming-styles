add_library(style STATIC
  monolithic.cc
)

target_include_directories(style PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(style PRIVATE
  -Wall
  -Wextra
  -pedantic
  -Werror
  -pthread
)

set_target_properties(style
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)


add_executable(style_app main.cc)

target_include_directories(style_app PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(style_app PRIVATE
  -Wall
  -Wextra
  -pedantic
  -Werror
  -pthread
)

target_link_libraries(style_app PRIVATE style)

set_target_properties(style_app
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
