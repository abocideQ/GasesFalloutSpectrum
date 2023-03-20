# Qt build with CMake
# Tips: CMake Build Tools Should Be <QT.Version.TOOLS.Mingw> Or Windeployqt Will Not Work.
# 1. CMake: Scan for Kits(* from .../.../CMakeTools/cmake-tools-kits.json)
# 2. CMake: Select a Kist(* should be Qt's tools .../.../QT${QtVersion}/${QtVersion}/Mingw${MingwVersion}/bin)
# 3. CMake: Select a Variant(Debug or Release mode)
# 4. CMake: Clean Rebuild
# 5. CMake: Debug / Run Without Debugging
# 0. CMake: Install(Will Build a .exe/.???)
cmake_minimum_required(VERSION 3.5)

project(Spectrum LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# env path to find_package 
set(Qt5_DIR D:/Project/qt/Qt5.12.10/5.12.10/mingw73_64/lib/cmake/Qt5/)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# SRC
set(src
  # .CPP.H
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
  # .QRC
  ${CMAKE_SOURCE_DIR}/src/res/mipmap.qrc
)
if(ANDROID)
  add_library(${PROJECT_NAME} SHARED
  ${src}
  )
elseif(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_executable(${PROJECT_NAME} WIN32
    ${src}
  )
  else()
  add_executable(${PROJECT_NAME}
  ${src}
  )
  endif()
else()
  add_executable(${PROJECT_NAME}
  ${src}
  )
endif()

# LINK_LIB
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
)

# INSTALL
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
install(TARGETS ${PROJECT_NAME}
    ARCHIVE 
      DESTINATION lib
    LIBRARY 
      DESTINATION lib
    RUNTIME
      DESTINATION bin
)