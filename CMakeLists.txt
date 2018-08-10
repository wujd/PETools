#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (PETools)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(PETools ${DIR_SRCS})

# 启用测试
#enable_testing()
# 测试程序是否成功运行
#add_test (test_run PETools ~/Desktop/notepad.exe)
#add_custom_command(run ./PETools)
