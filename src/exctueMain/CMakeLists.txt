cmake_minimum_required(VERSION 3.20)
project(exctueMain)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_CINCLUDE})
file(GLOB File_Source
${PROJECT_CINCLUDE}/*.h
exctueMain.cpp
)

add_executable(exctueMain  ${File_Source})
target_link_libraries(exctueMain BasicFun)
target_link_libraries(exctueMain PicJsonTrans)