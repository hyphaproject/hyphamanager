cmake_minimum_required(VERSION 3.0.0)

project(hyphamanager-handler)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins)
add_subdirectory( alarm )
add_subdirectory( blechuhr )
add_subdirectory( dooropener )
add_subdirectory( serverstatus )
add_subdirectory( videocontrol )
