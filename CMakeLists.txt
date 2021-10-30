cmake_minimum_required(VERSION 3.5)

project(QuickScreenshot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${CMAKE_BUILD_TYPE} MATCHES "[Dd][Ee][Bb][Uu][Gg]")
    set(IS_DEBUG TRUE)
else()
    set(IS_DEBUG FALSE)
endif()
message("Is Debug: ${IS_DEBUG}")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

#set(QT_MAJOR 6)
#set(QT_MAJOR 6 CACHE STRING "Use Qt6")
#set(QT_MAJOR ${QT_VERSION_MAJOR})

#find_library(QHOTKEY_LIBRARY NAMES qhotkey1 QHotkey1 HINTS "${CMAKE_PREFIX}/lib")
#message(${QHOTKEY_LIBRARY})

include(FetchContent)
set(QT_DEFAULT_MAJOR_VERSION 6)
option(QHOTKEY_INSTALL OFF)
FetchContent_Declare(QHotkey
    GIT_REPOSITORY https://github.com/Skycoder42/QHotkey
    GIT_TAG 1.5.0
)
FetchContent_MakeAvailable(QHotkey)

set(PROJECT_SOURCES
        src/main.cpp
        include/trayhandler.h src/trayhandler.cpp
        include/hotkeyhandler.h src/hotkeyhandler.cpp
        include/hotkeydialog.h src/hotkeydialog.cpp src/hotkeydialog.ui
        resources/resources.qrc
)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources/QuickScreenshot.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    if(IS_DEBUG)
        qt_add_executable(QuickScreenshot
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${APP_ICON_RESOURCE_WINDOWS}
        )
    else()
        qt_add_executable(QuickScreenshot
            WIN32
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${APP_ICON_RESOURCE_WINDOWS}
        )
    endif()
else()
    if(ANDROID)
        add_library(QuickScreenshot SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(QuickScreenshot
            ${PROJECT_SOURCES}
            ${APP_ICON_RESOURCE_WINDOWS}
        )
    endif()
endif()

target_link_libraries(QuickScreenshot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets QHotkey::QHotkey)

set_target_properties(QuickScreenshot PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QuickScreenshot)
endif()
