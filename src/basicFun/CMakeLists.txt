cmake_minimum_required(VERSION 3.20)
add_definitions(-DCOMMONFUN_EXPORT)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_CINCLUDE})


file(GLOB File_Source
	basicFun.cpp
    ${PROJECT_CINCLUDE}/basicFunApi.h
)

project(BasicFun)
add_library(BasicFun SHARED 
${File_Source}
)






