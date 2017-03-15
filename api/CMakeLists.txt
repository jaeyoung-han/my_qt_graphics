cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED
  COMPONENTS
  Core
  Widgets
  Gui
)

include_directories(
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

set(HEADERS
  graphicshexagonitem.h
  graphicsarrowitem.h
  graphicsview.h
)

set(SOURCES
  graphicshexagonitem.cpp
  graphicsarrowitem.cpp
  graphicsview.cpp
)

add_library(my_qt_graphics_api
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(my_qt_graphics_api
  ${Qt5Core_LIBRARIES}
  ${Qt5Gui_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
)
