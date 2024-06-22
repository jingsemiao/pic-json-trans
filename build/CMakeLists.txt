cmake_minimum_required(VERSION 3.20)
project(pic-json-trans)

#get_filename_component获得该文件所在目录，如果是文件夹，则获取母文件夹路径
# ${CMAKE_SOURCE_DIR} == 项目/build
#此处是Build目录 ，所以这样能获取到整个项目顶级目录
#此变量也会被传递到子cmake
get_filename_component(PROJECT_TOP_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

#设置inlucde位置路径变量
set(PROJECT_CINCLUDE ${PROJECT_TOP_DIR}/include)


#定义编译生成输出结果
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


#将几个小项目包括进去
add_subdirectory(${PROJECT_TOP_DIR}/src/basicFun basicFun.out)
add_subdirectory(${PROJECT_TOP_DIR}/src/exctueMain exctueMain.out)
