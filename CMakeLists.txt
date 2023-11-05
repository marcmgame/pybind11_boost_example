cmake_minimum_required(VERSION 3.13)

project(boost_example)

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif(APPLE)

add_subdirectory(pybind11)

find_package(Boost COMPONENTS chrono thread serialization REQUIRED)

include_directories (
  /usr/local/include
  ${Boost_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${USER_INCLUDE_PATH}/database
  ${USER_INCLUDE_PATH} )

link_directories (
  /usr/local/lib
  ${USER_LIBRARY_PATH} )

pybind11_add_module(_boost_example src/boost_example/_boost_example/main.cpp)

target_link_libraries (
  _boost_example PRIVATE
  Boost::chrono
  Boost::thread
  Boost::serialization)
