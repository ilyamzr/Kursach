cmake_minimum_required(VERSION 3.26)
project(untitled51)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.2\\mingw_64")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(untitled51 source/main.cpp
        source/mainwindow.cpp
        header/mainwindow.h
        source/mainwindow.ui
        source/operationsFunc.cpp
        header/operationFuncs.h
        source/interfaceFuncs.cpp
        header/interfaceFuncs.h
        source/Product.cpp
        header/Product.h
        source/Profile.cpp
        header/Profile.h
        source/profileFuncs.cpp
        header/profileFuncs.h
        source/profileInterface.cpp
        header/profileInterface.h
        source/menu.cpp
        header/menu.h
        source/enterwindow.cpp
        header/enterwindow.h
        source/enterwindow.ui
        source/regwindow.cpp
        header/regwindow.h
        source/regwindow.ui
        source/modeChooseWindow.cpp
        header/modeChooseWindow.h
        source/modechoosewindow.ui
        source/ProductData.cpp
        header/ProductData.h
        header/buyerwindow.h
        source/buyerwindow.cpp
        source/buyerwindow.ui
        source/ProfileControl.cpp
        header/ProfileControl.h
        source/Admin.cpp
        header/Admin.h
        source/sellermenu.cpp
        header/sellermenu.h
        source/sellermenu.ui
        source/ioninfo.cpp
        header/ioninfo.h
        source/ioninfo.ui
)
target_link_libraries(untitled51
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
