cmake_minimum_required(VERSION 2.8)
project(PandarGeneralSDK)

find_package( PCL REQUIRED COMPONENTS common )

# set (CMAKE_CXX_FLAGS "-fPIC --std=c++11")
ADD_COMPILE_OPTIONS(-std=c++17 )


add_subdirectory(src/PandarGeneralRaw)

include_directories(
    .
    include
    src/PandarGeneralRaw/include
    ${PCL_INCLUDE_DIRS}
)

add_library( ${PROJECT_NAME} SHARED
    src/pandarGeneral_sdk.cc
    src/tcp_command_client.c
    src/util.c
    src/wrapper.cc
)

target_link_libraries(${PROJECT_NAME} 
    PandarGeneral
    pcap
)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    find_package(PCL REQUIRED)
    find_package(Threads REQUIRED)

    add_executable(PandarGeneralTest
        test/test.cc
    )
    
    target_link_libraries(PandarGeneralTest
        ${PROJECT_NAME}
        Threads::Threads
        # ${Boost_LIBRARIES}
        # ${PCL_IO_LIBRARIES}
        # Boost::thread
    )
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

