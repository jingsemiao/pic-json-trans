cmake_minimum_required(VERSION 3.20)
project(exctueMain)



set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_CINCLUDE})
include_directories(${PROJECT_ThridParty})
include_directories(${PROJECT_ThridParty}/nlohmann-json)
include_directories(${PROJECT_OpenCv_Dir})

file(GLOB File_Source
${PROJECT_CINCLUDE}/*.h
exctueMain.cpp
)

add_executable(exctueMain  ${File_Source})
target_link_libraries(exctueMain BasicFun)
target_link_libraries(exctueMain PicJsonTrans)

target_link_directories(exctueMain PRIVATE ${PROJECT_OUTPUT_DIR})
target_link_libraries(exctueMain opencv_world4100.lib) # 链接库
