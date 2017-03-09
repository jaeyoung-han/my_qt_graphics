cmake_minimum_required (VERSION 2.8.11)

project(my_qt_graphics)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 REQUIRED
  COMPONENTS
  Core
  Widgets
  Gui
  )
  
