#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 定义项目名称
project (PETools)

# 定义项目的源文件目录
aux_source_directory(./source PROJECT_SOURCE_DIR)

# 定义编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build/)
# 定义编译输出可执行文件名
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR})


# 定义可执行文件运行参数
set(CUSTOM_RUN_ARGUMENTS "./resource/notepad.exe")
# 添加一个自定义运行规则 
ADD_CUSTOM_TARGET(run ./build/${PROJECT_NAME} ${CUSTOM_RUN_ARGUMENTS})
