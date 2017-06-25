/* C NOTE FREAM */
	day1 day2 命令行 vi 基础操作  C基础知识
	day3 数据类型 占位符 零碎知识点 进制转换
	day4 负数进制转换 占地大类型 占地小类型 强转 八进制 十六进制 操作符
	day5 隐式类型转换 分支语句（逻辑判断）if for switch case break continue
	day6 srand()/rand() 输入/输出缓冲区 scanf()/printf()
							scanf("%*[^\n]");/scanf("%*c"); fflush(stdout);
	day7 数组 array 多维数组

/* UNIX NOTE FREAM */

1. Unix/Linux系统的概述以及编程基础；

	day23  manual gcc(编译命令) 头文件的详细组成
	day24  常用预处理宏指令
	day25  静态库 共享库         共享库的动态加载 4个函数            #include<dlfcn.h> dlopen()/dlsym()/dlclose()/dlerror()
	day26  错误处理      #include<errno.h> strerror()/perror()重要
		   环境表相关函数 #include<stdlib.h> getenv()/setenv()/putenv()/clearenv()
   
2. Unix/Linux系统下的内存管理技术；

	day27  进程中的内存区域划分 	 代码区，只读常量区，全局区/数据区，BSS段，堆区，栈区；
								堆区的内存地址按照从小到大依次进行分配，栈区的内存地址按照从大到小依次分配，以避免区域的重叠；
			常量字符串不同存放形式的比较(重点) 常量字符串的字符指针 常量字符串的数组
			虚拟内存管理技术 建立映射关系 0——3G-1 是用户空间 3G——4G-1 是内核空间
			段错误的由来
			

3. Unix/Linux系统下的文件管理以及目录操作；


4. Unix/Linux系统下的进程管理技术；


5. Uinx/Linux系统下的信号处理技术；


6. Uinx/Linux系统下的进程间通信技术；


7. Uinx/Linux系统下的网络编程技术；


8. Uinx/Linux系统下的多线程开发技术；


