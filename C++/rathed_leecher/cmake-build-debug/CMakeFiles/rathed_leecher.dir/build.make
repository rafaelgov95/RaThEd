# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/rathed_leecher.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rathed_leecher.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rathed_leecher.dir/flags.make

rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: ../resources/buttons.qrc
rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: CMakeFiles/rathed_leecher_autogen.dir/RCCbuttonsInfo.cmake
rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: ../resources/buttons/stop.png
rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: ../resources/buttons/play.png
rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: ../resources/buttons/plus.png
rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: ../resources/buttons/skip-previous.png
rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: ../resources/buttons/pause.png
rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp: ../resources/buttons/skip-next.png
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for resources/buttons.qrc"
	/opt/clion/bin/cmake/linux/bin/cmake -E cmake_autorcc /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles/rathed_leecher_autogen.dir/RCCbuttonsInfo.cmake Debug

CMakeFiles/rathed_leecher.dir/main.cpp.o: CMakeFiles/rathed_leecher.dir/flags.make
CMakeFiles/rathed_leecher.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rathed_leecher.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed_leecher.dir/main.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/main.cpp

CMakeFiles/rathed_leecher.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed_leecher.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/main.cpp > CMakeFiles/rathed_leecher.dir/main.cpp.i

CMakeFiles/rathed_leecher.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed_leecher.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/main.cpp -o CMakeFiles/rathed_leecher.dir/main.cpp.s

CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.o: CMakeFiles/rathed_leecher.dir/flags.make
CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.o: ../peer/Leecher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/peer/Leecher.cpp

CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/peer/Leecher.cpp > CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.i

CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/peer/Leecher.cpp -o CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.s

CMakeFiles/rathed_leecher.dir/model/model.pb.cc.o: CMakeFiles/rathed_leecher.dir/flags.make
CMakeFiles/rathed_leecher.dir/model/model.pb.cc.o: ../model/model.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/rathed_leecher.dir/model/model.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed_leecher.dir/model/model.pb.cc.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/model/model.pb.cc

CMakeFiles/rathed_leecher.dir/model/model.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed_leecher.dir/model/model.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/model/model.pb.cc > CMakeFiles/rathed_leecher.dir/model/model.pb.cc.i

CMakeFiles/rathed_leecher.dir/model/model.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed_leecher.dir/model/model.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/model/model.pb.cc -o CMakeFiles/rathed_leecher.dir/model/model.pb.cc.s

CMakeFiles/rathed_leecher.dir/template/widget.cpp.o: CMakeFiles/rathed_leecher.dir/flags.make
CMakeFiles/rathed_leecher.dir/template/widget.cpp.o: ../template/widget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/rathed_leecher.dir/template/widget.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed_leecher.dir/template/widget.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/template/widget.cpp

CMakeFiles/rathed_leecher.dir/template/widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed_leecher.dir/template/widget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/template/widget.cpp > CMakeFiles/rathed_leecher.dir/template/widget.cpp.i

CMakeFiles/rathed_leecher.dir/template/widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed_leecher.dir/template/widget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/template/widget.cpp -o CMakeFiles/rathed_leecher.dir/template/widget.cpp.s

CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.o: CMakeFiles/rathed_leecher.dir/flags.make
CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.o: rathed_leecher_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/rathed_leecher_autogen/mocs_compilation.cpp

CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/rathed_leecher_autogen/mocs_compilation.cpp > CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.i

CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/rathed_leecher_autogen/mocs_compilation.cpp -o CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.s

CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.o: CMakeFiles/rathed_leecher.dir/flags.make
CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.o: rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp

CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp > CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.i

CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp -o CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.s

# Object files for target rathed_leecher
rathed_leecher_OBJECTS = \
"CMakeFiles/rathed_leecher.dir/main.cpp.o" \
"CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.o" \
"CMakeFiles/rathed_leecher.dir/model/model.pb.cc.o" \
"CMakeFiles/rathed_leecher.dir/template/widget.cpp.o" \
"CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.o"

# External object files for target rathed_leecher
rathed_leecher_EXTERNAL_OBJECTS =

rathed_leecher: CMakeFiles/rathed_leecher.dir/main.cpp.o
rathed_leecher: CMakeFiles/rathed_leecher.dir/peer/Leecher.cpp.o
rathed_leecher: CMakeFiles/rathed_leecher.dir/model/model.pb.cc.o
rathed_leecher: CMakeFiles/rathed_leecher.dir/template/widget.cpp.o
rathed_leecher: CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/mocs_compilation.cpp.o
rathed_leecher: CMakeFiles/rathed_leecher.dir/rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp.o
rathed_leecher: CMakeFiles/rathed_leecher.dir/build.make
rathed_leecher: /usr/lib/libQt5Quick.so.5.12.2
rathed_leecher: /usr/lib/libQt5MultimediaWidgets.so.5.12.2
rathed_leecher: /usr/lib/libprotobuf.so
rathed_leecher: /usr/lib/libQt5Qml.so.5.12.2
rathed_leecher: /usr/lib/libQt5Widgets.so.5.12.2
rathed_leecher: /usr/lib/libQt5Multimedia.so.5.12.2
rathed_leecher: /usr/lib/libQt5Network.so.5.12.2
rathed_leecher: /usr/lib/libQt5Gui.so.5.12.2
rathed_leecher: /usr/lib/libQt5Core.so.5.12.2
rathed_leecher: CMakeFiles/rathed_leecher.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable rathed_leecher"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rathed_leecher.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rathed_leecher.dir/build: rathed_leecher

.PHONY : CMakeFiles/rathed_leecher.dir/build

CMakeFiles/rathed_leecher.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rathed_leecher.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rathed_leecher.dir/clean

CMakeFiles/rathed_leecher.dir/depend: rathed_leecher_autogen/3YJK5W5UP7/qrc_buttons.cpp
	cd /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug /home/rafael/Documentos/Projetos/RaThEd/C++/rathed_leecher/cmake-build-debug/CMakeFiles/rathed_leecher.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rathed_leecher.dir/depend

