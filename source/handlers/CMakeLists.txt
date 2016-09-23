
# Check if examples are enabled
if(NOT OPTION_BUILD_HANDLERS)
    return()
endif()

# plugins

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MAIN ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/handlers")

add_subdirectory(blechuhr)
add_subdirectory(dooropener)
add_subdirectory(serverstatus)
add_subdirectory(videocontrol)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_MAIN})
