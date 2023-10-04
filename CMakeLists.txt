cmake_minimum_required(VERSION 3.5)


project(ObjectViewer VERSION 1.0 LANGUAGES C CXX)
find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets LinguistTools Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT5_DIR}/lib/cmake")

find_package(OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)


include_directories("./third_party/QtGifImage/src/gifimage" "./third_party/QtGifImage/src/3rdParty/giflib")
set(PROJECT_SOURCES
        src/Settings/Settings.h
        src/Settings/Settings.cc
        src/main.cc
        src/Command/Command.h
        src/Command/Command.cc
        src/Transformer/Transformer.h
        src/Transformer/Transformer.cc
        src/View/mainwindow.h
        src/View/mainwindow.cc
        src/View/glwidget.cc
        src/View/glwidget.h
        src/View/mainwindow.ui
        src/ObjectViewer/ObjectViewer.h
        src/ObjectViewer/ObjectViewer.cc
        src/Controller/Controller.h
        src/Controller/Controller.cc
        src/Object/Object.h
        src/Object/Object.cc
        src/FileReader/BaseFileReader.h
        src/FileReader/ObjectFileReader.h
        src/FileReader/ObjectFileReader.cc
        src/MediaSaver/MediaSaver.h
        src/MediaSaver/MediaSaver.cc
        src/Object/Object.h
        src/Object/Object.cc

        ./third_party/QtGifImage/src/gifimage/qgifimage.h
        ./third_party/QtGifImage/src/gifimage/qgifimage.cpp
        ./third_party/QtGifImage/src/gifimage/qgifglobal.h
        ./third_party/QtGifImage/src/gifimage/qgifimage_p.h

        ./third_party/QtGifImage/src/3rdParty/giflib/gif_lib.h
        ./third_party/QtGifImage/src/3rdParty/giflib/gif_hash.h
        ./third_party/QtGifImage/src/3rdParty/giflib/gif_lib_private.h

        ./third_party/QtGifImage/src/3rdParty/giflib/dgif_lib.c
        ./third_party/QtGifImage/src/3rdParty/giflib/egif_lib.c
        ./third_party/QtGifImage/src/3rdParty/giflib/gifalloc.c 
        ./third_party/QtGifImage/src/3rdParty/giflib/gif_err.c
        ./third_party/QtGifImage/src/3rdParty/giflib/gif_font.c 
        ./third_party/QtGifImage/src/3rdParty/giflib/gif_hash.c 
        ./third_party/QtGifImage/src/3rdParty/giflib/quantize.c

        ${TS_FILES}
)




if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ObjectViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

endif()
target_include_directories(ObjectViewer PRIVATE src)

set_target_properties(ObjectViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_link_libraries(ObjectViewer PRIVATE Qt6::OpenGL)
target_link_libraries(ObjectViewer PRIVATE Qt6::Gui)
target_link_libraries(ObjectViewer PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(ObjectViewer PRIVATE Qt6::Core)
set_source_files_properties(resources/icons/icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
