cmake_minimum_required(VERSION 3.5)

project(xsens_gps)

# path to look for the cmake files
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(xsens_gps_location C:/Program\ Files/Xsens/MT\ Software\ Suite\ 4.8/MT\ SDK)
option(USE_LOG4CPP ON)
option(LOG4CPP_READY OFF)

# The version number.
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "${PROJECT_SOURCE_DIR}/Config.h.in"
        "${PROJECT_BINARY_DIR}/Config.h"
)

find_package(Threads REQUIRED)
find_package(Log4cpp)

add_executable(xsens_gps src/main.cpp src/DeviceContainer.cpp)
include_directories(${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src)

if(${WIN32})
    if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
#        win 64
#        set( BOOST_LIBRARY "/boost/win64/lib" )
        include_directories("C:/Program Files/Xsens/MT Software Suite 4.8/MT SDK/x64/include")
        link_directories("C:/Program Files/Xsens/MT Software Suite 4.8/MT SDK/x64/lib")
        target_link_libraries(xsens_gps xstypes64
        xsensdeviceapi64
        )
    else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        include_directories("C:/Program Files/Xsens/MT Software Suite 4.8/MT SDK/Win32/include")
        find_library(xstypes32_LIB xstypes32 HINTS ${xsens_gps_location}/Win32/lib)
        find_library(xsensdeviceapi32_LIB xsensdeviceapi32 HINTS "C:/Program Files/Xsens/MT Software Suite 4.8/MT SDK/Win32/lib")
        #link_directories("C:\\Program Files\\Xsens\\MT Software Suite 4.8\\MT SDK\\Win32\\lib\\")
        target_link_libraries(xsens_gps
                ${xstypes32_LIB}
                ${xsensdeviceapi32_LIB}
                )

    endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

else()
#    not windows
include_directories(/usr/local/xsens/include)
link_directories(/usr/local/xsens/lib
        ${LOG4CPP_INCLUDE_DIRS}
        )
target_link_libraries(xsens_gps libxstypes.so
        libxsensdeviceapi.so
        ${LOG4CPP_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )
endif()

if(${LOG4CPP_found}&&${USE_LOG4CPP})
    include_directories(${LOG4CPP_INCLUDE_DIRS})
    link_directories(${LOG4CPP_INCLUDE_DIRS})
    target_link_libraries(${LOG4CPP_LIBRARIES})
    option(LOG4CPP_READY ON)
endif()

add_custom_command(TARGET xsens_gps POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        ${xsens_gps_location}/Win32/lib/xstypes32.dll      # <--this is in-file
        $<TARGET_FILE_DIR:xsens_gps>)                 # <--this is out-file path
add_custom_command(TARGET xsens_gps POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        ${xsens_gps_location}/Win32/lib/xsensdeviceapi32.dll       # <--this is in-file
        $<TARGET_FILE_DIR:xsens_gps>)                 # <--this is out-file path