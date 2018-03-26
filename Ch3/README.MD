# Chapter 3 总结
## 目录
目录和文件一样可以有系统调用操作，用opendir，readdir等。opendir会用到dirent结构体，readdir得到的文件信息只有一部分，需要用stat来查看详细信息。这里和Ch2类似。

## 文件模式
12位二进制，前4位文件类型，应该是普通文件，目录，软链接等的区分。后3为suid, sgid, sticky。最后9位表明权限。可以用or和and进行解码。suid是告诉内核，运行这个程序(可执行文件？）时认为是文件的所有者在运行，用来给某些程序提供额外权限。有suid的时候，user位的权限会变成rws。sgid与suid类似。sticky是对于文件是说这个程序会一直停留在交换空间中，对于目录是说目录中的文件只能被创建者删除。

不同的文件类型文件用不同的函数创建，例如create创建普通文件，文件类型不能修改。文件许可权限和特殊模式在文件创建的时候确立。umask会关闭某些权限位，系统调用chmod可以改变文件的模式，而且chmod不受新建文件解码的影响。Shell命令chmod也可以完成操作。系统调用chown和Shell命令chown，chgrp可以修改文件所有者和组。

时间:utime/touch(shell) 文件名修改:rename
