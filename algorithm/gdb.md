** gcc -g -o a.debug a.c **
** gdb a.debug **

在我的vim里直接Ctrl+r

####运行
`(gdb)r`

####断点
* 断点 `(gdb)break line_n/func_name`
* 清除断点 `(gdb)clear n`
* 查看断点情况 `(gdb)info break`

####单步
* 不进入函数 `(gdb)n`
* 进入函数 `(gdb)s`
* 恢复正常 `(gdb)c`

####查看变量
`(gdb)p argv_name`
