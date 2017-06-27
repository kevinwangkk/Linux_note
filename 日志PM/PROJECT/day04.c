项目第五天任务安排：通过ehome图形界面实现软件的在线升级
                    类似小米手机软件升级通过网络和本地升级
实施步骤：
1.用户需求分析
  以升级TPAD上的zImage为例
  软件的在线升级的方法有两种：
  网络升级：下位机利用网络从服务器上下载要升级的软件,最终
            将新的软件替代原先的老的软件
            画图
            结论：
            1.从服务器利用网络编程下载要升级的zImage到Nand
              上某个分区上
            2.利用某些软件将Nand进行擦除和写入
            
  本地升级：利用U盘或者SD完成本地升级,首先客户自行到服务器
             上下载要升级的软件zImage到U盘或者SD卡;
             将U盘或者SD卡插入到TPAD上,嵌入式linux系统能够
             识别U盘或者SD卡,最后将U盘或者SD卡上的软件更新到
             对应的位置
             画图
            总结：
            1.如何让TPAD识别U盘上的文件
            2.如果在uboot的命令不能使用的前提下
              擦除和写入数据到Nand上
            
2.软件设计
  此项目选择本地升级方式来升级zImage
  2.1.明确,关键的技术点
  1.如何让TPAD识别U盘
  2.如何擦和写Nand
  
  2.2.手动玩U盘,在TPAD上
  实施步骤：
  开发板操作：
  1.TPAD上linux系统正常启动
  2.将zImage拷贝到U盘上,将U盘插入到TPAD的USB口
    观察打印信息,获取到U盘的设备文件(sda1,sda4,sdb4...)
    类似一下信息：
    sda: sda4 //说明U盘的设备文件为sda4
    
    如果再插入一个U盘,又会出现打印信息,类似以下信息：
    sdb: sdb4 //说明第二块U盘的设备文件为sdb4
  3.手动挂接U盘到根文件系统rootfs某个目录上
    mount -t vfat /dev/sda4 /mnt   
    说明：
    将U盘(sda4)挂接到mnt目录,并且指定的文件系统类型为FAT32
    一旦挂接成功将来访问mnt目录就是在访问U盘
    
    cd /mnt //进入U盘
    ls  //查看U盘的文件
      zImage
  4.如果拔掉U盘,先去卸载U盘
    cd /  //务必先从U盘中退出来,退出mnt目录
    umount /mnt //卸载U盘
    ls /mnt //还能看到U盘的zImage？
 
 2.3.自动挂接和卸载U盘
 实施步骤：
 1.只需一个配置文件和两个脚本文件即可
   project.rar/usb.tar.bz2/
   			mdev.conf:配置文件
   			usb_insert.sh:挂接使用的脚本
   			usb_remove.sh:卸载使用的脚本
 2.给rootfs添加mdev.conf配置文件
   cp mdev.conf /opt/rootfs/etc/ 
   
   mdev.conf说明：
   插入U盘时执行：
   sd[a-z][0-9] 0:0 666 @/home/usb/usb_insert.sh /dev/$MDEV 
   
   拔出U盘时执行：
   sd[a-z] 0:0 666 $/home/usb/usb_remove.sh   			   
   
   第一列：U盘的设备文件,利用正则表达式
   第二列：用户：组
   第三列：访问权限
   第四列：
   	  @：插入U盘以后要执行的命令/home/usb/usb_insert.sh
   	  $: 拔出U盘之前要执行的命令/home/usb/usb_remove.sh
   第五列：
   	 /dev/$MDEV:给脚本传递的参数
   	 	    $MDEV就是U盘的设备文件sda4
   	 	    /dev/$MDEV=/dev/sda4
 
 3.给rootfs添加两个脚本
   mkdir /opt/rootfs/home/usb
   mkdir /opt/rootfs/mnt/usb 
   
   cp usb_insert.sh /opt/rootfs/home/usb
   cp usb_remove.sh /opt/rootfs/home/usb
   chmod 777 /opt/rootfs/home/usb/ *   	 	    
  
 4.开发板测试
   1.重启TPAD
   2.插入U盘,查看U盘是否自动完成挂接,只需执行：
     mount  //查看一下类似信息：
     /dev/sda4 on /mnt/usb //表明挂接成功
     cd /mnt/usb //进入U盘
     ls //查看U盘的内容
   3.拔出U盘
     cd / //务必先退出U盘
     拔出U盘
     mount //查看是否还有以下信息：
     /dev/sda4 on /mnt/usb //应该消失不见  
    
  2.4.问：如何在嵌入式linux系统正常运行的情况下(uboot早已结束)
          能对Nand某个分区进行擦除和写入操作呢？
      答：移植Nand的操作工具(命令)对应的开源软件
  实施步骤：
  1.获取源码：project.rar/mtd-utils-mtd-utils.tar
    
  2.源码操作
    mkdir /opt/project/mtd/
    cp mtd-utils-mtd-utils.tar.bz2 /opt/project/mtd
    cd /opt/project/mtd
    tar -xvf mtd-utils-mtd-utils.tar.bz2
    cd mtd-utils-mtd-utils //进入工具的源码根目录
    make //编译,生成一个arm-linux新目录
    cd arm-linux
    ls 
    	flash_erase:擦除Nand命令
    	nandwrite:写Nand命令
    	nanddump:读Nand命令
    
  3.拷贝到rootfs
    cp nandwrite /opt/rootfs/sbin 	
    cp flash_erase /opt/rootfs/sbin                                     
  
  4.开发板上手动擦除和写入zImage到Nand上
    开发板执行：
    cat /proc/mtd //查看Nand的分区信息
    mtd0:... .... "uboot"
    mtd1:... .... "kernel"
    mtd2:... .... "rootfs"
    mtd3:.. ..... "userdata"
    说明：zImage存在Nand的第二分区mtd1
    
    ls /dev/mtd* -lh //查看Nand的分区设备文件
    mtd0:第一分区的字符设备文件
    mtdblock0:第一分区的块设备文件
    mtd1:第二分区的字符设备文件
    mtdblock1:第二分区的块设备文件
    ...
    
    切记：nand的操作命令flash_erase,nandwrite只针对Nand字符设备文件
    
    flash_erase /dev/mtd1 0 0 //将zImage所在的分区mtd1全部擦除
    nandwrite -p /dev/mtd1 /mnt/usb/zImage //将U盘中的zImage写入到第二分区mtd1
    					   //前提是U盘挂接成功
    					   
    注意：以后升级不可能让用户操作以上命令,需要通过点击界面自动完成
  
  2.5.编写升级软件操作库
      参考代码：hwlib.tar.bz2/update_kernel
  2.6.编写ehome图形界面,添加升级按钮,当用户点击按钮
      自动将U盘中的zImage写入到Nand上
      参考代码：ehome_update_kernel.tar.bz2					   
    			
