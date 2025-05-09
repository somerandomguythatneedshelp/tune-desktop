cmake_minimum_required(VERSION 3.19)
project(Tune LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Multimedia Svg)

qt_standard_project_setup()

qt_add_executable(Tune
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    sidebar.h sidebar.cpp
    topbar.h topbar.cpp
    contentarea.h contentarea.cpp
    playbackbar.h playbackbar.cpp
    titlebar.h titlebar.cpp
)

target_link_libraries(Tune
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Gui
        Qt6::Multimedia
        Qt6::Svg
)

include(GNUInstallDirs)

install(TARGETS Tune
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Tune
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
