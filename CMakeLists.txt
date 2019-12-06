cmake_minimum_required(VERSION 3.1.0)

project(telegramBot)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)


set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

add_executable(telegramBot
    mainwindow.h
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    networkmanager.cpp
    networkmanager.h
)

find_package(Qt5 COMPONENTS Network REQUIRED)
get_target_property(QtNetwork_location Qt5::Network LOCATION)


target_link_libraries(telegramBot Qt5::Widgets)
target_link_libraries(telegramBot Qt5::Core)
target_link_libraries(telegramBot Qt5::Gui)
target_link_libraries(telegramBot Qt5::Network)
