# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Jaeyoung/Workspace/my_qt_graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Jaeyoung/Workspace/my_qt_graphics/build

# Include any dependencies generated for this target.
include example/CMakeFiles/example.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/example.dir/flags.make

example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o: example/CMakeFiles/example.dir/flags.make
example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o: ../example/CollimatorSectionalView.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jaeyoung/Workspace/my_qt_graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/CollimatorSectionalView.cpp.o -c /Users/Jaeyoung/Workspace/my_qt_graphics/example/CollimatorSectionalView.cpp

example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/CollimatorSectionalView.cpp.i"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jaeyoung/Workspace/my_qt_graphics/example/CollimatorSectionalView.cpp > CMakeFiles/example.dir/CollimatorSectionalView.cpp.i

example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/CollimatorSectionalView.cpp.s"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jaeyoung/Workspace/my_qt_graphics/example/CollimatorSectionalView.cpp -o CMakeFiles/example.dir/CollimatorSectionalView.cpp.s

example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.requires:

.PHONY : example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.requires

example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.provides: example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.requires
	$(MAKE) -f example/CMakeFiles/example.dir/build.make example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.provides.build
.PHONY : example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.provides

example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.provides.build: example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o


example/CMakeFiles/example.dir/mainwindow.cpp.o: example/CMakeFiles/example.dir/flags.make
example/CMakeFiles/example.dir/mainwindow.cpp.o: ../example/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jaeyoung/Workspace/my_qt_graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object example/CMakeFiles/example.dir/mainwindow.cpp.o"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/mainwindow.cpp.o -c /Users/Jaeyoung/Workspace/my_qt_graphics/example/mainwindow.cpp

example/CMakeFiles/example.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/mainwindow.cpp.i"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jaeyoung/Workspace/my_qt_graphics/example/mainwindow.cpp > CMakeFiles/example.dir/mainwindow.cpp.i

example/CMakeFiles/example.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/mainwindow.cpp.s"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jaeyoung/Workspace/my_qt_graphics/example/mainwindow.cpp -o CMakeFiles/example.dir/mainwindow.cpp.s

example/CMakeFiles/example.dir/mainwindow.cpp.o.requires:

.PHONY : example/CMakeFiles/example.dir/mainwindow.cpp.o.requires

example/CMakeFiles/example.dir/mainwindow.cpp.o.provides: example/CMakeFiles/example.dir/mainwindow.cpp.o.requires
	$(MAKE) -f example/CMakeFiles/example.dir/build.make example/CMakeFiles/example.dir/mainwindow.cpp.o.provides.build
.PHONY : example/CMakeFiles/example.dir/mainwindow.cpp.o.provides

example/CMakeFiles/example.dir/mainwindow.cpp.o.provides.build: example/CMakeFiles/example.dir/mainwindow.cpp.o


example/CMakeFiles/example.dir/main.cpp.o: example/CMakeFiles/example.dir/flags.make
example/CMakeFiles/example.dir/main.cpp.o: ../example/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jaeyoung/Workspace/my_qt_graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object example/CMakeFiles/example.dir/main.cpp.o"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/main.cpp.o -c /Users/Jaeyoung/Workspace/my_qt_graphics/example/main.cpp

example/CMakeFiles/example.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/main.cpp.i"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jaeyoung/Workspace/my_qt_graphics/example/main.cpp > CMakeFiles/example.dir/main.cpp.i

example/CMakeFiles/example.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/main.cpp.s"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jaeyoung/Workspace/my_qt_graphics/example/main.cpp -o CMakeFiles/example.dir/main.cpp.s

example/CMakeFiles/example.dir/main.cpp.o.requires:

.PHONY : example/CMakeFiles/example.dir/main.cpp.o.requires

example/CMakeFiles/example.dir/main.cpp.o.provides: example/CMakeFiles/example.dir/main.cpp.o.requires
	$(MAKE) -f example/CMakeFiles/example.dir/build.make example/CMakeFiles/example.dir/main.cpp.o.provides.build
.PHONY : example/CMakeFiles/example.dir/main.cpp.o.provides

example/CMakeFiles/example.dir/main.cpp.o.provides.build: example/CMakeFiles/example.dir/main.cpp.o


example/CMakeFiles/example.dir/example_automoc.cpp.o: example/CMakeFiles/example.dir/flags.make
example/CMakeFiles/example.dir/example_automoc.cpp.o: example/example_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jaeyoung/Workspace/my_qt_graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object example/CMakeFiles/example.dir/example_automoc.cpp.o"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/example_automoc.cpp.o -c /Users/Jaeyoung/Workspace/my_qt_graphics/build/example/example_automoc.cpp

example/CMakeFiles/example.dir/example_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/example_automoc.cpp.i"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jaeyoung/Workspace/my_qt_graphics/build/example/example_automoc.cpp > CMakeFiles/example.dir/example_automoc.cpp.i

example/CMakeFiles/example.dir/example_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/example_automoc.cpp.s"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jaeyoung/Workspace/my_qt_graphics/build/example/example_automoc.cpp -o CMakeFiles/example.dir/example_automoc.cpp.s

example/CMakeFiles/example.dir/example_automoc.cpp.o.requires:

.PHONY : example/CMakeFiles/example.dir/example_automoc.cpp.o.requires

example/CMakeFiles/example.dir/example_automoc.cpp.o.provides: example/CMakeFiles/example.dir/example_automoc.cpp.o.requires
	$(MAKE) -f example/CMakeFiles/example.dir/build.make example/CMakeFiles/example.dir/example_automoc.cpp.o.provides.build
.PHONY : example/CMakeFiles/example.dir/example_automoc.cpp.o.provides

example/CMakeFiles/example.dir/example_automoc.cpp.o.provides.build: example/CMakeFiles/example.dir/example_automoc.cpp.o


# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/CollimatorSectionalView.cpp.o" \
"CMakeFiles/example.dir/mainwindow.cpp.o" \
"CMakeFiles/example.dir/main.cpp.o" \
"CMakeFiles/example.dir/example_automoc.cpp.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

bin/example: example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o
bin/example: example/CMakeFiles/example.dir/mainwindow.cpp.o
bin/example: example/CMakeFiles/example.dir/main.cpp.o
bin/example: example/CMakeFiles/example.dir/example_automoc.cpp.o
bin/example: example/CMakeFiles/example.dir/build.make
bin/example: lib/libmy_qt_graphics_api.a
bin/example: /usr/local/opt/qt5/lib/QtWidgets.framework/QtWidgets
bin/example: /usr/local/opt/qt5/lib/QtGui.framework/QtGui
bin/example: /usr/local/opt/qt5/lib/QtCore.framework/QtCore
bin/example: example/CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Jaeyoung/Workspace/my_qt_graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../bin/example"
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/example.dir/build: bin/example

.PHONY : example/CMakeFiles/example.dir/build

example/CMakeFiles/example.dir/requires: example/CMakeFiles/example.dir/CollimatorSectionalView.cpp.o.requires
example/CMakeFiles/example.dir/requires: example/CMakeFiles/example.dir/mainwindow.cpp.o.requires
example/CMakeFiles/example.dir/requires: example/CMakeFiles/example.dir/main.cpp.o.requires
example/CMakeFiles/example.dir/requires: example/CMakeFiles/example.dir/example_automoc.cpp.o.requires

.PHONY : example/CMakeFiles/example.dir/requires

example/CMakeFiles/example.dir/clean:
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build/example && $(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/example.dir/clean

example/CMakeFiles/example.dir/depend:
	cd /Users/Jaeyoung/Workspace/my_qt_graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Jaeyoung/Workspace/my_qt_graphics /Users/Jaeyoung/Workspace/my_qt_graphics/example /Users/Jaeyoung/Workspace/my_qt_graphics/build /Users/Jaeyoung/Workspace/my_qt_graphics/build/example /Users/Jaeyoung/Workspace/my_qt_graphics/build/example/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/example.dir/depend

