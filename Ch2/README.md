# Chapter 2 总结
## 用户相关
who命令通过读系统日志的内容显示当前已经登陆的用户，这个系统日志是utmp和wtmp,在头文件<utmp.h>中定义了日志的目录和结构体utmp可以用来读取记录。里面的时间是从1970年到现在的秒数，可以用ctime这个系统调用来处理。
具体可以用联机查询阅读手册。

whoami.c里面用的是<passwd.h>，应该与下一章的ls比较相关。

## 文件系统
包括一系列的系统调用：open， close， creat， read， write， lseek。这些都是需要文件描述符来操作的。

在编写cp时对文件的是否存在和是否相同是通过access和stat系统调用实现的。也许还有别的更好的实现方法。因为在cp_with_option.c中关于是否存在和是否相同需要
三次系统调用，如果有什么方法可以减少系统调用的次数就好了。

## 缓冲
使用缓冲可以减少系统调用的次数，提高程序的效率。

## 系统调用中的错误
全局变量errno用来指明错误的类型，perror会自动查找errno对应的错误,在**标准错误**输出中显示相应的错误信息。

## 带有参数的命令
需要调用getopt，简单的使用可以随意参见一些技术博客。这里有一个比较详细的，[使用getopt()进行命令行参数处理](https://www.ibm.com/developerworks/cn/aix/library/au-unix-getopt.html)
