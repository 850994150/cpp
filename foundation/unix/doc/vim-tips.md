## vim-tips
* 查找替换
 * 全局替换：%s/old/new/g

* 相对行号
`set relativenumber`

## cvim
```
I    search history
b    search bookmarks
ctrl+k    地址栏google快速搜索
T    新tab打开当前页面
```

|command |[vim使用笔记](http://www.cnblogs.com/jiqingwu/archive/2012/06/14/vim_notes.html)|
|: ----- :|: ---- :|
| `gd` | 跳转到局部变量定义处|
| `''`  | (两个单引号) 跳转到上次停靠处
| `:earlier 10m` |  恢复到10分钟以前的状态
| `ge`  | 移动到上一个单词的词未
| ` + / - ` |  移到下/上一列第一个字符处
| `(/)` |  移到句首/句末
| `{/}` |  段首/段未
| `NG`  |  文件的第n列
| `N + /- ` |  移动光标位置之后/前第N列
| `.`   |  重做
| `:n`  |  跳到第n行
| `:Tx` |  移动到光标后第一个x处
| `ma`  | |
| `gv`  |  重新选择曾选择过的文本块
| `ctrl  +  g`|查看当前位置
| `g  +  ctrl  +  g` | 统计
| `q:`  | 显示输入过的命令历史
| `vim  - M file_name`  | 只读形式打开文件


## 常用命令


* 多行行首插入：   
```
按 Ctrl  +  v 进入列选择模式，选择需要行首插入的行
然后按 I，进入列插入状态，
输入星号 *，再按下 ESC
你会看到，所有行之前都出现了一个星号
```

* 多行行末插入：   
`Ctrl - v  +  $  +  A  +  想插入的字符  +  esc`

* [折叠命令](http://www.cnblogs.com/wangkangluo1/archive/2011/06/10/2077203.html)
* zc 折叠,只折叠最外层的折叠
* zo 展开,只展开最外层的折叠
* zC 对所在范围内所有嵌套的折叠点折叠，包括嵌套的折叠.
* zO 对所在范围内所有嵌套的折叠点展开，包括嵌套折叠.
