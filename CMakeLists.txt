cmake_minimum_required(VERSION 3.13)

project(boost_example)

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif(APPLE)

add_subdirectory(pybind11)

set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_ROOT "/usr/local")

set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")

set(BOOST_INCLUDE_DIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARY_DIR "${BOOST_ROOT}/lib")

find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)
include_directories(${BOOST_INCLUDE_DIRS})

find_package(Boost COMPONENTS chrono thread serialization REQUIRED)

include_directories (
  /usr/local/include
  ${Boost_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
  ${USER_INCLUDE_PATH}/database
  ${USER_INCLUDE_PATH} )

link_directories (
  /usr/local/lib
  ${Boost_LIBRARY_DIR}
  ${Boost_LIBRARY_DIRS}
  ${USER_LIBRARY_PATH} )

pybind11_add_module(_boost_example src/boost_example/_boost_example/main.cpp)

target_link_libraries (
  _boost_example PRIVATE
  Boost::chrono
  Boost::thread
  Boost::serialization)
