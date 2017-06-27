智能家居项目：
   监控室内温度,温度高于某个阀值,报警
   监控室内烟雾,烟雾浓度高于某个阀值,报警
   监控红外状态,判断是否有非法闯入
   实现软件的在线升级
   实现软件和硬件版本号的查询
   实现MP3播放器功能
智能小车项目：
   实现小车的运动控制
   实现小车上的摄像头的摆动
   实现摄像头视频数据的采集
   实现小车的无线路由器功能和热点
   
实施步骤：
面试题：如何做一个嵌入式产品？
面试题：以采集温度为例,用51单片机,成本只需100元不到,为什么
        要选择一个高端的S5PV210+linux系统来做呢？

1.要分析用户的需求
  围绕着"嵌入式系统"的概念去谈
  以用户需求为中心
  紧接着以iphone手机的诺基亚1050为例
  软件和硬件可裁剪
  功能要合理
  价格要合适
  成本要低
  可靠性要高
  体积？
  功耗要低

2.硬件设计
  谈：嵌入式产品开发包括硬件和软件
  最难：芯片选型
  芯片选型的原则：
  性能要合适
  价格要合理
  芯片厂家服务要周到：
  		最好能够提供硬件参考设计
  		最好能够提供软件参考设计
  硬件通信接口要简单为主：
  		GPIO
  		UART
  		总线
  		I2C
  		1-Wire
  		SPI
  例如：以温度传感器为例：
  	LM77(I2C接口)：首选,采用标准I2C接口,I2C控制器完成时序,效率高
  	DS18B20(1-Wire):次选,采用1-wire,将会面临大量的忙延时
  
  以智能家居为例：
  CPU选型
  内存选型
  闪存选型
  外围接口的选型
  “主动出击”谈为什么不选择51单片机而选择高端的S5PV210
  如果以采用51单片机采集温度,烟雾,红外完全没有问题,成本低
  但是如果添加视频采集,视频数据的存储,网络功能,此处理器完全
  不能胜任,此时需要考虑高端的CPU
  
3.软件设计
  明确：是否运行操作系统
  裸板程序,程序框架:
  main() {
  	xxx_init //各种硬件初始化
  	while(1) {
  		//处理业务
  	}
  }
  中断处理函数(){
  	//中断相关的业务
  }
  
  操作系统：以linux系统为例
  交叉编译器
  	芯片厂家获取
  	版本要合适
  bootloader:(u-boot)
  	大谈特谈uboot的功能,谈笔记
  linux内核：
  	7大子系统,谈笔记
  rootfs根文件系统：
  	谈笔记,分分钟搞定
  外设设备的驱动程序：属于linux的范畴
        以按键或者AT24C02两个芯片为例
        按键关键牵扯到中断,大谈中断
        AT24C02牵着I2C总线,大谈I2C总线
        
  应用程序:属于rootfs范畴
  	谈系统调用的原理
  			
项目第一天任务安排：
1.制作最小rootfs根文件系统
2.移植tslib
  特点：
  0.tslib=touch screen lib触摸屏的硬件操作库
  1.开源软件
  2.管理的硬件是触摸屏
  3.运行在用户空间,本质就是动态库
  4.应用程序QT,Android能够调用tslib提供的动态库函数能够
    获取到触摸屏的有效坐标(X,Y)
    画图
  5.移植tslib的本质目的就是获取到对应的动态库,将来QT
    能够获取到X,Y坐标
  6.提示：开源软件操作三步曲：
    ./configure --prefix=/opt/project/tslib --host=arm-linux //配置
    切记：--prefix:指定安装路径
          --host:指定将来软件运行的目标平台arm,linux系统
    make //编译
    make install //安装,将编译生成的二进制文件统统放在
                 --prefix选项指定的目录中
  7.linux系统的按键,触摸屏,鼠标的设备文件都叫：
    /dev/input/eventX
    或者
    /dev/eventX
  8.tslib运行时重要的环境变量：
    //指定tslib动态库将来操作的触摸屏的设备文件,一定不能错
    export TSLIB_TSDEVICE=/dev/input/event3
    //指定tslib动态库的路径,否则将来提示找不到动态库
    export LD_LIBRARY_PATH=/home/tslib/lib:$LD_LIBRARY_PATH
  9.触摸屏校准
    如果将来QT点击,不精确,重新运行ts_calibrate校准  
             
3.移植QT
  1.移植的QT版本为4.8.4
    交叉编译器的版本不能为4.4.1,
  2.移植QT本质的目的：同样获取到QT的动态库
    将来自己编写的QT程序调用移植的QT动态库实现界面的操作和显示
  3.QT涉及的关键环境变量
    //告诉QT将来获取的坐标X,Y对应的触摸屏的设备文件
    export QWS_MOUSE_PROTO="Tslib:/dev/input/event3" 		
    //指定字体库
    export QT_QWS_FONTDIR=$QTDIR/lib/fonts
    //指定图片处理库
    export QT_PLUGIN_PATH=$QTDIR/plugins
    //QT运行时指定的QT动态库的路径
    export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
  4.切记切记,交叉编译自己的QT软件步骤：
    如果让自己的QT运行在linux虚拟机中,编译步骤：
    cd 自己的QT程序目录
    qmake -project //生成工程文件,只做一次
    qmake  //根据工程文件,生成Makefile,只做一次
    vim Makefile //查看CPP=g++
    make //编译
    
    
    如果让自己的QT程序运行在TPAD,编译步骤：
    cd 自己的QT程序目录
    //一定使用自己移植QT生成的qmake工具
    /opt/project/qt/bin/qmake -project //生成工程文件,只做一次
    /opt/project/qt/bin/qmake  //根据工程文件,生成Makefile,只做一次
    vim Makefile //查看CPP=arm-linux-g++
    make //编译 
    
4.通过QT界面实现开关灯操作
  实施步骤：
  1.分析用户需求
    通过QT上的界面按钮实现点击开和关TPAD上的LED1和LED2
  2.硬件设计,硬件特性
    LED采用GPIO通信方式
    硬件操作：输出高电平开
              输出低电平关
  3.软件设计
    3.1.uboot/kernel/rootfs:都已搞定
    3.2.编写LED的设备驱动
    实施步骤：
    1.创建项目LED驱动的源码存放目录
      mkdir /opt/project/drivers/led -p
      cd /opt/project/drivers/led
    2.编写LED驱动
      驱动参考代码：project.rar/drivers.tar.bz2/led
      vim led_drv.c 
      vim Makefile
      make
    3.创建驱动目标的存放目录
      mkdir /opt/rootfs/home/drivers/
      cp led_drv.ko /opt/rootfs/home/drivers/
    
    3.3.画出整个软件的操作流程图
        编写LED的硬件操作库(目的：让代码维护更加简便,使用更加方便)
        实施步骤：
        1.创建硬件操作库源码的存放目录
          mkdir /opt/project/hwlib/led -p
          cd /opt/project/hwlib/led
        2.编写硬件操作库源码
          参考代码：project.rar/hwlib.tar.bz2/led
          	    led.h //声明
          	    led.c //定义
          	    ledlib_test.c //测试用例
          	    Makefile
         vim led.h 
         vim led.c
         vim ledlib_test.c 
          	    
        3.编译生成动态库和测试用例
        arm-linux-gcc -shared -fpic -o libled.so led.c
        arm-linux-gcc -o ledlib_test ledlib_test.c -L. -lled
        
        4.创建硬件操作库和测试用例的存放目录
        mkdir /opt/rootfs/home/apptest //测试用例
        mkdir /opt/rootfs/home/applib  //动态库
        cp libled.so /opt/rootfs/home/applib
        cp ledlib_test /opt/rootfs/home/apptest
        
        5.添加动态库的运行的环境变量
          vim /opt/rootfs/etc/profile 文件最后添加：
          export LD_LIBRARY_PATH=/home/applib:$LD_LIBARY_PATH
          保存退出即可
          重启开发板
        6.开发板上测试驱动和硬件操作库
          开发板上执行：
          insmod /home/drivers/led_drv.ko
          /home/apptest/ledlib_test on 1
          ...
          如果都OK，说明动态库OK，驱动OK，硬件OK~!
      
      3.4.编写QT图形界面,会调用硬件操作库实现最终的开关灯      
      实施步骤：
      参考代码：project.rar/ehome_led.tar.bz2
      0.友情提示可以花点时间复习QT
        先看视屏QT.avi和QT2.avi
      1.利用qtcreator创建QT项目工程
        工程名：ehome
        工程源码存放路径：/opt/project/ehome
      2.利用qtcreator打开mainwindow.ui文件,添加两个
        按钮：
        开灯           关灯
        QPushButton    QPushButton
      3.给这两个按钮添加槽函数
        光标移动到按钮上方,点击右键,选择"跳转到槽函数"
        选择clicked()信号函数,确定以后自动在代码中
        添加了槽函数的声明和槽函数的定义
      4.利用qtcreator打开mainwindow.h文件,添加硬件
        操作库的头文件和相关的成员
        #include "led.h"
        
        在MainWindow类中添加新成员
        int m_led_fd; //LED设备文件描述符
      5.利用qtcreator打开mainwindow.cpp文件
        在构造函数中调用硬件操作库：
        m_led_fd = led_open();
        
        在开灯按钮的槽函数中调用库函数实现开灯：
        struct led_cmd led;
        led.whichled = 1; //第一个灯
        led.cmd = 1; //开
        led_config(m_led_fd, &led); //实现开第一个灯
        
        在关灯按钮的槽函数中调用库函数实现关灯：
        struct led_cmd led;
        led.whichled = 1; //第一个灯
        led.cmd = 0; //关
        led_config(m_led_fd, &led); //实现关第一个灯  
      
      6.交叉编译ehome图形界面软件
        切记：不能用qtcreator的绿色的三角按钮编译
              只能通过命令行去编译
               
        cd /opt/project/ehome
        /opt/project/qt/bin/qmake --project //生成工程文件  
        vim ehome.pro //打开工程文件,添加：
        INCLUDEPATH += /opt/project/hwlib/led  
        LIBS += -L/opt/project/hwlib/led -lled
        保存退出
        /opt/project/qt/bin/qmake //工程文件只有修改,就需要重新生成Makefile
        make 
        ls 
          ehome //可执行程序
        创建图形界面软件的存放目录
        mkdir /opt/rootfs/home/appbin
        cp ehome /opt/rootfs/home/appbin
        
      7.开发板测试ehome
        /home/appbin/ehome -qws //操作按钮观察灯是否开或者关
          
