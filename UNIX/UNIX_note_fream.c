/* C NOTE FREAM */
	day1 day2 命令行 vi 基础操作  C基础知识
	day3 数据类型 占位符 零碎知识点 进制转换
	day4 负数进制转换 占地大类型 占地小类型 强转 八进制 十六进制 操作符
	day5 隐式类型转换 分支语句（逻辑判断）if for switch case break continue
	day6 srand()/rand() 输入/输出缓冲区 scanf()/printf()
							scanf("%*[^\n]");/scanf("%*c"); fflush(stdout);
	day7 数组 array 多维数组
	day8 函数 volatile 行参 实参 数组形参 可变长函数参数(内容不足)
	day9 

/* UNIX NOTE FREAM */

1. Unix/Linux系统的概述以及编程基础；

	day23  manual gcc(编译命令) 　头文件的详细组成 (1)头文件卫士(2)其他头文件(3)宏定义(4)结构体(5)外部变量和函数声明
	day24  常用预处理宏指令　 环境变量 export PATH 　查找头文件 whereis stdio.h
	day25  静态库 共享库         共享库的动态加载 4个函数            #include<dlfcn.h> dlopen()/dlsym()/dlclose()/dlerror()
	day26  错误处理      #include<errno.h> strerror()/perror()重要
		   环境表相关函数 #include<stdlib.h> getenv()/setenv()/putenv()/clearenv()
   
2. Unix/Linux系统下的内存管理技术；

	day27  进程中的内存区域划分 	 代码区，只读常量区，全局区/数据区，BSS段，堆区，栈区；
								堆区的内存地址按照从小到大依次进行分配，栈区的内存地址按照从大到小依次分配，以避免区域的重叠；
			常量字符串不同存放形式的比较(重点) 常量字符串的字符指针 常量字符串的数组
			虚拟内存管理技术 建立映射关系 0——3G-1 是用户空间 3G——4G-1 是内核空间
			段错误的由来
	day28  内存相关函数
			#include <unistd.h>  getpagesize() //获取一个内存页大小
			#include <unistd.h>  sbrk()/brk()  //申请动态内存 释放动态内存
			#include <sys/mman.h>  mmap()/munmap()  //map or unmap files or devices into memory


3. Unix/Linux系统下的文件管理以及目录操作；

	day28  标C中的文件操作函数：
			fopen()/fclose()/fread()/fwrite()/fseek();

		   UC中的文件操作函数：
			open()/close()/read()/write()/lseek();
			#include <sys/types.h> 
			#include <sys/stat.h>
			#include <fcntl.h>
			#include <unistd.h>

			获取文件大小的两种方法
			1. 使用fseek函数调整文件读写位置到末尾，使用ftell函数返回；
			2. 使用lseek函数调整文件读写位置到末尾，返回值就是文件大小；
			
	day29  标C和UC文件操作函数的效率  
		   文件描述符工作原理
		   #include <unistd.h>  dup()/dup2()  //复制文件描述符
		   
	day30  文件管理
			#include <unistd.h>
    		#include <fcntl.h>
			fcntl()  //manipulate file descriptor  实现文件锁(重点) 　复制文件描述符
					在读写操作的时候，附带加锁操作，根据能否进行加锁成功决定是否读写操作；

			#include <unistd.h>
			access()  //检查文件的存在性及是否拥有相应权限

			#include <sys/stat.h>
			#include <sys/types.h>
			#include <unistd.h>
			stat() / fstat()  //获取指定文件的状态信息

			#include <time.h>
			ctime()      //将参数指定的整数时间转换为字符串类型时间并返回
			localtime()  //将参数指定的整数时间转换为结构体指针类型的时间

	day31  文件管理
			#include <sys/stat.h>
			chmod() / fchmod()  //修改指定文件的指定权限


			#include <unistd.h>
			#include <sys/types.h>
			truncate() / ftruncate()  //修改指定文件的指定大小

			#include <sys/stat.h>
			#include <sys/types.h>
			umask()   //设置文件在创建时屏蔽的权限为：参数指定的权限值

			#include <sys/mman.h>
			mmap() / munmap() //建立文件到虚拟地址的映射，可以将对文件的读写操作转换为对内存地址的读写操作，
			                  //只需要简单的赋值操作就可以将数据写入到文件中，因此又多了一种读写文件的方式

	       目录管理
			
4. Unix/Linux系统下的进程管理技术；


5. Uinx/Linux系统下的信号处理技术；


6. Uinx/Linux系统下的进程间通信技术；


7. Uinx/Linux系统下的网络编程技术；


8. Uinx/Linux系统下的多线程开发技术；


