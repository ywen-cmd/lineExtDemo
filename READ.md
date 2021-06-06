工程文件路径： /home/user15/lineExtDemo
该目录下主要有以下几个文件：
	src     		文件夹存放所有.cpp源文件
	include 		文件夹存放所有.h头文件
	build   		文件夹存放编译链接相关文件
	CMakeLists.txt  用于生成MakeFile文件，生成后的文件存放到build目录下
	lineExt         由编译链接生成的可执行文件，用于生成中心线
工程编译链接步骤：
	1、先生成MakeFile文件
		进入 cd /home/user15/lineExtDemo/build/
		执行命令 ccmake ../
		选择c,在选择g
	2、编译链接生成可执行程序lineExt
		执行命令 make
	3、返回到/lineExtDemo目录下
		执行命令 cd ..
	4、生成中心线
		执行命令 ./lineExt boundary_1.txt
	5、最后会在/lineExtDemo目录下生成centerline_1.txt


