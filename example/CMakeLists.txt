cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED
  COMPONENTS
  Core
  Widgets
  Gui
)

include_directories(
  ../api
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

set(HEADERS
  data_types.h
  qUtil.h
  UmbraWidget.h
  DoubleSpinBoxSliderWidget.h
  DockCollimator.h
  CollimatorHorizontalSectionView.h
  CollimatorVerticalSectionView.h
  UmbraView.h
  mainwindow.h
)

set(SOURCES
  UmbraWidget.cpp
  DoubleSpinBoxSliderWidget.cpp
  DockCollimator.cpp
  CollimatorHorizontalSectionView.cpp
  CollimatorVerticalSectionView.cpp
  UmbraView.cpp
  mainwindow.cpp
  main.cpp
)

add_executable(example
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(example
  my_qt_graphics_api
  ${Qt5Core_LIBRARIES}
  ${Qt5Gui_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
)
