cmake_minimum_required(VERSION 3.0.0)

project(hyphamanager)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5LinguistTools REQUIRED)
find_package(Qt5WebKit REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

find_package(Hypha COMPONENTS Utils Core Handler Plugin REQUIRED)
#find_package(Poco REQUIRED)
find_library(POCO_DATA PocoData)
find_library(POCO_MYSQL PocoMySQL)
find_library(POCO_SQLITE PocoSQLite)
find_library(POCO_NET PocoNet)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_FOUNDATION PocoFoundation)

find_package(Ldap)
find_package(Boost COMPONENTS signals thread system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${Hypha_INCLUDE_DIRS} ${Poco_INCLUDE_DIRS})

IF(WIN32)
    include_directories( "C:/poco/Net/include" "C:/poco/Foundation/include"
        "C:/poco/Util/include" "C:/poco/Data/include" "C:/poco/Data/MySQL/include" ${Hypha_INCLUDE_DIRS} )
    link_directories( "C:/poco/lib" "C:/Dev/hypha/lib" )
else()
    #link_directories( "/usr/lib/" "/usr/local/lib/" )
ENDIF(WIN32)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/defines.h.cmake
				${CMAKE_CURRENT_BINARY_DIR}/defines.h)

file(GLOB Sources "*.cpp" "main/*.cpp" "database/*.cpp" "settings/*.cpp" "user/*.cpp" "connection/*.cpp"
        "handler/*.cpp" "plugin/*.cpp" "wizzards/*.cpp" )
file(GLOB Headers "*.h" "main/*.cpp" "database/*.cpp" "settings/*.h" "user/*.h" "connection/*.h"
        "handler/*.h" "plugin/*.h" "wizzards/*.h" )
file(GLOB Resources "res/*.qrc" )
file(GLOB UIS "res/*.ui" "main/*.ui" "user/*.ui" "connection/*.ui" "settings/*.ui"
        "handler/*.ui" "plugin/*.ui" "wizzards/*.ui" )
file(GLOB Trans "i18n/*.ts" )

set(hyphamanagerlibs ${Hypha_LIBRARIES} 
     ${Boost_LIBRARIES} ${Poco_LIBRARIES} PocoNet PocoUtil PocoFoundation PocoData PocoMySQL PocoSQLite)

qt5_add_resources(ResourceSources ${Resources})
qt5_wrap_ui(UI_SRCS ${UIS})

qt5_create_translation(QM "."
 ${Sources} ${Headers} ${UIS}
 ${Trans}
 OPTIONS -no-obsolete)
set_source_files_properties(${QM} PROPERTIES OUTPUT_LOCATION ${TRANSLATION_DIRECTORY})


if(LDAP_FOUND AND USE_LDAP)
    add_definitions(-DWITH_LDAP)
    include_directories(${LDAP_INCLUDE_DIR} )
    file (GLOB Sources ${Sources} "database/ldap/*.cpp")
    file (GLOB Headers ${Headers} "database/ldap/*.h")
    set(hyphamanagerlibs ${hyphamanagerlibs} ${LDAP_LIBRARIES})
endif(LDAP_FOUND AND USE_LDAP)
# Windows application icon
if (WIN32)
    set(hyphamanagerlibs HyphaUtils Qt5::Widgets Qt5::WinMain Qt5::WebKit Qt5::WebKitWidgets Qt5::PrintSupport)

    set(WINDOWS_RES_FILE ${CMAKE_CURRENT_BINARY_DIR}/resources.obj)
    include_directories( C:/poco/Net/include C:/poco/Foundation/include C:/poco/Util/include)
    #set(hyphamanagerlibs ${hyphamanagerlibs}  PocoNet PocoUtil PocoFoundation )
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(hyphamanagerlibs ${hyphamanagerlibs} "C:/poco/lib/PocoNetd.lib" "C:/poco/lib/PocoUtild.lib" "C:/poco/lib/PocoFoundationd.lib"  )
    else()
        set(hyphamanagerlibs ${hyphamanagerlibs} "C:/poco/lib/PocoNet.lib" "C:/poco/lib/PocoUtil.lib" "C:/poco/lib/PocoFoundation.lib"  )
    endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (MSVC)
    add_custom_command(OUTPUT ${WINDOWS_RES_FILE}
      COMMAND rc.exe /fo ${WINDOWS_RES_FILE} resources.rc
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/win
    )
  else()

    add_custom_command(OUTPUT ${WINDOWS_RES_FILE}
      COMMAND windres.exe resources.rc ${WINDOWS_RES_FILE}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/win
    )
  endif()
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${Sources} ${Headers} ${ResourceSources} ${UI_SRCS} ${QM})
else()
    set(hyphamanagerlibs ${hyphamanagerlibs} Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets Qt5::PrintSupport)
    set(hyphamanagerlibs ${hyphamanagerlibs} ${Hypha_LIBRARIES} PocoNet PocoUtil PocoFoundation )
    add_executable(${CMAKE_PROJECT_NAME} ${Sources} ${Headers} ${ResourceSources} ${UI_SRCS} ${QM})
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} ${hyphamanagerlibs})
qt5_use_modules(${CMAKE_PROJECT_NAME} Widgets Network Sql WebKit WebKitWidgets)

#file(COPY ${QM} DESTINATION ${TRANSLATION_DIRECTORY})

add_subdirectory( handlers )
add_subdirectory( plugins )
add_subdirectory( tests )

if (UNIX)
  install(TARGETS ${CMAKE_PROJECT_NAME}
          RUNTIME DESTINATION bin)
elseif (WIN32)
  install(TARGETS ${CMAKE_PROJECT_NAME}
          DESTINATION .)
endif()

enable_testing ()
add_test (NAME HyphaManagerTests COMMAND hyphamanagertests)
