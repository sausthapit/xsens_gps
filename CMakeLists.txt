cmake_minimum_required(VERSION 3.5)

project(xsens_gps)

# path to look for the cmake files
set(CMAKE_MODULE_PATH "/home/saurav/CLionProjects/xsens_gps")

find_package(Threads REQUIRED)
find_package(Log4cpp REQUIRED)

include_directories(/usr/local/xsens/include)
link_directories(/usr/local/xsens/lib
        ${LOG4CPP_INCLUDE_DIRS}

        )

add_executable(xsens_gps src/main.cpp src/console.cpp)

target_link_libraries(xsens_gps libxstypes.so
        libxsensdeviceapi.so
        ${LOG4CPP_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )