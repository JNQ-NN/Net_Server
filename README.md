bin文件夹，用于存放可执行文件
obj文件夹，用于存放Makefile生成的中间文件
config.mk Makefile的全局配置文件
net文件夹，用于提供网络服务
tool文件夹，用于基本工具

#Makefile
$make 编译成可执行文件
$make run 执行编译出的可执行文件
$make clean 清理可执行文件和.o文件


#Makefile TODO
1.include .h文件
2.链接静态库
3.链接动态库
4.编译选项细化 如选择c++版本
5.将文件打包成deb包


#cJson
使用时，只需使用cJSON的cJSON.cpp cJSON.h 文件即可

#log4cplus
使用前linux环境应安装log4cplus
编译时应该链接log4cplus

#boost::asio
使用时，需要安装
安装asio方法 $sudo apt install libasio-dev
安装boost方法