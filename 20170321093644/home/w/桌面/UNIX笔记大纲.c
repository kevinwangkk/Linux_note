	1. Unix/Linux系统的概述以及编程基础；
	2. Unix/Linux系统下的内存管理技术；
	3. Unix/Linux系统下的文件管理以及目录操作；
	4. Unix/Linux系统下的进程管理技术；
	5. Uinx/Linux系统下的信号处理技术；
	6. Uinx/Linux系统下的进程间通信技术；
	7. Uinx/Linux系统下的网路编程技术；
	8. Uinx/Linux系统下的多线程开发技术；

1. Unix/Linux系统的概述以及编程基础；
23
	基本知识点

24
	环境变量

25
	库文件的概念和使用 静态库 共享库  
	共享库的动态加载 #include <dlfcn.h>   dlopen() dlsym() dlclose() dlerror()
		dynamic linking

26
	错误处理 
	错误编号 #include<errno.h> - 实现了对errno外部变量的声明，和包含其他头文件，
				     包含errno的取值范围等信息；
	环境表
  	#include<stdlib.h>  getenv() setenv() unsetenv() putenv() clearenv()

2. Unix/Linux系统下的内存管理技术；
27
	内存管理技术 程序和进程 进程中的内存区域划分 
	常量字符串不同存放形式的比较（重点） 虚拟内存管理技术
	段错误的由来  使用malloc函数申请动态内存->内存页

28
	内存管理函数 
		#include <unistd.h> getpagesize() 获取内存页的大小 

		#include <unistd.h>
		sbrk() sbrk函数专门用于申请内存，brk函数专门用于释放内存 搭配使用 
		brk() 

		#include <sys/mman.h>
		mmap() 建立文件/设备到虚拟内存之间的映射
		munmap() 解除

	/*内存管理函数之间的层次关系*/
	标准C语言 => 使用malloc函数申请内存，使用free函数释放内存

	POSIX标准 => 使用sbrk函数申请内存，使用brk函数释放内存

	操作系统 => 使用mmap函数建立映射，使用munmap函数接触映射

3. Unix/Linux系统下的文件管理以及目录操作；
28
	ls -l 详解
	文件管理的相关函数（重中之重）
	#include <sys/types.h>
      	#include <sys/stat.h>
       	#include <fcntl.h> 
	open()函数 close()函数 read()函数 write函数 lseek()函数

	获取一个文件的大小信息？
	1. 使用fseek函数调整文件读写位置到末尾，使用ftell函数返回；
	2. 使用lseek函数调整文件读写位置到末尾，返回值就是文件大小；

29
	标C和UC文件操作函数效率  
	文件描述符的工作原理-> 
	#include <unistd.h> dup/dup2函数  复制文件描述符

30
	文件管理
	#include <unistd.h>
       	#include <fcntl.h>
	fcntl()	 manipulate file descriptor 操作文件描述符  //主要用于文件锁 读锁 写锁

	#include <unistd.h>
	access() 判断文件的存在性以及是否拥有相应的权限

	#include <sys/types.h>
       	#include <sys/stat.h>
       	#include <unistd.h>
	stat/fstat函数 用于获取指定的文件状态信息 (类型 大小 修改时间)

	#include <time.h>
	ctime() 用于将参数指定的整数时间转换为字符串类型时间并返回

31
	文件管理
	#include<sys/stat.h>
	chmod/fchmod函数 修改指定文件的指定权限

	#include<unistd.h>
	#include<sys/types.h>
	truncate/ftruncate函数 修改指定文件的指定大小

	#include<sys/stat.h>
	#include<sys/types.h>
	umask() 设置文件在创建时屏蔽的权限为：参数指定的权限值

	#include<sys/mmap.h>
	mmap/munmap函数 
	通过建立文件到虚拟地址的映射，可以将对文件的读写操作转换为对内存地址的读写操作，
只需要简单的赋值操作就可以将数据写入到文件中，因此又多了一种读写文件的方式

31
	目录管理
	#include <sys/types.h>
       	#include <dirent.h>
	opendir/readdir/closedir

4. Unix/Linux系统下的进程管理技术；
31	
	进程管理
	//ps - 表示查看当前终端启动的进程信息
	//ps -aux - 表示查看所有包括其他使用者的进程信息；
	//ps -aux | more - 表分屏显示所有的进程信息；

	#include <sys/types.h>
       	#include <unistd.h>
	getpid() - 获取当前进程的编号，返回值类型是pid_t    int
	getppid() - 获取当前进程父进程的编号，返回值类型是pid_t	      //parent
	getuid() - 获取当前用户的编号，返回值类型是uid_t  unsigned int   //user  
	getgid() - 获取当前用户所在用户组的编号,返回值类型你是gid_t  unsigned int	

32
	进程的创建
	#include <unistd.h>
	fork() 创建子进程
	父子进程的内存关系

	进程的终止
	1. 正常终止进程的方式
		1. 执行main函数中的return语句；
		2. 调用exit()函数进行终止；
		3. 调用 _exit()和 _Exit()函数进行终止；//立即终止“immediately”
		4. 最后一个线程返回；
		5. 最后一个线程调用了pthread_exit()函数；

	2. 非正常终止进程的方式
		1. 采用信号终止进程的执行；
		2. 最后一个线程被其他线程取消；
	
	#include <unistd.h>
	void _exit(int status); => uc函数 //终止当前正在调用的进程

       	#include <stdlib.h>
       	void _Exit(int status); => 标C函数 //终止当前正在调用的进程

	#include <stdlib.h>
       	void exit(int status);  //终止正常的进程

	#include <stdlib.h>
       	int atexit(void (*function)(void));//注册一个函数用于进程正常终止时调用
			//该形参里的函数会在调用它的函数正常结束时register

	#include <stdlib.h>
       	int on_exit(void (*function)(int , void *), void *arg);
	//注册一个函数用于进程正常终止时调用
			//参数arg指针会传给参数function函数里的void*
	例子在 day32作业

	进程的等待
	#include <sys/types.h>
       	#include <sys/wait.h>
	pid_t wait(int *status);  //用于正在执行的进程
	//主要用于挂起当前正在执行的进程直到有一个子进程终止为止

	#include <sys/types.h>
       	#include <sys/wait.h>
	pid_t waitpid(pid_t pid, int *status, int options);
	//用于等待参数指定的进程，并获取退出状态信息；

	进程管理的其他函数
	#include <sys/types.h>
       	#include <unistd.h>
       	pid_t vfork(void); //创建子进程并挂起父进程

	exec系列函数
	vfork函数本身没有太大的实际意义，一般与exec系列的函数搭配使用，该用法主要用于子进程需要与父进程完全不同的代码段配合中，其中vfork函数专门用于创建子进程，exec系列函数专门用于执行全新的代码段；
	#include <unistd.h>
	execl, execlp, execle, execv, execvp, execvpe - execute a file
							  执行

	#include <stdlib.h>
       	int system(const char *command); //execute a shell command

5. Uinx/Linux系统下的信号处理技术；
33
	#include <signal.h>
       	typedef void (*sighandler_t)(int);
       	sighandler_t signal(int signum, sighandler_t handler);
	//对信号(1~64信号范围)进行默认处理/忽略处理/自定义函数处理

	/*父子进程对信号的处理方式*/
	1. 对于fork函数创建的子进程来说，子进程完全照搬父进程中对信号的处理方式，也就是父进程默认，子进程也默认；父进程忽略，子进程也忽略；父进程自定义处理，子进程也自定义处理；
	2. 对于vfork()和execl()函数启动的子进程来说，父进程默认，子进程也默认；父进程忽略，子进程也忽略；/*父进程自定义，子进程采用默认*/；(自定义函数不受控，没有改变函数内的信号值，所以是默认)

	发送信号的函数
	#include <sys/types.h>
       	#include <signal.h>
       	int kill(pid_t pid, int sig); //用于给指定的进程发送指定的信号；

	#include <signal.h>
       	int raise(int sig); //用于给当前正在调用的进程/线程发送参数指定的信号，对于单线程的程序来说，等价于kill(getpid(),sig)

	#include <unistd.h>
       	unsigned int sleep(unsigned int seconds);
	//用于使得当前正在调用的进程进入睡眠状态，当指定的秒数睡够了则返回0，当指定的秒数没有睡够但一个不能忽略的信号到来了，则返回剩余没有来得及睡的秒数；

	#include <unistd.h>
       	unsigned int alarm(unsigned int seconds);
	用于经过参数指定的秒数后给当前正在调用的进程发送SIGALRM信号，如果参数为0，则表示没有新的闹钟被设置，每次设置闹钟时都会取消之前的闹钟；
	如果之前有闹钟则返回/*之前*/闹钟没有来得及响的剩余秒数，否则返回0；

34
	信号集
	#include <signal.h>
       	int sigemptyset(sigset_t *set); //清空信号集
       	int sigfillset(sigset_t *set);	//填满信号集
       	int sigaddset(sigset_t *set, int signum); //添加信号到信号集中
       	int sigdelset(sigset_t *set, int signum); //删除信号集中的指定信号
       	int sigismember(const sigset_t *set, int signum); //判断信号是否存在信号集中
	
	信号的屏蔽
	#include <signal.h>
       	int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
	//用于提取/修改当前进程中的信号屏蔽集合；

	#include <signal.h>
       	int sigpending(sigset_t *set);	
	//获取信号屏蔽期间来过但没有来得及处理的信号，将所有获取到的信号存放在参数指定的信号集set中，通过参数带出去；

	#include <signal.h>
       	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	//用于检查和修改指定信号的处理方式；

	#include <signal.h>
       	int sigqueue(pid_t pid, int sig, const union sigval value);
	//用于向指定的进程发送指定的信号和附加数据；

	计时器
	#include <sys/time.h>
       	int getitimer(int which, struct itimerval *curr_value);
       	int setitimer(int which, const struct itimerval *new_value,
                     struct itimerval *old_value);
	//用于获取/设置计时器的参数信息；

6. Uinx/Linux系统下的进程间通信技术；
35
		
//******************************************************************************
	1. 预处理/预编译
		主要用于实现头文件的扩展以及宏替换； 
		（.i 文件）cc -E 01hello.c -o 01hello.i
	2. 编译
		主要用于将高级语言代码翻译成汇编语言，得到汇编文件； 
		（.s 文件）cc -S 01hello.i
	3. 汇编
		主要用于将汇编语言翻译成机器语言指令，得到目标文件；
		（.o 文件）cc -c 01hello.s
	4. 链接
		主要用于将目标文件和库文件进行链接，得到可执行文件；
		（ a.out ）cc 01hello.o
//******************************************************************************
/*头文件的详细组成（重点）*/
	1. 头文件的卫士
		#ifndef _XXX_H
		#define _XXX_H
		... ...
		#endif //_XXX_H
	2. 包含其他头文件
		#include<stdio.h>
		... ...
	3. 进行宏定义
		#define PI 3.14
	4. 进行结构体的定义以及对数据类型起别名
		typedef struct node{
			int data;
			struct node *next;
		}Node;
	5. 外部变量和函数的声明
		extern int num;
		void show(void);
//******************************************************************************
/*进程中的内存区域划分*/
如：
	int num；	//全局变量 默认初始值为0  BSS段(bss)
	int main(void)
	{
		int num; //局部变量 默认初始值为随机数  栈区(stack)
		return 0;
	}

1. 代码区(text)
	该区域存放具体的功能代码，函数指针指向该区域；
2. 只读常量区(text)
	该区域存放常量字符串，const 修饰的已经初始化的全局变量和静态局部变量，以及字面值；
3. 全局区/数据区(data)
	该区域存放没有 const 修饰的已经初始化的全局变量和静态局部变量；
4. BSS段(data)
	该区域存放没有 const 修饰也没有初始化的全局变量和静态局部变量；
	该区域会在main函数执行之前自动清零；
5. 堆区(heap)
	该区域由函数malloc()/calloc()/realloc()/free()函数操作的内存区域；
	该区域由程序员手动申请 手动释放；
6. 栈区(stack)
	该区域存放非静态的局部变量(包括函数的形参)；
	该区域由操作系统自动管理；

进程中的内存区域按照地址从小到大依次排列的结果：
	代码区，只读常量区，全局区/数据区，BSS段，堆区，栈区；
	一般来说，其中堆区的内存地址按照从小到大依次进行分配，栈区的内存地址按照从大到小依次分配，以避免区域的重叠；

//******************************************************************************
/*常量字符串不同存放形式的比较（重点）*/
对于记录常量字符串的字符指针来说，指针指向的内容不可以改变，但指针指向可以改变。
对于记录常量字符串的数组来说，指针指向的内容可以改变，但是指针的指向不可以改变。

对于指向一块动态内存的指针来说，指针指向的内容和指针的值都可以改变；

//常量字符串不同存放形式的比较
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	//pc指向只读常量区 pc本身在栈区
	//pc存的其实是h的地址
	char *pc="hello";
	
	//将字符串复制一份到连续存储空间中
	//ps指向栈区 ps本身在栈区 代表第一个元素的地址
	char ps[6]="hello";

	printf("pc=%p,&pc=%p\n",pc,&pc);  //pc=0x80486b0,&pc=0xbff48f2c
	printf("ps=%p,&ps=%p\n",ps,&ps);  //ps=0xbff48f36,&ps=0xbff48f36

	//试图改变指针的指向
	pc="1234";//ok
	//ps="1234";//error

	//试图改变指针指向的内容
	//strcpy(pc,"GOOD");//error
	strcpy(ps,"GOOD");//ok

	printf("--------------------\n");
	//pc指向堆区 pc本身在栈区
	pc=(char*)malloc(sizeof(char)*10);
	//试图改变pc指针指向的内容
	strcpy(pc,"world");
	printf("pc=%s\n",pc);//pc=world

	//指定临时指针指向了动态内存
	char *pt=pc;
	//试图改变pc指针的指向	
	pc="world2";
	printf("pc=%s\n",pc);//world2
	free(pt);
	pt=NULL;

	return 0;
}

结果：	pc=0x80486b0,&pc=0xbff48f2c
	ps=0xbff48f36,&ps=0xbff48f36
	--------------------
	pc=world
	pc=world2

//******************************************************************************

获取一个指定文件大小的方式有三种（重点）
1. 使用fseek函数调整文件读写位置到末尾，使用ftell函数
2. 使用lseek函数调整文件读写位置到末尾，返回值就是大小
3. 使用stat/fstat函数获取文件信息，结构体中st_size就是文件的大小信息；

//******************************************************************************





























































































































