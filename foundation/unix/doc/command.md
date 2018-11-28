[linux工具快速教程](https://github.com/lanxuezaipiao/linuxtools_rst)

[TOC]
<!-- vim-markdown-toc GFM -->
* [查找](#查找)
    * [Find](#find)
        * [日常](#日常)
        * [常用选项](#常用选项)
    * [GREP](#grep)
        * [日常](#日常-1)
        * [常用选项](#常用选项-1)
        * [AWK](#awk)
* [网络](#网络)
    * [nmap](#nmap)
* [其他](#其他)
    * [crontab](#crontab)
    * [弹出通知](#弹出通知)
    * [文件大小](#文件大小)
* [日常](#日常-2)
    * [MD5](#md5)
    * [生成密码](#生成密码)
    * [拆分大文件](#拆分大文件)

<!-- vim-markdown-toc -->


# 查找

## Find

### 日常

查找某目录及子目录下的文件
```
find directory options criteria_to_match action_to_perform_on_results
```

删除当前目录及子目录下多有的.log文件
find . -name "*log" -print -exec rm -rf {} \;


### 常用选项

* -name  
> 按照文件名查找
```
find dir/ -name file_name # 在dir/目录及子目录下查找
find . -name "*.py" # 在当前目录及子目录下查找扩展为py的文件
find ./ -name "*.o" -exec rm {} \ # 删除当前目录及其子目录下的所有.o文件
```

* -perm  
> 按照文件权限来查找
```
find . -perm 755 -print # 在当前目录下查找权限为755的文件
```

* -regex
> 正则方式查找, -iregex忽略大小写的正则
```
find . -regex ".*\(\.txt|\.pdf\)$"
```

* -print  
> find命令将匹配到的文件输出到标准输出

* -prune(删减)  
> 在A文件夹内,不包含B文件夹中查找;如果同时使用-depth,那prune会被find命令忽略
```
find /apps -path "/apps/bin" -prune -o -print # 在/apps下,但不在/apps/bin内查找
```

* -newer file1 ! file2
> 查找更改时间比file1新但比file2旧的文件
```
find -newer file1 ! # 查找比file1新的文件
```

* -type  
> 查找某一类型的文件
```
b 块设备文件; d 目录
c 字符设备文件; p 管道文件
l 符号链接文件; f 普通文件
```

* -depth  
> 首先在当前目录查找,再在子目录中查找
```
find / -name "CON.FILE" -depth -print
```

* -follow  
> 如果查找到符号链接文件,就跟中所指向的文件

* -mtime -n +n  
(modify_time) 按照文件更改时间查找;+n/-n 表示文件更改时间距现在n天 前/内.
```
find / -mtime -5 -print #在根目录下查找更改时间在5日以内的文件
```

* -user  
> 按照文件属主来查找
```
find ~ -user kepler -print # 在$HOME下查找属于kepler的文件
```

* -nouser  
> 查找无有效属主的文件
```
find /home -nouser -print
```

* -group  
> 按照文件属组来查找  
```
find /apps -group kepler_group -print # 在/apps目录下查找属于kepler_group用户组的文件
```

* -nogroup  
> 查找无有效所属组的文件 ``` find / -nogroup -print

* -exec 与 xargs  



## GREP

### 日常

* 在当前目录及当前目录下的子目录查找某个字符串
```
grep -rn "test" *
```

* 全面搜索正则表达式pattern并把匹配的行打印出来
```
grep [OPTION] 'pattern' [FILE]
```

### 常用选项

* 以str开始/结尾
```
^str:以str开始
str$:以str结尾
```

* -n
> 同时显示匹配航的上下的n行 ``` grep -2 pattern filename ```

* -b
> byte offset 显示匹配行所在的行号

* -c
> count 显示匹配的行数有多少,不显示匹配的内容

* -v
> 反转

* -f
> file从文件中提取模板

* -i
> ignore-case 忽略大小写

* -h

* -l
> files-with-matchs显示**包含匹配内容**的文件名

* -L
> 显示**不包含匹配内容**的文件名

* -r
> 递归查找文件夹内的所有文件

* -s
> silent 不显示关于不存在或无法读物文件之类的错误信息


### AWK




# 网络

## nmap
端口扫描

* -sP Ping扫描
> 对某个或某段ip进行ping扫描
```
nmap -sP 10.21.125.154
nmap -sP 10.21.125.154-255
```

* -sU UDP扫描
>
```
sudo nmap -sU 10.21.125.154
```

* -sT TCP扫描


# 其他

* 只看前/后10行
```
$head/tail - 10 file_name
```

* 清空文件
```
$:>a.txt
```

* 查看磁盘空间大小
```
$ df -h
```

* 查看当前目录所站空间大小
```
$du -sh
```


## crontab


[cron表达式生成器](cron.qqe2.com)

```
 For details see man 4 crontabs
 Example of job definition:
 .---------------- minute (0 - 59)
 |  .------------- hour (0 - 23)
 |  |  .---------- day of month (1 - 31)
 |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
 |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
 |  |  |  |  |
 *  *  *  *  * user-name  command-to-be-executed
 *,*/5 9-16 * 1-5,9-12 1-5 root command
 在1到5月,9到12月每周周一到周五的9点到16点之间每5分钟执行一次
 星号（*）：代表所有可能的值，例如month字段如果是星号，则表示在满足其它字段的制约条件后每月都执行该命令操作。
 逗号（,）：可以用逗号隔开的值指定一个列表范围，例如，“1,2,5,7,8,9”
 中杠（-）：可以用整数之间的中杠表示一个整数范围，例如“2-6”表示“2,3,4,5,6”
 正斜线（/）：可以用正斜线指定时间的间隔频率，例如“0-23/2”表示每两小时执行一次。同时正斜线可以和星号一起使用，例如*/10，如果用在minute字段，表示每十分钟执行一次。
 m h dom mon dow user	command
17 *	* * *	root    cd / && run-parts --report /etc/cron.hourly
25 6	* * *	root	test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.daily )
47 6	* * 7	root	test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.weekly )
52 6	1 * *	root	test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.monthly )
```

## 弹出通知
notify-send
```
notify-send "标题" "通知内容"
```

## 文件大小
* du (disk usage)
```
 - a 显示全部目录和子目录下每个文件所占磁盘空间
 - s 只显示各档案大小的总合
 - b 大小用bytes来显示
```

# 日常

* ls -l | grep "^-" | wc -l # 统计当前文件夹下文件的个数 / 若要统计目录个数，将"^-"改为"^d"
* ls -lR | grep "^-" | wc -l # 统计当前文件夹下文件的个数(包括子文件夹内)
 
## MD5

* 获取字符串的md5: $echo -n "hellofasjdfas" | md5sum
* 获取文件的md5: $md5sum file_name
* 用md5校验文件：
```
$ md5sum file_name > file_name.md5  //输出md5值到.md5
$ md5sum -c file_name.md5           //把.md5和文件放在同一目录下
```

## 生成密码



## 拆分大文件

拆分大体积的文件(每个100MB)，然后合并回去：
```
split –b 100m /path/to/large/archive /path/to/output/files
cat files* > archive
```


* netstat -an | grep port_


* 移动/复制文件时排除某一文件/文件夹
