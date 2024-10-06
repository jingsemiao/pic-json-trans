cmake_minimum_required(VERSION 3.20)
add_definitions(-DPICJSONTRANS_EXPORT)

project(PicJsonTrans)


# 假设当前目录是包含CMakeLists.txt的目录  
# 获取当前目录的父目录  
#set CUR_DIR=%~dp0
# 获取当前源码目录的父目录
get_filename_component(MyParent_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

#CMAKE_CURRENT_SOURCE_DIR
message(NOTICE "PROJECT_TOP_DIR == " ${PROJECT_TOP_DIR})
message(NOTICE "PicJsonTrans MyParent_DIR == " ${MyParent_DIR})
message(NOTICE "PicJsonTrans CMAKE_CURRENT_SOURCE_DIR == " ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${MyParent_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_CINCLUDE})
include_directories(${PROJECT_ThridParty})
include_directories(${PROJECT_ThridParty}/nlohmann-json)
include_directories(${PROJECT_OpenCv_Dir})


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



include_directories(${PROJECT_TOP_DIR}/src/basicFun)
target_link_libraries(PicJsonTrans BasicFun)

message(STATUS "PROJECT_OpenCv_Dir Is: ${PROJECT_OpenCv_Dir}")

# 正是因为有了这句 target_link_directories ,才让 附加库目录中 多了对应的两个lib目录
# 非常重要。  似乎是会根据类型自动判断的 后续还需要研究下
target_link_directories(PicJsonTrans PRIVATE ${PROJECT_OUTPUT_DIR})
target_link_libraries(PicJsonTrans opencv_world4100.lib) # 链接库

