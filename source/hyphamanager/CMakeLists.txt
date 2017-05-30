
#
# External dependencies
#

# find_package(THIRDPARTY REQUIRED)


find_package(Qt5Sql REQUIRED)
find_package(Qt5LinguistTools REQUIRED)
find_package(Qt5WebKit REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Network REQUIRED)


# Enable automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)

# ENABLE CMP0020: Automatically link Qt executables to qtmain target on Windows.
cmake_policy(SET CMP0020 NEW)

#
# Library name and options
#

# Target name
set(target hyphamanager)

# Exit here if required dependencies are not met
message(STATUS "Exe ${target}")


# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(feature_file "include/${target}/${target}_features.h")
set(export_file  "include/${target}/${target}_api.h")
set(export_macro "${target_upper}_API")


#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(resource_path  "${CMAKE_CURRENT_SOURCE_DIR}/resource")

configure_file(${include_path}/defines.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/defines.h)

file(GLOB headers
"${include_path}/*.h"
"${include_path}/main/*.h"
"${include_path}/database/*.h"
"${include_path}/settings/*.h"
"${include_path}/user/*.h"
"${include_path}/connection/*.h"
"${include_path}/plugin/*.h"
"${include_path}/wizzards/*.h" )

file(GLOB sources
"${source_path}/*.cpp"
"${source_path}/main/*.cpp"
"${source_path}/database/*.cpp"
"${source_path}/settings/*.cpp"
"${source_path}/user/*.cpp"
"${source_path}/connection/*.cpp"
"${source_path}/plugin/*.cpp"
"${source_path}/wizzards/*.cpp" )

file(GLOB uis
"${source_path}/*.ui"
"${source_path}/main/*.ui"
"${source_path}/database/*.ui"
"${source_path}/settings/*.ui"
"${source_path}/user/*.ui"
"${source_path}/connection/*.ui"
"${source_path}/plugin/*.ui"
"${source_path}/wizzards/*.ui" )


file(GLOB resources "${resource_path}/*.qrc" )
qt5_add_resources(resourcesources ${resources})

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$"
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$"
    ${source_group} ${sources})


#
# Create executable
#

# Build executable
add_executable(${target}
    MACOSX_BUNDLE
    ${sources}
    ${headers}
    ${uis}
    ${resourcesources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${include_path}
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source/${target}
    ${CMAKE_CURRENT_BINARY_DIR}/source/${target}
    ${CMAKE_CURRENT_BINARY_DIR}

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE

    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::core
    ${META_PROJECT_NAME}::user
    Qt5::WebKit Qt5::WebKitWidgets Qt5::PrintSupport )


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


#
# Compile options
#

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)


#
# Deployment
#

# Executable
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime
    BUNDLE  DESTINATION ${INSTALL_BIN} COMPONENT runtime
)
