cmake_minimum_required(VERSION 3.5)

project(Spectrum LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

# 查找 windeployqt / macdeployqt 文件
# list(APPEND CMAKE_PREFIX_PATH "C:/Project/Qt/Qt5.12.10/5.12.10/mingw73_64/lib")
# get_target_property(_qmake_executable Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
# get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
# find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt macdeployqt HINTS "${_qt_bin_dir}")
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(src
  #src
  ${CMAKE_SOURCE_DIR}/src/qsrc/main.cpp
  ${CMAKE_SOURCE_DIR}/src/qsrc/mainwindow.cpp
  ${CMAKE_SOURCE_DIR}/src/qsrc/mainwindow.h
  ${CMAKE_SOURCE_DIR}/src/qsrc/qinterface.cpp
  ${CMAKE_SOURCE_DIR}/src/qsrc/qinterface.h
  ${CMAKE_SOURCE_DIR}/src/qwidget/qcustomplot.cpp
  ${CMAKE_SOURCE_DIR}/src/qwidget/qcustomplot.h
  ${CMAKE_SOURCE_DIR}/src/qwidget/qtimerprogressbar.cpp
  ${CMAKE_SOURCE_DIR}/src/qwidget/qtimerprogressbar.h
  ${CMAKE_SOURCE_DIR}/src/qwidget/qtitlebar.cpp
  ${CMAKE_SOURCE_DIR}/src/qwidget/qtitlebar.h
  ${CMAKE_SOURCE_DIR}/src/csrc/cpfundation.cpp
  ${CMAKE_SOURCE_DIR}/src/csrc/cpfundation.h
  ${CMAKE_SOURCE_DIR}/src/csrc/cpextend.cpp
  ${CMAKE_SOURCE_DIR}/src/csrc/cpextend.h
  ${CMAKE_SOURCE_DIR}/src/csrc/modelspec.h
  ${CMAKE_SOURCE_DIR}/src/csrc/stringutils.h
  #res
  ${CMAKE_SOURCE_DIR}/src/res/mipmap.qrc
)

if(ANDROID)
  add_library(Spectrum SHARED
    ${src}
  )
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  add_executable(Spectrum WIN32
    ${src}
  )
else()
  add_executable(Spectrum
    ${src}
  )
endif()

target_link_libraries(Spectrum
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
)
