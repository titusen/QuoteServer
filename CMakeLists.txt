cmake_minimum_required(VERSION 3.6)

project(QuoteServer)

find_package( Boost 1.40 COMPONENTS program_options REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

include_directories( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)

set(LINKER_FLAGS "-lboost_system -lpthread -lthrift")

include_directories(src)
include_directories(gen-cpp)
include_directories(src_client)

file(GLOB DEPS src/*.cpp)
file(GLOB THRIFT_DEPS gen-cpp/QuoteAnalisys.h
gen-cpp/QuoteServer_constants.h
gen-cpp/QuoteServer_types.h
gen-cpp/QuoteServer_constants.cpp
gen-cpp/QuoteServer_types.cpp
gen-cpp/QuoteAnalisys.cpp
)
file(GLOB CLIENT_DEPS src_client/*cpp)

add_executable(QuoteServer src/main.cpp ${DEPS} ${THRIFT_DEPS})

add_executable(QuoteClient src_client/QuoteClient.cpp ${CLIENT_DEPS} ${THRIFT_DEPS}  )

target_link_libraries(QuoteServer ${LINKER_FLAGS})

target_link_libraries(QuoteClient ${LINKER_FLAGS})