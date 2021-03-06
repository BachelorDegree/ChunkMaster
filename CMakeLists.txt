CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(chunkmaster)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-Wall")

ADD_SUBDIRECTORY(PaxosKVServiceClient)
ADD_SUBDIRECTORY(IdAllocatorServiceClient)
ADD_SUBDIRECTORY(ChunkServerServiceClient)

INCLUDE_DIRECTORIES(/usr/local/include)
INCLUDE_DIRECTORIES(.)
LINK_LIBRARIES(pthread protobuf gpr grpc++ grpc++_reflection SQLiteCpp sqlite3 dl)

SET(APP_SOURCES "./dylib.cpp")
FILE(GLOB APP_SOURCES ${APP_SOURCES} "./Proto/*.cc")
FILE(GLOB APP_SOURCES ${APP_SOURCES} "./Logic/*.cpp")
FILE(GLOB APP_SOURCES ${APP_SOURCES} "./Handler/*.cpp")
FILE(GLOB APP_SOURCES ${APP_SOURCES} "./*.cpp")
INCLUDE_DIRECTORIES(".")
ADD_LIBRARY(chunkmaster SHARED ${APP_SOURCES})
TARGET_LINK_LIBRARIES(chunkmaster coredeps)
TARGET_LINK_LIBRARIES(chunkmaster paxoskvclient idallocatorclient chunkserverclient)
