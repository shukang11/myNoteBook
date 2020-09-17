# tmux 常用命令

#### 基本

* 开启 `tmux`

* 关闭 `ctrl+d` 或者 `exit`

* 前缀命令 `ctrl+b` 所有的快捷键都需要前缀命令唤起

* 查询所有会话 `tmux ls` 或者 `ctrl+b s`


#### 会话管理

* 新建一个会话 `tmux new -s <session-name>`

* 分离会话 `tmux detach` 或者 `ctrl+b d`

* 接入会话 `tmux attach -t <session-name>`

* 杀死会话 `tmux kill-session -t <session-name>`

* 切换会话 `tmux switch -t <session-name>`

* 重命名会话 `tmux rename-session -t <old-session-name> <new-session-name>` 或者 `ctrl+b $`


#### 窗格管理


* 划分上下两个窗格 `tmux split-window` 或者 `ctrl+b "`

* 划分左右两个窗格 `tmux split-window -h`  或者 `ctrl+b %`

* 当前窗格上移 `tmux swap-pane -U` 或者 `ctrl+b {`

* 当前窗格下移 `tmux swap-pane -D` 或者 `ctrl+b }`

* 关闭当前窗格 `ctrl+b x`

* 窗格切换全屏 `ctrl+b z`


#### 窗口管理

* 创建新窗口 `tmux new-window` 或者 `ctrl+b c`


# Ref

* [Tmux 使用教程](http://www.ruanyifeng.com/blog/2019/10/tmux.html)