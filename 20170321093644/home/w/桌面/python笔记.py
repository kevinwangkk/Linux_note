
在面向过程的语言中，程序是由过程或仅仅是可重用代码的函数构建起来的。
在面向对象的语言中，程序是由数据和功能组合而成的对象构建起来的。
#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
print 打印字符串 遇到 ',' 变成空格 
	>>> print "helod,dd","wwww"
	helod,dd wwww

>>> print '100 + 200 =', 100 + 200
100 + 200 = 300

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
输入
>>> name = raw_input()
Michael

>>> name  #再次输入name 将之前存放的变量输出
'Michael'

>>> print name   #还可以print 打印变量值
Michael

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

Python程序是大小写敏感的，如果写错了大小写，程序会报错。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

在Python中有4种类型的数——整数、长整数、浮点数和复数。

●      2是一个整数的例子。
●      长整数不过是大一些的整数。
●      3.23和52.3E-4是浮点数的例子。E标记表示10的幂。在这里，52.3E-4表示52.3 * 10-4。
●      (-5+4j)和(2.3-4.6j)是复数的例子。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

# 运算符
运算符 名称 说明 例子
+ 加 
	两个对象相加 
		3 + 5得到8。'a' + 'b'得到'ab'。
- 减
	得到负数或是一个数减去另一个数
		-5.2得到一个负数。50 - 24得到26。
* 乘
	两个数相乘或是返回一个被重复若干次的字符串
		2 * 3得到6。'la' * 3得到'lalala'。
** 幂
	返回x的y次幂
		3 ** 4得到81（即3 * 3 * 3 * 3）
/ 除 
	x除以y
		4/3得到1（整数的除法得到整数结果）。
		4.0/3或4/3.0得到1.3333333333333333
// 取整除 
	返回商的整数部分 
		4 // 3.0得到1.0
% 取模 
	返回除法的余数 
		8%3得到2。-25.5%2.25得到1.5 # -12*2.25+1.5
<< 左移
	把一个数的比特向左移一定数目（每个数在内存中都表示为比特
	或二进制数字，即0和1）
		2 << 2得到8。——2按比特表示为10
>> 右移 
	把一个数的比特向右移一定数目
		11 >> 1得到5。——11按比特表示为1011，向右移动1比特后得
		到101，即十进制的5。
& 按位与 
	数的按位与 	
		5 & 3得到1。
| 按位或 
	数的按位或 
		5 | 3得到7。
^ 按位异或 
	数的按位异或 
		5 ^ 3得到6
~ 按位翻转 
	x的按位翻转是-(x+1) 	
		~5得到-6。
< 小于
	返回x是否小于y。
	所有比较运算符返回1表示真，返回0表示假。
	这分别与特殊的变量True和False等价。注意，这些变量名的大写。
		5 < 3返回0（即False）而3 < 5返回1（即True）。
		比较可以被任意连接：3 < 5 < 7 返回True。
> 大于 
	返回x是否大于y
		5 > 3返回True。
		# 如果两个操作数都是数字，它们首先被转换为一个/共同的类型/。
		否则，它总是返回False。
<= 小于等于 
	返回x是否小于等于y 
		x = 3; y = 6; x <= y返回True。
>= 大于等于 
	返回x是否大于等于y 
		x = 4; y = 3; x >= y返回True。
== 等于 
	比较对象是否相等
		x = 2; y = 2; x == y返回True。
		x = 'str'; y = 'stR'; x == y返回False。
		x = 'str'; y = 'str'; x == y返回True。
!= 不等于 
	比较两个对象是否不相等 
		x = 2; y = 3; x != y返回True。
not 布尔“非”
	如果x为True，返回False。如果x为False，它返回True。
		x = True; not y返回False。
and 布尔“与”
	如果x为False，x and y返回False，否则它返回y的计算值。
		x = False; y = True; x and y，由于x是False，返回False。
		在这里，Python不会计算y，因为它知道这个表达式的值肯定是False
		（因为x是False）。这个现象称为短路计算。
or 布尔“或”
	如果x是True，它返回True，否则它返回y的计算值。
		x = True; y = False; x or y返回True。短路计算在这里也适用。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

# 运算符优先级    从最低的优先级（最松散地结合）到最高的优先级（最紧密地结合）
	运算符 			描述
	lambda 			Lambda表达式
	or 			布尔“或”
	and 			布尔“与”
	not x 			布尔“非”
	in，not in 		成员测试
	is，is not 		同一性测试
	<，<=，>，
	>=，!=，==		比较
	| 			按位或
	^ 			按位异或
	& 			按位与
	<<，>> 			移位
	+，- 			加法与减法
	*，/，%			乘法、除法与取余
	+x，-x 			正负号
	~x 			按位翻转
	** 			指数
	x.attribute 		属性参考
	x[index] 		下标
	x[index:index] 		寻址段
	f(arguments...) 	函数调用
	(experession,...) 	绑定或元组显示
	[expression,...] 	列表显示
	{key:datum,...} 	字典显示
	'expression,...' 	字符串转换

# 运算符通常由左向右结合
#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

在逻辑行首的空白（空格和制表符）用来决定逻辑行的缩进层次，从而用来决定语句的分组。
这意味着同一层次的语句必须有相同的缩进。

if 控制流

  1 # coding:utf-8
  2 number= 23
  3 guess = int(raw_input("Enter integer:")) # 类似于强转
  4 
  5 if guess==number:
  6     print "="
  7 elif guess < number:
  8     print "<"
  9 else:
 10     print ">"
 11 
 12 print "done"

#注意if语句在结尾处包含一个冒号——我们通过它告诉Python下面跟着一个语句块。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

while 控制流

  1 # coding:utf-8
  2 
  3 number = 23
  4 running=True
  5 
  6 while running:
  7     guess=int(raw_input("Enter integer:"))
  8     if guess==number:
  9         print "="
 10         running=False
 11     elif guess<number:
 12         print "<"
 13     else:
 14         print ">"
 15 else:
 16     print "the while loop is over"
 17 print "done"

多行注释 三个单引号
'''
当while循环条件变为False的时候，else块才被执行——这甚至也可能是在条件第一次被检验的
时候。如果while循环有一个else从句，它将始终被执行，除非你的while循环将永远循环下去不
会结束！
'''
else块事实上是多余的，因为你可以把其中的语句放在同一块（与while相同）中，跟在while语
句之后，这样可以取得相同的效果。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

for 控制流   for..in

  1 
  2 for i in range(1,5):
  3     print i
  4 else:
  5     print "the for loop is over"


#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

#内建函数range
range返回一个序列的数。
这个序列从第一个数开始到第二个数
为止。例如，range(1,5)给出序列[1, 2, 3, 4]。默认地，range的步长为1。
如果我们为range提供第三个数，那么它将成为步长。
例如，range(1,5,2)给出[1,3]。记住，range 向上 延伸到第二个数，即它不包含第二个数。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

break 

  1 while True:
  2     s=raw_input("Enter something:" )
  3     if s=='quit':
  4         break
  5     print "length of the string is ",len(s)    # 内建函数len
  6 print "Done"

Enter something:222
length of the string is  3
Enter something:wang
length of the string is  4
Enter something:quit
Done

continue 和C 一样
#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

函数

  1 def say_hello():
  2     print "Hello"
  3 
  4 say_hello() # call the function

Hello

带参函数

  1 def max(a,b):
  2     if a<b:
  3         print b,"is maximum"
  4     else:
  5         print a,"is maximum"
  6 
  7 max(4,7)
  8 
  9 x=10
 10 y=9
 11 max(x,y)

7 is maximum
10 is maximum

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

局部变量

	所有变量的作用域是它们被定义的块，从它们的名称被定义的那点开始  # 被定义的块

  1 def func_local(x):
  2     print "x is",x
  3     x=2
  4     print "change local x to",x
  5 
  6 x=9
  7 func_local(x)
  8 print "x is still",x
  9 

x is 9
change local x to 2
x is still 9


#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

全局变量 global 

  1 def func_global():
  2     global x
  3 
  4     print "x is",x
  5     x=2
  6     print "change local x to",x
  7 
  8 x=50
  9 func_global()
 10 print "x is",x,"now"

x is 50
change local x to 2
x is 2 now

可以使用同一个global语句指定多个全局变量。例如global x, y, z。
#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

默认参数值

  1 def func_defult(message,time=1):
  2     print message*time
  3 
  4 func_defult("hello")
  5 func_defult("hello",5)

hello
hellohellohellohellohello

只有在形参表末尾的那些参数可以有默认参数值，即你不能在声明函数形参的时候，先声明有
默认值的形参而后声明没有默认值的形参。
这是因为赋给形参的值是根据位置而赋值的。例如，def func(a, b=5)是有效的，
但是def func(a=5, b)是无效的。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

关键参数
如果你的某个函数有许多参数，而你只想指定其中的一部分，那么你可以通过命名来为这些参
数赋值——这被称作 关键参数 ——我们使用名字（关键字）而不是位置（我们前面所一直使
用的方法）来给函数指定实参。

  1 def func_key(a,b,c=9):
  2     print "a is",a,"and b is",b,"and c is",c
  3 
  4 func_key(10,11)
  5 
  6 func_key(b=11,a=10)

a is 10 and b is 11 and c is 9
a is 10 and b is 11 and c is 9


#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

return

  1 def Max(x,y):
  2     if x>y:
  3         return x
  4     elif x<y:
  5         return y
  6 print Max(7,9)

9

没有返回值的return语句等价于return None。None是Python中表示没有任何东西的特殊类型。
例如，如果一个变量的值为None，可以表示它没有值。
除非你提供你自己的return语句，每个函数都在结尾暗含有return None语句。
通过运行print someFunction()，你可以明白这一点，
函数someFunction没有使用return语句，如同：
def someFunction():
    pass 
pass语句在Python中表示一个空的语句块。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

DocStrings 文档字符串

  1 def print_max(x,y):
  2     '''Print the maximum of two numbers.
  3 
  4     The two numbers must be integers.'''
  5 
  6     x=int(x)
  7     y=int(y)
  8 
  9     if x<y:
 10         print y,"is the maximum"
 11     elif x>y:
 12         print x,"is the maximum"
 13 print print_max.__doc__
 14 print_max(3,9)

Print the maximum of two numbers.

    The two numbers must be integers.
9 is the maximum

文档字符串的惯例是一个多行字符串，它的首行以大写字母开始，句号结尾。第二行是空行，
从第三行开始是详细的描述。 强烈建议 你在你的函数中使用文档字符串时遵循这个惯例。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

help()   
帮助文档  和man类似

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

模块

import sys

dir


#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

数据结构
在Python中有三种内建的数据结构——列表、元组和字典。

#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××



#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××



#×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

















































































































































