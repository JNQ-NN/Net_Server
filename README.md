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
3.链接动态库  /usr/local/lib/libxxx.so 存放动态库.so文件
  在Makefile使用-lxxx链接动态库
4.编译选项细化 如选择c++版本
5.将文件打包成deb包


#cJson
使用时，只需使用cJSON的cJSON.cpp cJSON.h 文件即可

#log4cplus
使用前linux环境应安装log4cplus
编译时应该链接log4cplus动态库

#boost::asio
使用时，需要安装
安装asio方法 $sudo apt install libasio-dev


#mysql
安装mysql服务 $sudo apt-get install mysql-server
初始化配置 $sudo mysql_secure_installation
查看服务 $sudo systemctl status mysql.service
#配置mysql远程访问 
$sudo vi /etc/mysql/mysql.conf.d/mysqld.cnf #找到 bind-address 修改值为 0.0.0.0
$sudo /etc/init.d/mysql restart #重启mysql
#打开mysql
$/etc/init.d/mysql
#安装libmysqlclient库
$sudo apt-get install libmysqlclient-dev
#账户&密码 admin&123456
