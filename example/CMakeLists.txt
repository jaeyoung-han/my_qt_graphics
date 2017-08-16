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
  SectionShape.h
  shape_hexagon.h
  shape_square.h
  shape_square_thick.h
  CollimatorVerticalSectionView.h
  UmbraView.h
  mainwindow.h
)

set(SOURCES
  UmbraWidget.cpp
  DoubleSpinBoxSliderWidget.cpp
  DockCollimator.cpp
  CollimatorHorizontalSectionView.cpp
  shape_hexagon.cpp
  shape_square.cpp
  shape_square_thick.cpp
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


IF(WIN32) # Check if we are on Windows
    if(MSVC) # Check if we are using the Visual Studio compiler
        set_target_properties(example PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
        set_target_properties(example PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
    else()
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
    endif()
elseif(UNIX)
    # Nothing special required
else()
    message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
ENDIF()
