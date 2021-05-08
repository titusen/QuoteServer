cmake_minimum_required(VERSION 3.6)

project(QuoteServer)

find_package( Boost 1.56 COMPONENTS program_options REQUIRED )
find_package(Folly COMPONENTS program_options REQUIRED )
find_package(Wangle COMPONENTS program_options REQUIRED )
find_package(Fizz COMPONENTS program_options REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

include_directories( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)

set(LINKER_FLAGS1 "-lwangle  -lfizz -lfolly -lfollybenchmark -pthread -lglog -lgflags -ldl -ldouble-conversion -lcrypto -lssl")
set(LINKER_FLAGS2 "-lunwind -liberty -lboost_filesystem -lboost_system -lboost_regex -lboost_coroutine -lboost_context -levent -lsodium -lboost_program_options")

include_directories(src)
include_directories(gen-cpp)
include_directories(src_client)

file(GLOB DEPS src/*.cpp)
file(GLOB CLIENT_DEPS src_client/*cpp)

add_executable(QuoteServer src/main.cpp ${DEPS} )

add_executable(QuoteClient src_client/QuoteClient.cpp ${CLIENT_DEPS}  )

target_link_libraries(QuoteServer ${LINKER_FLAGS1} ${LINKER_FLAGS2})

target_link_libraries(QuoteClient ${LINKER_FLAGS1} ${LINKER_FLAGS2})