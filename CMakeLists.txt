cmake_minimum_required(VERSION 3.20)

project(
  sorting-visualizer
  VERSION 0.0.1
  DESCRIPTION "Simple sorting algorithms visualizer"
  HOMEPAGE_URL "https://github.com/abidanBrito/sorting-visualizer"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 6.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)

  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET OFF)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

add_subdirectory(src)
