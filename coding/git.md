# git

## 遇到的问题

### git clone时，显示could not resolve host: github.com

使用git clone时，显示could not resolve host: github.com

在终端ping github.com时显示无法正常显示

解决方法：

- 在终端输入 sudo vim /private/etc/hosts
- 输入i进入编辑模式
- 增加映射域名140.82.114.4    github.com

再ping即有显示

<img src="/Users/wangluyao/Library/Application Support/typora-user-images/image-20220307225143342.png" alt="image-20220307225143342" style="zoom:50%;" />

也可以正常git clone

control+c停止



### The remote end hung up unexpectedly

问题来源，使用`git fetch --unshallow`时候显示

<img src="/Users/wangluyao/Downloads/RPC_failed.jpg" alt="RPC_failed" style="zoom: 50%;" />

原因在于，`--unshallow`命令表示获取全部分支的信息，即全部提交记录，显然，信息是非常大的，但只需要拉去一次的完整状态即可，可使用命令`git fetch --depth 1`



## git命令相关

### git fetch

用于从远程获取代码库

执行好`git fetch`后需要执行`git merge`远程分支到所在分支

`git merge`：从远程仓库提取数据并尝试合并到当前分支

> `git fetch`和`git pull`的区别