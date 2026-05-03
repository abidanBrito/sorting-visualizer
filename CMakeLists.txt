cmake_minimum_required(VERSION 3.16)

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

add_subdirectory(src)
