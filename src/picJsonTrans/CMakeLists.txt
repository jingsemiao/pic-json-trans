cmake_minimum_required(VERSION 3.20)
add_definitions(-DPICJSONTRANS_EXPORT)

project(PicJsonTrans)


#set(PROJECT_ThridParty ${PROJECT_TOP_DIR}/ThridParty)

include_directories(${PROJECT_CINCLUDE})
include_directories(${PROJECT_ThridParty})
include_directories(${PROJECT_ThridParty}/nlohmann-json)

set(CMAKE_CXX_STANDARD 17)

file(GLOB File_Include
${PROJECT_CINCLUDE}/*.h
)

#GLOB_RECURSE 递归地去搜索设定目录下的文件
file(GLOB_RECURSE SUB_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_library(PicJsonTrans SHARED 
${File_Include}
${SUB_FILES}
)

message(NOTICE "PROJECT_TOP_DIR == " ${PROJECT_TOP_DIR})
message(NOTICE "CMAKE_CURRENT_SOURCE_DIR == " ${CMAKE_CURRENT_SOURCE_DIR})
#CMAKE_CURRENT_SOURCE_DIR

include_directories(${PROJECT_TOP_DIR}/src/basicFun)
target_link_libraries(PicJsonTrans BasicFun)
