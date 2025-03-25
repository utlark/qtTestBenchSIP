cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME testBenchSIP)
set(TARGET_FULL_NAME qtTestBenchSIP)

project(${TARGET_FULL_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(QT_QML_GENERATE_QMLLS_INI ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick OpenGL)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(${TARGET_NAME}
    main.cpp
)

qt_add_qml_module(${TARGET_NAME}
    URI ${TARGET_FULL_NAME}
    VERSION 1.0
    QML_FILES
        Main.qml
        VideoItem.qml
    SOURCES
        ViewModels/MainViewModel.h
        ViewModels/MainViewModel.cpp
        Extension/JsonConfig.h
        Extension/JsonConfig.cpp
        Extension/LambdaRunnable.h
)

configure_file("${CMAKE_SOURCE_DIR}/config.json" config.json COPYONLY)

target_include_directories(${TARGET_NAME} PRIVATE
    ${GSTREAMER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Extension
    ${CMAKE_SOURCE_DIR}/ViewModels
)

target_link_directories(${TARGET_NAME} PRIVATE
    ${GSTREAMER_LIBRARY_DIRS}
)

target_link_libraries(${TARGET_NAME}
    PRIVATE Qt6::Quick Qt6::OpenGL
    ${GSTREAMER_LIBRARIES}
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${TARGET_NAME} PRIVATE -O0 -g)
    target_link_options(${TARGET_NAME} PRIVATE -O0 -g)
    target_compile_definitions(${TARGET_NAME} PRIVATE DEBUG)
else ()
    target_compile_options(${TARGET_NAME} PRIVATE -Os)
    target_link_options(${TARGET_NAME} PRIVATE -Os -Wl,--strip-all)
endif ()
