项目第二天任务安排：
面试题：请谈谈你的智能家居项目
        提示：就以温度采集显示监控为例
实施步骤：
1.用户需求：采集室内温度,并且在ehome图形界面每隔5秒动态刷新显示温度
          如果温度高于某个阀值,启动报警器,让LED1告警指示灯每隔200ms闪烁

2.硬件设计
  2.1.硬件外设芯片选型,原则：
  性能合适
  价格合理
  服务周到
  接口简单
  
  采集温度要选择一款温度传感器
  例如：
  	I2C接口的LM77
        TPAD上选择1-Wire接口的DS18B20温度传感器(咱滴)
  
  2.2.掌控DS18B20的硬件特性
  1.粗看
    查看DS18B20温度传感器在开发板上所在的位置(咨询硬件工程师)
    确定DS18B20对应的标签“U20”
  
  2.细看
    首先看底板原理图,根据标签U20找到对应的链接位置P6
    三根管脚：
    VDD:电源
    GND：地
    DQ:数据线,并且连接了一个上拉电阻(默认为高电平)
       并且连接到CPU的XEINT8/GPH1_0
    
    最后看DS18B20的芯片手册,主要目的掌握软件将来如何访问此硬件
  
  3.阅读DS18B20芯片手册,关键目的是软件如何访问硬件
    3.1.DS18B20硬件通信接口采用一线式串行总线(1-Wire bus)
    开始解释“一线式串行总线”
    “一线式”：CPU和DS18B20的数据传输只需一根数据线,不像I2C总线
              还有一根时钟线
    	      数据线上连接一个上拉电阻
    “串行”：CPU和DS18B20是一个"时钟周期"传输1个bit位
    "总线"：在这一根数据线上可以挂接多个DS18B20
    画出简要的连接示意图
    
    3.2.看图提问题
    1.CPU如何找到总线上某个DS18B20
    2.如果CPU找到了某个DS18B20,CPU如何通过一根数据线和
      DS18B20进行通信呢？
    3.由于没有时钟线,如何保证双方数据传输正常呢
    答：答案都在DS18B20的手册中,重点关注其中的时序图
    
    3.3.继续阅读DS18B20芯片手册
    1.每一个DS18B20片内都集成了64BIT的ROM,存储对应的序列码(ID)
      类似I2C总线上外设的设备地址,都具有唯一性
    2.每一个DS18B20片内都集成了9字节的SRAM,用于存储相关的数据
      可以把它作为寄存器使用
      SRAM的byte0,byte1分别存放温度的低字节和高字节
      所以温度=byte1 << 8 | byte0
      
      兴奋：如果CPU要获取DS18B20采集的问题,无非就是CPU想办法
            读取到DS18B20片内的byte1和byte0数据即可
      通过byte0和byte1这两个寄存器的说明,得到以下公式：
      实际温度值=(byte1 << 8 | byte0)*0.0625(摄氏度)
      例如：
      实际温度值=0x0191*0.0625=25.0625摄氏度
    3.CPU访问DS18B20三步骤
      1.CPU发送初始化复位信号
        类似UART的起始位,I2C的START信号
      2.CPU发送ROM命令,用来匹配查找总线上某个DS18B20
        类似I2C的设备地址,SPI总线的片选信号拉低
      3.CPU发送功能性命令,用来和DS18B20进行数据的读写操作等
      
      明确：GPIO控制权
            谁配输出谁控制
            谁配输入谁释放
            可以同时配输入
            不可以同时配输出
            
    4.CPU访问DS18B20三步曲之CPU发送初始化复位信号P15
      重中之重：看时序写代码
      参考代码：
      void ds18b20_reset(void)
      {
      	gpio_direction_output(..., 0);
      	udelay(500);
      	gpio_direction_output(..., 1);
      	udelay(30);
      	gpio_direction_input(...); //释放控制权
      	data = gpio_get_value(...);
      	if (data == 1)
      		failed
      	else
      	        ok
      }
    
    5.CPU访问DS18B20三步骤之CPU发送ROM命令
      如果只连接一个DS18B20,可以跳过匹配过程,
      CPU只需向总线发送SKIP ROM命令即可,命令字=0xcc(11001100)
      注意：CPU通过一根数据线向总线发送数据,从数据的低位开始传输

	   I2C从数据的高位开始传输
	   1-wire从数据的底位开始传输
 	   UART从数据的底位开始传输

      问：由于CPU的处理速度要远远快于DS18B20,CPU如果单纯的发送数据
          0xCC给DS18B20,软件实现很简单,但是DS18B20显然不能处理
          CPU如何通过一根数据线将数据正常的发给DS18B20呢？
      答：重点看P16四个时序图
      void ds18b20_write8(unsigned char data)
      {
      		int i;
      		
      		for (i = 0; i < 8; i++) {
      			if(data & 0x1) {
      				//根据写1时序图
      				gpio_...(...,0);
      				udelay(3);
      				gpio_...(...,1); //CPU帮上拉电阻拉高
      				udelay(80);
      			} else {
      				//根据写0时序图
      				gpio_...(...,0);
      				udelay(80);
      				gpio_...(...,1);
      				udelay(3);
      			}
      			data = data >> 1;	
      		}
      }    
      
      unsigned char ds18b20_read8(void)
      {
      		unsigned char data = 0;
      		unsigned int ret;
      		int i;
      		
      		for (i = 0; i < 8; i++) {
      		    gpio_direction_output(.., 0);
      		    udelay(3);
      		    gpio_direction_input();//CPU释放控制权,将控制权交给DS18B20或者上拉电阻
      		    ret = gpio_get_value(); //采样0/1
      		    data |= ret << i;	
      		}
      		return data;
      }           
      
      切记：务必画出5个时序图
      
    6. CPU访问DS18B20三步骤之CPU发送功能性命令
    转换温度命令：CONVERTT,命令字=0x44
                  如果CPU要获取到DS18B20采集的温度,首先CPU
                  必须向DS18B20发送此命令,让DS18B20硬件上
                  进行采集温度,DS18B20采集的温度会自动放在
                  片内RAM的byte0和byte1中
    READ RAM命令：命令字=0xBE
    		  此命令用于CPU读取片内的RAM数据
    
    阶段总结：目前基本掌握了CPU访问DS18B20的三步骤,但是细节不够详细
              要结合手册中的操作流程图才可以
    
    7.就以CPU获取DS18B20采样的温度为例,整个流程如下：
    1.CPU向总线发送初始化复位信号
      ds18b20_rest();
    2.CPU向总线发送SKIP ROM命令(0xCC)//不用匹配
      ds18b20_write8(0xcc);
    3.CPU首先向设备发送温度转换命令0x44,DS18B20硬件自动
      启动温度的采集,采集完毕,自动将温度值放在byte0,byte1
      ds18b20_write8(0x44);
    4.CPU再次向总线发送初始化复位信号
      ds18b20_rest();
    5.CPU向总线发送SKIP ROM命令(0xCC)//不用匹配
      ds18b20_write8(0xcc);
    6.CPU向设备发送读取RAM数据的命令0xBE
      ds18b20_write8(0xbe);
    7.CPU开始读取byte0数据
      templ = ds18b20_read8();
    8.CPU再读取byte1数据
      temph = ds18b20_read8();
    9.至此采集的温度读取到了,换算处最后的实际温度
      temp = (temph << 8 | templ) * 625;   		  

3.软件设计
  3.1.掌握硬件特性以后,编写DS18B20的设备驱动
  参考驱动：drivers.tar.bz2/ds18b20
  			   ds18b20_drv.c //驱动
  			   ds18b20_test.c //测试程序
  1.先运行品味驱动的采集温度
    make
    arm-linux-gcc -o ds18b20_test ds18b20_test.c 
    cp ds18b20_test ds18b20_drv.ko /opt/rootfs/home/drivers/
    开发板测试：
    insmod /home/drivers/ds18b20_drv.ko
    ls /dev/ds18b20 -lh
    /home/drivers/ds18b20_test //每隔一秒钟打印温度
    手摸一下,吹一下
  
  2.编写DS18B20驱动
    mkdir /opt/project/drivers/ds18b20
    cd /opt/project/drivers/ds18b20
    vim ds18b20_drv.c
    vim Makefile
    make
    cp ds18b20_drv.ko /opt/rootfs/home/drivers
  
  3.2.先画出整个温度采集显示的软件框架图
      编写ds18b20硬件操作库
      参考代码：hwlib.tar.bz2/ds18b20
      			      ds18b20.h //声明
      			      ds18b20.c //定义
      			      ds18b20lib_test.c //测试用例
      mkdir /opt/project/hwlib/ds18b20
      cd /opt/project/hwlib/ds18b20
      vim ds18b20.h
      vim ds18b20.c
      vim ds18b20lib_test.c 
      arm-linux-gcc -shared -fpic -o libds18b20.so ds18b20.c
      arm-linux-gcc -o ds18b20lib_test ds18b20lib_test.c -L. -lds18b20
      cp libds18b20.so /opt/rootfs/home/applib
      cp ds18b20lib_test /opt/rootfs/home/apptest
      
      开发板测试：
      insmod /home/drivers/ds18b20_drv.ko
      /home/apptest/ds18b20lib_test
      
  3.3.在ehome图形界面添加温度显示,每隔5秒显示一次
  0.参考代码：ehome_ds18b20.tar.bz2
  1.利用qtcreator打开mainwindow.ui文件,添加元素
    当前室内温度：25摄氏度
      QLabel       QLabel
  2.利用qtcreator打开mainwindow.h文件，添加
    #include "ds18b20.h" 
    在Mainwindow类中添加:
    QTimer *timer; //利用timer定时器实现每隔5秒读取温度
    int m_fd_ds18b20; //ds18b20设备文件描述符
  3.利用qtcreator打开mainwindow.cpp文件，添加
    在构造函数中调用库函数打开设备
    m_fd_ds18b20 = ds18b20_open();
    
    还要添加定时器的超时对应的槽函数
  
  4.在定时器超时以后要执行的槽函数中,调用库函数获取温度
    并且在QLabel中显示
    struct ds18b20_cmd ds18b20;
    ds18b20_read(...);
    qlabel->setText(显示);  
  
  5.编译
    cd /opt/project/ehome/
    vim ehome.pro 添加ds18b20头文件和库的支持
    INCLUDEPATH += /opt/project/hwlib/ds18b20
    LIBS += -L/opt/project/hwlib/ds18b20 -lds18b20
    保存退出
    /opt/project/qt/bin/qmake //重新生成Makefile
    make
    cp ehome /opt/rootfs/home/appbin
    
    开发板测试           
                       
