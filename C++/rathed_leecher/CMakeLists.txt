cmake_minimum_required(VERSION 3.13)
project(rathed_leecher)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Quick CONFIG REQUIRED)
find_package (Qt5Multimedia CONFIG REQUIRED)
find_package (Qt5Network CONFIG REQUIRED)
find_package (Qt5Gui CONFIG REQUIRED)
find_package(Qt5MultimediaWidgets CONFIG REQUIRED)


find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(model/model.pb.h model/model.pb.cc model/model.proto )

find_package (Threads REQUIRED)
set(CMAKE_CXX_STANDARD 14)

include_directories(peer/ util/ model/ template/ resources/ rede/)


qt5_wrap_ui(UI_HEADERS ${UI})

add_executable(rathed_leecher main.cpp peer/Leecher.cpp peer/Leecher.h
        util/util.h model/model.pb.cc model/model.pb.h template/widget.cpp template/widget.h template/ui_widget.h resources/buttons.qrc rede/CamadaDeRede.h rede/CamadaDeRede.cpp util/PrioritFIFO.cpp  util/PrioritFIFO.h
        util/PrioritDataGramaFIFO.cpp util/PrioritDataGramaFIFO.h util/Temporizador.cpp util/Temporizador.h
        )
set_target_properties(rathed_leecher PROPERTIES AUTOMOC TRUE)

target_link_libraries(rathed_leecher Qt5::Core)
target_link_libraries(rathed_leecher Qt5::Widgets)
target_link_libraries(rathed_leecher Qt5::Quick)
target_link_libraries(rathed_leecher Qt5::Multimedia)
target_link_libraries(rathed_leecher Qt5::Network)
target_link_libraries(rathed_leecher Qt5::Gui)
target_link_libraries(rathed_leecher Qt5::MultimediaWidgets)
target_link_libraries(rathed_leecher Threads::Threads ${PROTOBUF_LIBRARIES})
