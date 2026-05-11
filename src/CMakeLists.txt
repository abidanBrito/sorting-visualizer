set(SOURCE_FILES
  main.cpp
  visualizer.cpp
  algorithms/selection_sort.cpp
  algorithms/bubble_sort.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${raygui_SOURCE_DIR}/src)

target_compile_options(sorting-visualizer PRIVATE -Wno-enum-compare)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
