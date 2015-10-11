cmake_minimum_required(VERSION 3.0.0)

project(hyphamanagertests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)
find_package(Qt5Core REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

include_directories ("." "../"
    ${Boost_INCLUDE_DIRS} )

file(GLOB Sources "*.cpp" "../blechuhr/model/*.cpp"
        "../blechuhr/model/rules/*.cpp" )
file(GLOB Headers "*.h" "../blechuhr/model/*.h"
        "../blechuhr/model/rules/*.h" ) 

add_executable (hyphamanagertests ${Sources} ${Headers})

target_link_libraries(hyphamanagertests
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    Qt5::Core
)
