cmake_minimum_required(VERSION 3.16)

project(qtTestBenchSIP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(QT_QML_GENERATE_QMLLS_INI ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick OpenGL)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(testBenchSIP
    main.cpp
)

qt_add_qml_module(testBenchSIP
    URI qtTestBenchSIP
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

configure_file("./config.json" config.json COPYONLY)

target_include_directories(testBenchSIP PRIVATE
    ${GSTREAMER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Extension
    ${CMAKE_SOURCE_DIR}/ViewModels
)

target_link_directories(testBenchSIP PRIVATE
    ${GSTREAMER_LIBRARY_DIRS}
)

target_link_libraries(testBenchSIP
    PRIVATE Qt6::Quick Qt6::OpenGL
    ${GSTREAMER_LIBRARIES}
)

include(GNUInstallDirs)
install(TARGETS testBenchSIP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(testBenchSIP PRIVATE -O0 -g)
    target_link_options(testBenchSIP PRIVATE -O0 -g)
    target_compile_definitions(testBenchSIP PRIVATE DEBUG)
else ()
    target_compile_options(testBenchSIP PRIVATE -Os)
    target_link_options(testBenchSIP PRIVATE -Os -Wl,--strip-all)
endif ()
