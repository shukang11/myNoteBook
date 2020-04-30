#python 笔记

##  pyenv 离线安装

` cd ~/.pyenv/ && mkdir cache/`

下载安装包

`wget https://www.python.org/ftp/python/3.5.4/Python-3.5.4.tar.xz `

安装 ` pyenv install 3.5.4 `


### 常用命令
1. 虚拟环境
* pipenv virtualenv
 - 创建虚拟环境 `pyenv virtualenv <env-name>`
 - 查看环境列表 `pyenv virtualenvs`
 - 激活环境 `pyenv activate <name>`
 - 退出环境 `pyenv deactivate`
 - 删除环境 `pyenv uninstall <env-name>`

* virtualenv
 - 创建虚拟环境 `virtualenv --no-site-packages <env-name>`
 - 激活环境 `source <env-name>/bin/activate`
 - 退出环境 `deactivate`

* conda
 - 创建虚拟环境 `conda create -n <env-name> python=<version>`
 - 安装到某个环境 `conda install --name <env-name> <package>`
 - 激活环境 `source activate <env-name>`
 - 退出环境 `source deactivate`


## jupyter

安装好之后 

启动 `jupyter notebook` 启动