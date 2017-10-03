cmake_minimum_required(VERSION 3.1)

project(visualization.linuxwhatelse.pictureit LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_BUILD_TYPE Debug)

if(UNIX)
    add_definitions(-DTARGET_LINUX)
else()
    message(FATAL_ERROR "This plattform is NOT supported!")
endif()


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_POSITION_INDEPENDENT_CODE 1)

# Make sure we use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Find and include kodi
find_package(Kodi REQUIRED)
include_directories(${KODI_INCLUDE_DIR}/..)


# Find and include PictureIt
find_package(PictureIt REQUIRED)
include_directories(${PictureIt_INCLUDE_DIRS})
list(APPEND DEPLIBS ${PictureIt_LIBRARY})

set(ADDON_SOURCES src/addon.cpp)

build_addon(visualization.linuxwhatelse.pictureit ADDON DEPLIBS)

include(CPack)
