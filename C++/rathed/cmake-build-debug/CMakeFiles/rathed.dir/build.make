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
CMAKE_SOURCE_DIR = /home/rafael/Documentos/Projetos/RaThEd/C++/rathed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/rathed.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rathed.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rathed.dir/flags.make

CMakeFiles/rathed.dir/main.cpp.o: CMakeFiles/rathed.dir/flags.make
CMakeFiles/rathed.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rathed.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed.dir/main.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/main.cpp

CMakeFiles/rathed.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/main.cpp > CMakeFiles/rathed.dir/main.cpp.i

CMakeFiles/rathed.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/main.cpp -o CMakeFiles/rathed.dir/main.cpp.s

CMakeFiles/rathed.dir/peer/Seed.cpp.o: CMakeFiles/rathed.dir/flags.make
CMakeFiles/rathed.dir/peer/Seed.cpp.o: ../peer/Seed.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rathed.dir/peer/Seed.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed.dir/peer/Seed.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/peer/Seed.cpp

CMakeFiles/rathed.dir/peer/Seed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed.dir/peer/Seed.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/peer/Seed.cpp > CMakeFiles/rathed.dir/peer/Seed.cpp.i

CMakeFiles/rathed.dir/peer/Seed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed.dir/peer/Seed.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/peer/Seed.cpp -o CMakeFiles/rathed.dir/peer/Seed.cpp.s

CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.o: CMakeFiles/rathed.dir/flags.make
CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.o: ../rastreador/Rastreador.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/rastreador/Rastreador.cpp

CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/rastreador/Rastreador.cpp > CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.i

CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/rastreador/Rastreador.cpp -o CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.s

CMakeFiles/rathed.dir/model/model.pb.cc.o: CMakeFiles/rathed.dir/flags.make
CMakeFiles/rathed.dir/model/model.pb.cc.o: ../model/model.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/rathed.dir/model/model.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rathed.dir/model/model.pb.cc.o -c /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/model/model.pb.cc

CMakeFiles/rathed.dir/model/model.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathed.dir/model/model.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/model/model.pb.cc > CMakeFiles/rathed.dir/model/model.pb.cc.i

CMakeFiles/rathed.dir/model/model.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathed.dir/model/model.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/model/model.pb.cc -o CMakeFiles/rathed.dir/model/model.pb.cc.s

# Object files for target rathed
rathed_OBJECTS = \
"CMakeFiles/rathed.dir/main.cpp.o" \
"CMakeFiles/rathed.dir/peer/Seed.cpp.o" \
"CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.o" \
"CMakeFiles/rathed.dir/model/model.pb.cc.o"

# External object files for target rathed
rathed_EXTERNAL_OBJECTS =

rathed: CMakeFiles/rathed.dir/main.cpp.o
rathed: CMakeFiles/rathed.dir/peer/Seed.cpp.o
rathed: CMakeFiles/rathed.dir/rastreador/Rastreador.cpp.o
rathed: CMakeFiles/rathed.dir/model/model.pb.cc.o
rathed: CMakeFiles/rathed.dir/build.make
rathed: /usr/lib/libprotobuf.so
rathed: CMakeFiles/rathed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable rathed"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rathed.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rathed.dir/build: rathed

.PHONY : CMakeFiles/rathed.dir/build

CMakeFiles/rathed.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rathed.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rathed.dir/clean

CMakeFiles/rathed.dir/depend:
	cd /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafael/Documentos/Projetos/RaThEd/C++/rathed /home/rafael/Documentos/Projetos/RaThEd/C++/rathed /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug /home/rafael/Documentos/Projetos/RaThEd/C++/rathed/cmake-build-debug/CMakeFiles/rathed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rathed.dir/depend

