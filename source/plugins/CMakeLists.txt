
# Check if examples are enabled
if(NOT OPTION_BUILD_PLUGINS)
    return()
endif()

# plugins

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MAIN ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/plugins")

add_subdirectory(email)
add_subdirectory(explorenfc)
add_subdirectory(fingerprintzfm)
add_subdirectory(lightsensor)
add_subdirectory(rfid)
add_subdirectory(rpianalogsensor)
add_subdirectory(rpigpio)
add_subdirectory(rpiled)
add_subdirectory(rpipir)
add_subdirectory(video)
add_subdirectory(watersensor)
add_subdirectory(wifi)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_MAIN})
