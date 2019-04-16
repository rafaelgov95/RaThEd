cmake_minimum_required(VERSION 3.13)
project(rathed)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(model/model.pb.h model/model.pb.cc model/model.proto )

find_package (Threads REQUIRED)
set(CMAKE_CXX_STANDARD 14)
include_directories(peer/ rastreador/ util/ model/ template/)
add_executable(rathed main.cpp peer/Seed.cpp peer/Seed.h
        rastreador/Rastreador.cpp rastreador/Rastreador.h util/util.h model/model.pb.cc model/model.pb.h
        )

target_link_libraries(rathed Threads::Threads ${PROTOBUF_LIBRARIES})
