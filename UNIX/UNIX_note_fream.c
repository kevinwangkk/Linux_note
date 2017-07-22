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
			#include <sys/types.h>
			#include <dirent.h>
			opendir() / fdopendir()
			readdir()
			closedir()
			目录相关其他函数
			递归打印所有子目录


4. Unix/Linux系统下的进程管理技术；

	day31  进程管理
			ps -aux | more - 表示分屏显示所有的进程信息；
			kill -9 进程号 - 表示杀死指定的进程

			#include <unistd.h>
			#include <sys/types.h>
			getpid()  //获取当前进程的进程号
			getppid() //获取当前进程父进程的进程号 parent
			getuid()  //获取当前用户的编号 user
			getgid()  //获取当前用户的用户组编号 group

	day32  进程创建
			#include <unistd.h>
			pid_t fork(void);  //创建子进程
				1.父子进程的执行关系
				2.父子进程之间的关系
				3.父子进程的复制(内存)关系

		   进程终止
			#include <unistd.h>
			void _exit(int status); //立即终止正在调用的进程

			#include <stdlib.h>
			void exit(int status); //终止正常的进程

			#include <stdlib.h>
			int atexit(void (*function)(void)); //注册一个函数用于进程正常终止时调用

			#include <stdlib.h>
			int on_exit(void (*function)(int , void *), void *arg); //(带参数)注册一个函数用于进程正常终止时调用

		   进程等待
			#include <sys/types.h>
			#include <sys/wait.h>
			pid_t wait(int *status); //等待进程的状态改变
				WIFEXITED(*status) - 当子进程正常终止时返回真
				WEXITSTATUS(*status) - 返回子进程的退出状态信息

			#include <sys/types.h>
			#include <sys/wait.h>
			pid_t waitpid(pid_t pid, int *status, int options); //wait for process to change state

		   进程的其他管理函数
			#include <unistd.h>
			#include <sys/types.h>
			pid_t vfork(void); //create a child process and block parent

			vfork函数和exec系列函数配合使用

			#include <unistd.h>
			execl, execlp, execle, execv, execvp, execvpe - execute a file //执行文件

			#include <stdlib.h>
			int system(const char *command); //execute a shell command


5. Uinx/Linux系统下的信号处理技术；

	day33  信号的处理
			信号本质就是一种软件中断
			kill -l  表示显示当前系统所支持的所有信号

			SIGINT  2   采用ctrl+c来产生该信号，默认处理方式为终止进程
			SIGQUIT 3   采用ctrl+\来产生该信号，默认处理方式为终止进程
			SIGKILL 9   采用kill -9命令来产生，默认处理方式为终止进程

		   信号3种处理方式
			1. 默认处理，绝大多数信号的默认处理方式都是终止进程；
			2. 忽略处理
			3. 自定义处理/捕获处理

			#include <signal.h>
			 typedef void (*sighandler_t)(int);
			 sighandler_t signal(int signum, sighandler_t handler);  //设置指定信号的处理方式

			父子进程对信号的处理方式 
				fork 和 vfork 区别

		   发送信号函数
			#include <sys/types.h>
			#include <signal.h>
			int kill(pid_t pid, int sig);  //发送信号给进程

			#include <signal.h>
			int raise(int sig); //给调用者发送信号

			#include <unistd.h>
			unsigned int sleep(unsigned int seconds); //使进程进入seconds时间睡眠

			#include <unistd.h>
			unsigned int alarm(unsigned int seconds); //设置second时间的闹钟

	day34  信号集
			#include <signal.h>
			int sigemptyset(sigset_t *set); //清空信号集
			int sigfillset(sigset_t *set); //填满信号集
			int sigaddset(sigset_t *set, int signum); //增加信号到信号集中
			int sigdelset(sigset_t *set, int signum); //删除信号集中指定的信号
			int sigismember(const sigset_t *set, int signum); //判断信号是否存在信号集中

		   信号的屏蔽
			#include <signal.h>
			int sigprocmask(int how, const sigset_t *set, sigset_t *oldset); //用于提取/修改当前进程中的信号屏蔽集合

			#include <signal.h>
			int sigpending(sigset_t *set); 
			//获取信号屏蔽期间来过但没有来得及处理的信号，将所有获取到的信号存放在参数指定的信号集set中，通过参数带出去；

		   其他信号相关函数
			sigaction()函数 => signal函数的增强版
			#include <signal.h>
			int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
			//用于检查和修改指定信号的处理方式

			#include <signal.h>
			int sigqueue(pid_t pid, int sig, const union sigval value); //向指定的进程发送指定的信号和附加数据

		   计时器
			在linux系统中，为每个进程都维护三种计时器，分别为：真实计时器，虚拟计时器，以及实用计时器，一般采用真实计时器进行计时；

			#include <sys/time.h>
			int getitimer(int which, struct itimerval *curr_value);
			int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
			//获取/设置计时器的参数信息


6. Uinx/Linux系统下的进程间通信技术；

	day35  进程间通信

			管道
			管道本质上就是文件，只是一种比较特殊的文件
			管道分为两种：有名管道 和 无名管道
			有名管道 - 可以用于任意两个进程间的通信；
			无名管道 - 只能用于父子进程之间的通信；

			管道的特殊性就在于仅仅作为进程间通信的媒介，但是管道本身并不会存在任何数据

			#include <sys/types.h>
			#include <sys/stat.h>
			int mkfifo(const char *pathname, mode_t mode); //创建一个有名管道

			#include <unistd.h>
			int pipe(int pipefd[2]); //创建无名管道

			共享内存

7. Uinx/Linux系统下的网络编程技术；


8. Uinx/Linux系统下的多线程开发技术；


