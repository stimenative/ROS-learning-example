# Ros学习笔记

## 一、环境搭建

### 1. 项目建立步骤（python）

##### step 1 创建工作空间

```shell
mkdir -p xxx_ws/src
cd xxx_ws
catkin_make
```

##### step 2 启动VSC

```shell
cd xxx_ws
code .
```

##### step 3 编译Ros

快捷键 ctrl + shift + B 调用编译，选择:`catkin_make:build`

可以点击配置设置为默认，修改`.vscode/tasks.json` 文件

```json
{
// 有关 tasks.json 格式的文档，请参见
    // https://go.microsoft.com/fwlink/?LinkId=733558
    "version": "2.0.0",
    "tasks": [
        {
            "label": "catkin_make:debug", //代表提示的描述性信息
            "type": "shell",  //可以选择shell或者process,如果是shell代码是在shell里面运行一个命令，如果是process代表作为一个进程来运行
            "command": "catkin_make",//这个是我们需要运行的命令
            "args": [],//如果需要在命令后面加一些后缀，可以写在这里，比如-DCATKIN_WHITELIST_PACKAGES=“pac1;pac2”
            "group": {"kind":"build","isDefault":true},
            "presentation": {
                "reveal": "always"//可选always或者silence，代表是否输出信息
            },
            "problemMatcher": "$msCompile"
        }
    ]
}

```

##### step 4 创建功能包

选定 src 右击 ---> create catkin package

添加包：`roscpp rospy std_msgs`

##### step 5 添加python文件

在 功能包 下新建 scripts 文件夹，添加 python 文件

```python
#! /usr/bin/env python

import rospy # 1.导包

if __name__ == "__main__":

    rospy.init_node("Hello_Vscode_p")  # 2.初始化 ROS 节点
    rospy.loginfo("Hello VScode, 我是 Python ....")  #3.输出格式
```

编写相关功能

##### step 6 添加可执行权限

```shell
chmod +x *.py
```

##### step 7 配置CMakelists.txt

修改包目录下的CMakelists.txt文件

```cmake
catkin_install_python(PROGRAMS
  scripts/diy_pub.py	#scripts/*.py
  scripts/diy_sub.py	
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
```

##### step 8 编译执行

编译: ctrl + shift + B

执行: 和之前一致，只是可以在 VScode 中添加终端，首先执行:`source ./devel/setup.bash`

或者在`~/.bashrc`中写入`source (path)/devel/setup.bash`

或者`echo "source ~/工作空间/devel/setup.bash" >> ~/.bashrc`



### 2. Ros命令

```shell
sudo apt install xxx  	# 安装 ROS功能包
sudo apt purge xxx    	# 删除某个功能包
rospack find pkg  	  	# 查找某个功能包是否存在，如果存在返回安装路径
roscore				  	# 启动 ros master、ros参数服务器、rosout日志节点
rosrun pkg .py 		  	# 运行指定的ROS节点
roslaunch pkg .launch 	# 执行某个包下的 launch 文件
rqt_graph				# 启动计算图
```



### 3. 建立launch文件

功能：同时启动roscore和多个节点，避免多次rosrun操作。

步骤：

- 选定功能包右击 ---> 添加 launch 文件夹

- 选定 launch 文件夹右击 ---> 添加 .launch 文件

- 编辑 launch 文件内容:

  ```xml
  <launch>
      <node pkg="helloworld" type="demo_hello" name="hello" output="screen" />
      <node pkg="turtlesim" type="turtlesim_node" name="t1"/>
      <node pkg="turtlesim" type="turtle_teleop_key" name="key1" />
  </launch>
  ```

     - node ---> 包含的某个节点
     - pkg -----> 功能包
     - type ----> 被运行的节点文件
     - name --> 为节点命名
     - output-> 设置日志的输出目标

- 运行launch文件

  `roslaunch 包名 launch文件名`

- 注意运行python文件时，属性`type="*.py"`



## 二、Ros通信机制

ROS 中的基本通信机制主要有如下三种实现策略:

- 话题通信(发布订阅模式)
- 服务通信(请求响应模式)
- 参数服务器(参数共享模式)



### 1. 话题通信

#### 1.1 理论模型

话题通信实现模型是比较复杂的，该模型如下图所示,该模型中涉及到三个角色:

- ROS Master (管理者)
- Talker (发布者)
- Listener (订阅者)

ROS Master 负责保管 Talker 和 Listener 注册的信息，并匹配话题相同的 Talker 与 Listener，帮助 Talker 与 Listener 建立连接，连接建立后，Talker 可以发布消息，且发布的消息会被 Listener 订阅。

<img src="http://www.autolabor.com.cn/book/ROSTutorials/assets/01%E8%AF%9D%E9%A2%98%E9%80%9A%E4%BF%A1%E6%A8%A1%E5%9E%8B.jpg" alt="img" style="zoom: 50%;" />

**流程：**

0. **Talker注册**：Talker启动后，会通过RPC在 ROS Master 中注册自身信息，其中包含所发布消息的话题名称。ROS Master 会将节点的注册信息加入到注册表中。

1. **Listener注册**：Listener启动后，也会通过RPC在 ROS Master 中注册自身信息，包含需要订阅消息的话题名。ROS Master 会将节点的注册信息加入到注册表中。

2. **ROS Master实现信息匹配**：ROS Master 会根据注册表中的信息匹配Talker 和 Listener，并通过 RPC 向 Listener 发送 Talker 的 RPC 地址信息。

3. **Listener向Talker发送请求**：Listener 根据接收到的 RPC 地址，通过 RPC 向 Talker 发送连接请求，传输订阅的话题名称、消息类型以及通信协议(TCP/UDP)。

4. **Talker确认请求**：Talker 接收到 Listener 的请求后，也是通过 RPC 向 Listener 确认连接信息，并发送自身的 TCP 地址信息。

5. **Listener与Talker件里连接**：Listener 根据步骤4 返回的消息使用 TCP 与 Talker 建立网络连接。

6. **Talker向Listener发送消息**：连接建立后，Talker 开始向 Listener 发布消息。



#### 1.2 基本操作（python）

ROS 中通过 `std_msgs` 封装了一些原生的数据类型

- `int8, int16, int32, int64` (或者无符号类型: `uint*`)
- `float32, float64`
- `string，char，bool，empty`
- `time, duration`
- other `msg files`
- `variable-length array[] and fixed-length array[C]`
- `Header`

##### 发布方

实现流程:

1.  导包 
2.  初始化 ROS 节点:命名(唯一)
3.  实例化 发布者 对象
4.  组织被发布的数据，并编写逻辑发布数据

```python
#! /usr/bin/env python
# 1.导包 
import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    
    # 2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("talker_p")
    # 3.实例化发布者 （名称，类，参数）
    pub = rospy.Publisher("chatter",String,queue_size=10)
    # 4.组织被发布的数据，并编写逻辑发布数据
    msg = String()  		# 创建 msg 对象
    msg_front = "hello 你好"
    count = 0  				# 计数器 
    rate = rospy.Rate(1)    # 设置循环频率 # Hz
    while not rospy.is_shutdown():
    	msg.data = msg_front + str(count)	# 拼接字符串
    	pub.publish(msg)
    	rate.sleep()
    	rospy.loginfo("写出的数据:%s",msg.data)
    	count += 1
```

##### 订阅方

```python
#! /usr/bin/env python
#1.导包 
import rospy
from std_msgs.msg import String

def doMsg(msg):				# 定义消息处理函数
    rospy.loginfo("I heard:%s",msg.data)

if __name__ == "__main__":
    #2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("listener_p")
    #3.实例化 订阅者 对象
    sub = rospy.Subscriber("chatter",String,doMsg,queue_size=10)
    #4.处理订阅的消息(回调函数)
    #5.设置循环调用回调函数
    rospy.spin()
```



#### 1.3 自定义消息

**流程:**

1. 按照固定格式创建 `msg` 文件
2. 编辑配置文件
3. 编译生成可以被 Python 或 C++ 调用的中间文件

##### step 1 定义msg文件

功能包下新建 msg 目录，添加文件 `xxx.msg`

```
string name
uint16 age
float64 height
```

##### step 2 编辑配置文件

在`package.xml`中添加编译依赖和执行依赖

```xml
<build_depend>message_generation</build_depend>		<!--编译时使用的依赖项-->
  
<exec_depend>message_runtime</exec_depend>			<!--运行时使用的依赖项-->
```

`CMakeLists.txt`编辑 msg 相关配置

```cmake
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation		# 编译加入message_generation包
)
```

```cmake
add_message_files(
  FILES
  Person.msg				# 添加msg源文件
)
```

```cmake
generate_messages(
  DEPENDENCIES
  std_msgs					# 添加生成消息时的依赖
)
```

```cmake
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES demo02_talker_listener
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime	 #添加执行依赖messgae_runtime
#  DEPENDS system_lib
)
```

##### step 3 编译

生产中间文件地址：`.../工作空间/devel/lib/python3/dist-packages/包名/msg`

##### step 4 vscode配置

将前面生成的 python 文件路径配置进 `settings.json`

```json
{
    "python.autoComplete.extraPaths": [
        "/opt/ros/noetic/lib/python3/dist-packages",
        "/xxx/yyy工作空间/devel/lib/python3/dist-packages"
    ]
}
```

##### 发布方：

```python
#! /usr/bin/env python

import rospy
from topic_DIYmsg.msg import Person			# 从工作空间导入msg文件

if __name__ == "__main__":
    #1.初始化 ROS 节点
    rospy.init_node("talker_person_p")
    #2.创建发布者对象
    pub = rospy.Publisher("chatter_person",Person,queue_size=10)	# 选择自定义类型
    #3.组织消息
    p = Person()
    p.name = "葫芦瓦"
    p.age = 18
    p.height = 0.75
    #4.编写消息发布逻辑
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        pub.publish(p)  #发布消息
        rate.sleep()  #休眠
        rospy.loginfo("姓名:%s, 年龄:%d, 身高:%.2f",p.name, p.age, p.height)
```

##### 订阅方：

```python
#! /usr/bin/env python

import rospy
from topic_DIYmsg.msg import Person

def doPerson(p):
    rospy.loginfo("接收到的人的信息:%s, %d, %.2f",p.name, p.age, p.height)

if __name__ == "__main__":
    #1.初始化节点
    rospy.init_node("listener_person_p")
    #2.创建订阅者对象
    sub = rospy.Subscriber("chatter_person",Person,doPerson,queue_size=10)
    rospy.spin() #3.循环
```



### 2. 服务通信

服务通信是基于**请求响应**模式的，是一种应答机制。也即: 一个节点A向另一个节点B发送请求，B接收处理请求并产生响应结果返回给A。

用于偶然的、对时时性有要求、有一定逻辑处理需求的数据传输场景。

#### 2.1 理论模型

ROS Master 负责保管 Server 和 Client 注册的信息，并匹配话题相同的 Server 与 Client ，帮助 Server 与 Client 建立连接，连接建立后，Client 发送请求信息，Server 返回响应信息。

<img src="http://www.autolabor.com.cn/book/ROSTutorials/assets/02_%E6%9C%8D%E5%8A%A1%E9%80%9A%E4%BF%A1%E6%A8%A1%E5%9E%8B.jpg" alt="img" style="zoom:50%;" />

**0. Server注册:**Server 启动后，会通过RPC在 ROS Master 中注册自身信息，其中包含提供的服务的名称。ROS Master 会将节点的注册信息加入到注册表中。

**1. Client注册:**Client 启动后，也会通过RPC在 ROS Master 中注册自身信息，包含需要请求的服务的名称。ROS Master 会将节点的注册信息加入到注册表中。

**2. ROS Master实现信息匹配**：ROS Master 会根据注册表中的信息匹配Server和 Client，并通过 RPC 向 Client 发送 Server 的 **TCP** 地址信息。

**3. Client发送请求**：Client 根据步骤2 响应的信息，使用 TCP 与 Server 建立网络连接，并发送请求数据。

**4. Server发送响应**：Server 接收、解析请求的数据，并产生响应结果返回给 Client。



#### 2.2 自定义srv

srv 文件内的可用数据类型与 msg 文件一致，且定义 srv 实现流程与自定义 msg 实现流程类似:

1. 按照固定格式创建srv文件
2. 编辑配置文件
3. 编译生成中间文件

##### step 1 定义srv文件

服务通信中，数据分成两部分，请求与响应，在 srv 文件中请求和响应使用`---`分割，具体实现如下:

功能包下新建 srv 目录，添加 xxx.srv 文件

```c
# 客户端请求时发送的两个数字 Request
int32 num1
int32 num2
---
# 服务器响应发送的数据 Response
int32 sum
```

##### step 2 编辑配置文件
与自定义srv类似，首先在`package.xml`中添加编译依赖和执行依赖

```xml
<build_depend>message_generation</build_depend>		<!--编译时使用的依赖项-->
  
<exec_depend>message_runtime</exec_depend>			<!--运行时使用的依赖项-->
```

`CMakeLists.txt`编辑 srv 相关配置

```cmake
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation		# 编译加入message_generation包
)
```

```cmake
add_service_files(
  FILES
  intsum.srv				# 添加srv源文件
)
```

```cmake
generate_messages(
  DEPENDENCIES
  std_msgs					# 添加生成消息时的依赖
)
```

```cmake
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES demo02_talker_listener
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime	 #添加执行依赖messgae_runtime
#  DEPENDS system_lib
)
```

##### step 3 编译

Python 需要调用的中间文件(`.../工作空间/devel/lib/python3/dist-packages/包名/srv`)

##### step 4 vscode配置

配置setting.json文件

```json
{
    "python.autoComplete.extraPaths": [
        "/opt/ros/noetic/lib/python3/dist-packages",
    ]
}
```

##### 服务端：

```python
#! /usr/bin/env python

# 1. 导入包
import rospy
from service_client_test.srv import intsum,intsumRequest,intsumResponse

# 建立回调函数
def doReq(req):
    # 处理数据并响应
    sum = req.num1 + req.num2
    # 创建响应对象
    resp = intsumResponse()
    resp.sum = sum
    rospy.loginfo("提交的数据为：num1=%d,num2=%d,sum=%d",req.num1,req.num2,resp.sum)
    return resp

if __name__ == "__main__":
    # 初始化节点
    rospy.init_node("intsum_service")
    # 创建服务对象（name，class，func）
    service = rospy.Service("insum",intsum,doReq)
    # spin函数
    rospy.spin()
```

##### 客户端：

```python
#! /usr/bin/env python

import rospy
from service_client_test.srv import intsum,intsumRequest,intsumResponse
import sys

if __name__ == "__main__":

    #优化实现
    if len(sys.argv) != 3:
        rospy.logerr("请正确提交参数")
        sys.exit(1)

    # 2.初始化 ROS 节点
    rospy.init_node("intsum_client")
    # 3.创建客户端对象（name，class）
    client = rospy.ServiceProxy("intsum",intsum)
    
    # 请求前，等待服务已经就绪
    # 方式1:
    # rospy.wait_for_service("AddInts")
    # 方式2
    client.wait_for_service()
    
    # 4.发送请求,接收并处理响应
    # 方式1
    # resp = client(3,4)
    # 方式2
    # resp = client(AddIntsRequest(1,5))
    # 方式3
    req = intsumRequest()
    # req.num1 = 100
    # req.num2 = 200 

    #优化
    req.num1 = int(sys.argv[1])
    req.num2 = int(sys.argv[2]) 

    resp = client.call(req)
    rospy.loginfo("响应结果:%d",resp.sum)

```



### 3. 参数服务器通信

#### 3.1 理论模型

ROS Master 作为一个公共容器保存参数，Talker 可以向容器中设置参数，Listener 可以获取参数。

<img src="http://www.autolabor.com.cn/book/ROSTutorials/assets/03ROS%E9%80%9A%E4%BF%A1%E6%9C%BA%E5%88%B603_%E5%8F%82%E6%95%B0%E6%9C%8D%E5%8A%A1%E5%99%A8.jpg" alt="img" style="zoom:50%;" />

整个流程由以下步骤实现:

**1.Talker 设置参数**

Talker 通过 RPC 向参数服务器发送参数(包括参数名与参数值)，ROS Master 将参数保存到参数列表中。

**2.Listener 获取参数**

Listener 通过 RPC 向参数服务器发送参数查找请求，请求中包含要查找的参数名。

**3.ROS Master 向 Listener 发送参数值**

ROS Master 根据步骤2请求提供的参数名查找参数值，并将查询结果通过 RPC 发送给 Listener。



#### 3.2 基本操作

##### 3.2.1 新增、修改参数

```python
#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("add_para")

    # 设置参数
    rospy.set_param("para01_int",10)
    rospy.set_param("para02_double",2.56)
    rospy.set_param("para03_bool",True)
    rospy.set_param("para04_string","hello")
    rospy.set_param("para05_list",["a","b",3])
    rospy.set_param("para06_dict",{"name":"gwq","age":24})

    # 修改参数
    rospy.set_param("para02_double",4.62)
```

##### 3.2.2 获取参数

```python
#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("get_para")

    # 获取参数 rospy.get_param(name,default)
    para01_intValue = rospy.get_param("para01_int")
    para01_intValue2 = rospy.get_param("para01_int2",100)
    para02_doubleValue = rospy.get_param("para02_double")
    para03_boolValue = rospy.get_param("para03_bool")
    para05_list = rospy.get_param("para05_list")
    para06_dict = rospy.get_param("para06_dict")

    rospy.loginfo("获取的数据为：%d,%d,%.3f,%d",
                  para01_intValue,
                  para01_intValue2,
                  para02_doubleValue,
                  para03_boolValue)
    rospy.loginfo("iist data:")
    for elem in para05_list:
        rospy.loginfo(elem)

    # 类似方法 rospy.get_param_cached()
    int_cach = rospy.get_param_cached("para01_int")
    name = rospy.get_param_names()
    print(name)

    # 判断是否存在参数 rospy.has_param()
    flag = rospy.has_param("para03_bool")
    if flag:
        print("exict")
    else:
        print("no exict")

    # 搜索参数，若存在返回参数名，若不存在返回None rospy.search_param()
    key = rospy.search_param("para02_int")
    print(key)
```

##### 3.2.3 删除参数

```python
#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("delet_para")
	
    # 若参数名不存在会报错
    try:
        rospy.delete_param("para01_int")
    except Exception as e:
        rospy.loginfo("delete fail")
```



### 4. 常用命令

##### rosnode

```shell
rosnode ping    测试到节点的连接状态
rosnode list    列出活动节点
rosnode info    打印节点信息
rosnode machine    列出指定设备上节点
rosnode kill    杀死某个节点
rosnode cleanup    清除不可连接的节点
```

##### rostopic

```shell
rostopic bw     显示主题使用的带宽
rostopic delay  显示带有 header 的主题延迟
rostopic echo   打印消息到屏幕
rostopic find   根据类型查找主题
rostopic hz     显示主题的发布频率
rostopic info   显示主题相关信息
rostopic list (-v)   显示所有活动状态下的主题
rostopic pub /主题名称 消息类型 消息内容    直接调用命令向订阅者发布消息
rostopic type   打印主题类型
```

##### rosmsg

```shell
rosmsg show 消息名称   	显示消息描述
rosmsg info    		   显示消息信息
rosmsg list   		   列出所有消息
rosmsg md5    		   显示 md5 加密后的消息
rosmsg package 包名    显示某个功能包下的所有msg
rosmsg packages    	   列出包含消息的功能包
```

##### rosservice

```shell
rosservice args 	打印服务参数
rosservice call    	使用提供的参数调用服务
rosservice find    	按照服务类型查找服务
rosservice info    	打印有关服务的信息
rosservice list    	列出所有活动的服务
rosservice type    	打印服务类型
rosservice uri    	打印服务的 ROSRPC uri
```

##### rossrv

```shell
rossrv show    	显示服务消息详情
rossrv info    	显示服务消息相关信息
rossrv list    	列出所有服务信息
rossrv md5    	显示 md5 加密后的服务消息
rossrv package 包名  显示某个包下所有服务消息
rossrv packages    	显示包含服务消息的所有包
```

##### rosparam

```shell
rosparam set    设置参数
rosparam get    获取参数
rosparam load    从外部文件加载参数
rosparam dump    将参数写出到外部文件
rosparam delete    删除参数
rosparam list    列出所有参数
```



### 5. 常用API

#### 5.1 初始化

```python
def init_node(name, argv=None, anonymous=False, log_level=None, disable_rostime=False, disable_rosout=False, disable_signals=False, xmlrpc_port=0, tcpros_port=0):
"""
在ROS msater中注册节点

@param name: 节点名称，必须保证节点名称唯一，节点名称中不能使用命名空间(不能包含 '/')
@type  name: str

@param anonymous: 取值为 true 时，为节点名称后缀随机编号
@type anonymous: bool
"""
```

#### 5.2 话题与服务

##### 发布对象

```python
class Publisher(Topic):
"""
在ROS master注册为相关话题的发布方
"""

    def __init__(self, name, data_class, subscriber_listener=None, tcp_nodelay=False, latch=False, headers=None, queue_size=None):
    """
    Constructor
    @param name: 话题名称 
    @type  name: str
    @param data_class: 消息类型

    @param latch: 如果为 true,该话题发布的最后一条消息将被保存，并且后期当有订阅者连接时会将该消息发送给订阅者
    @type  latch: bool

    @param queue_size: 等待发送给订阅者的最大消息数量
    @type  queue_size: int

    """
    def publish(self, *args, **kwds):
        ...
```

##### 订阅对象

```python
class Subscriber(Topic):
    """
   类注册为指定主题的订阅者，其中消息是给定类型的。
    """
    def __init__(self, name, data_class, callback=None, callback_args=None,
                 queue_size=None, buff_size=DEFAULT_BUFF_SIZE, tcp_nodelay=False):
        """
        Constructor.

        @param name: 话题名称
        @type  name: str
        @param data_class: 消息类型
        @type  data_class: L{Message} class
        @param callback: 处理订阅到的消息的回调函数
        @type  callback: fn(msg, cb_args)

        @param queue_size: 消息队列长度，超出长度时，头部的消息将被弃用

        """

```

##### 服务对象

```python
class Service(ServiceImpl):
    """
     声明一个ROS服务

    使用示例::
      s = Service('getmapservice', GetMap, get_map_handler)
    """

    def __init__(self, name, service_class, handler,
                 buff_size=DEFAULT_BUFF_SIZE, error_handler=None):
        """

        @param name: 服务主题名称 ``str``
        @param service_class:服务消息类型

        @param handler: 回调函数，处理请求数据，并返回响应数据

        @type  handler: fn(req)->resp

        """

```

##### 客户端对象

```python
class ServiceProxy(_Service):
    """
   创建一个ROS服务的句柄

    示例用法::
      add_two_ints = ServiceProxy('add_two_ints', AddTwoInts)
      resp = add_two_ints(1, 2)
    """

    def __init__(self, name, service_class, persistent=False, headers=None):
        """
        ctor.
        @param name: 服务主题名称
        @type  name: str
        @param service_class: 服务消息类型
        @type  service_class: Service class
        """
        
	def call(self, *args, **kwds):
        """
        发送请求，返回值为响应数据

        """

    def wait_for_service(service, timeout=None):
    	"""
    	调用该函数时，程序会处于阻塞状态直到服务可用
    	@param service: 被等待的服务话题名称
    	@type  service: str
    	@param timeout: 超时时间
    	@type  timeout: double|rospy.Duration
   	 	"""
    
```



#### 5.3 时间相关

```python
#! /usr/bin/env python

import rospy

rospy.init_node("time_action")

rightnow = rospy.Time.now()
rospy.loginfo("当前时间为：%.2f",rightnow.to_sec())

# 自定义时间
diy_time01 = rospy.Time(12345,12)
diy_time02 = rospy.Time(12345.12)
rospy.loginfo(diy_time01.to_sec())
rospy.loginfo(diy_time02.to_sec())
rospy.loginfo(diy_time02 - diy_time01)

# output:
# 12345.000000012
# 12345.12

# 设置时间
diy_time03 = rospy.Time.from_sec(54321.12)
diy_time04 = rospy.Time.from_seconds(54321.12)

# 持续时间
durTime = rospy.Duration(2)
rospy.loginfo("start")
rospy.sleep(durTime)
rospy.loginfo("end")

# 时间运算
durTime01 = rospy.Duration(10)
durTime02 = rospy.Duration(20)
beforeTime = rightnow - durTime01
afterTime = rightnow + durTime02
durDura = durTime01 + durTime02
rightnow02 = rospy.Time.now()
durDura02 = rightnow02.to_sec() - rightnow.to_sec()
rospy.loginfo(durDura.to_sec())
rospy.loginfo(durDura02)

# 定时器
def doTime(event):
    rospy.loginfo("00000")
    rospy.loginfo("当前时间为：%s",str(event.current_real))

rospy.Timer(rospy.Duration(2),doTime)
rospy.spin()
```



#### 5.4 其他函数

```python
def is_shutdown():
    """
    @return: True 如果节点已经被关闭
    @rtype: bool
    """
```

```python
def signal_shutdown(reason):
    """
    关闭节点
    @param reason: 节点关闭的原因，是一个字符串
    @type  reason: str
    """
def on_shutdown(h):
    """
    节点被关闭时调用的函数
    @param h: 关闭时调用的回调函数，此函数无参
    @type  h: fn()
    """
```

```python
rospy.logdebug("hello,debug")  #不会输出
rospy.loginfo("hello,info")  #默认白色字体
rospy.logwarn("hello,warn")  #默认黄色字体
rospy.logerr("hello,error")  #默认红色字体
rospy.logfatal("hello,fatal") #默认红色字体
```



### 6. python模块的导入

```python
import os
import sys

path = os.path.abspath(".")
# 核心
sys.path.insert(0,path + "/src/plumbing_pub_sub/scripts")

import tools

....
....

rospy.loginfo("num = %d",tools.num)

```



## 三、ROS运行管理

### 1. 元功能包

MetaPackage是Linux的一个文件管理系统的概念。是ROS中的一个虚包，里面没有实质性的内容，但是它依赖了其他的软件包，通过这种方法可以把其他包组合起来，我们可以认为它是一本书的目录索引，告诉我们这个包集合中有哪些子包，并且该去哪里下载。

#### 实现：

**首先:**新建一个功能包

**然后:**修改**package.xml** ,内容如下:

```xml
 <exec_depend>被集成的功能包</exec_depend>
 .....
 <export>
   <metapackage />
 </export>
```

**最后:**修改 CMakeLists.txt,内容如下:

```cmake
cmake_minimum_required(VERSION 3.0.2)
project(demo)
find_package(catkin REQUIRED)
catkin_metapackage()
```

PS:CMakeLists.txt 中不可以有换行。



### 2. Launch文件

launch 文件是一个 XML 格式的文件，可以启动本地和远程的多个节点，还可以在参数服务器中设置参数。

#### 主要结构：

```xml
<launch>
    <node pkg="turtlesim" type="turtlesim_node" name="turtle1" output="screen" />
    <node pkg="turtlesim" type="turtle_teleop_key" name="key1" />
    <node pkg="tf_dynamic" type="tf_dynamic_pub.py" name="dynamic_pub" />
    <node pkg="tf_dynamic" type="tf_dynamic_sub.py" name="dynamic_sub" output="screen"/>
</launch>
```

#### 标签：

**1. launch**

`<launch [deprecated=" "]>`

是所有 launch 文件的根标签，充当其他标签的容器

属性：`deprecated = "弃用声明"`

**2. node**

`node [pkg="包名"] [type="执行文件名"] [name="节点名称"] [args="参数"] [respawn="true|false（自动重启）"] [required="true|false"] [output="log|screen"]`

子级标签：

- env 环境变量设置
- remap 重映射节点名称
- rosparam 参数设置
- param 参数设置

**3. include**

用于将另一个 xml 格式的 launch 文件导入到当前文件

例：

```xml
<launch>
    <include file="$(find launch_test01)/launch/start_turtle.launch"/>
</launch>
```

**4. remap**

用于话题重命名

```xml
<remap from="/turtle1/cmd_vel" to="/cmd_vel" />
```

**5. param**

在参数服务器上设置参数，可以位于<node>内，也可以在<launch>内

```xml
<param name="para02" type="str" value="ssss" />
```

**6. rosparam**

可以从 YAML 文件导入参数，或将参数导出到 YAML 文件，也可以用来删除参数

```xml
<rosparam command="load" file="$(find launch_test01)/launch/params.yaml">
<rosparam command="dump" file="$(find launch_test01)/launch/paramsDump.yaml">
```

**7. group**

可以对节点分组，具有 ns 属性，可以让节点归属某个命名空间

- ns="名称空间" (可选)

- clear_params="true | false" (可选)

  启动前，是否删除组名称空间的所有参数(慎用....此功能危险)

**8. arf**

用于动态传参，类似于函数的参数，可以增强launch文件的灵活性

```xml
<launch>
    <arg name="data01" default="2.0" />

    <param name="a" value="$(arg data01)" />
    <param name="b" value="$(arg data01)" />
    <param name="c" value="$(arg data01)" />

</launch>
<!-- run: roslaunch launch_test01 arg_test.launch data01:= value -->
```

- name="参数名称"

- default="默认值" (可选)

- value="数值" (可选)

  不可以与 default 并存

- doc="描述"

  参数说明



### 3. 节点名称重映射

#### 3.1 rosrun设置命名空间

语法: rosrun 包名 节点名 __ns:=新名称

```shell
rosrun turtlesim turtlesim_node __ns:=/xxx

/xxx/turtlesim
```

#### 3.2 rosrun名称重映射

语法: rosrun 包名 节点名 __name:=新名称

```shell
rosrun turtlesim  turtlesim_node __name:=t1

/t1
```

#### 3.3 编码实现

`rospy.init_node("example",anonymous=True)`

会在节点名称后缀时间戳

#### 3.4 launch文件实现

修改launch文件中的`name`和`ns`属性



### 4. 话题名称重映射

#### 4.1 rosrun设置

将 teleop_twist_keyboard 节点的话题从`/cmd_vel`设置为`/turtle1/cmd_vel`

```shell
rosrun teleop_twist_keyboard teleop_twist_keyboard.py /cmd_vel:=/turtle1/cmd_vel
```

#### 4.2 launch文件设置

```xml
<node pkg="xxx" type="xxx" name="xxx">
    <remap from="原话题" to="新话题" />
</node>
```

#### 4.3 编码设置

##### 全局名称

格式:以`/`开头的名称，和节点名称无关

示例1:`pub = rospy.Publisher("/chatter",String,queue_size=1000)`

结果1:`/chatter`

示例2:`pub = rospy.Publisher("/chatter/money",String,queue_size=1000)`

结果2:`/chatter/money`

##### 相对名称

格式:非`/`开头的名称,参考命名空间(与节点名称平级)来确定话题名称

示例1:`pub = rospy.Publisher("chatter",String,queue_size=1000)`

结果1:`xxx/chatter`

示例2:`pub = rospy.Publisher("chatter/money",String,queue_size=1000)`

结果2:`xxx/chatter/money`

##### 私有名称

格式:以`~`开头的名称

示例1:`pub = rospy.Publisher("~chatter",String,queue_size=1000)`

结果1:`/xxx/hello/chatter`

示例2:`pub = rospy.Publisher("~chatter/money",String,queue_size=1000)`

结果2:`/xxx/hello/chatter/money`



### 5. 参数名称重映射

略

### 6. 分布式通信

http://www.autolabor.com.cn/book/ROSTutorials/5/44-rosfen-bu-shi-tong-xin.html



## 四、ROS常用组件

### 1. TF坐标变换

#### 1.1 坐标msg信息

在坐标转换实现中常用的 msg:`geometry_msgs/TransformStamped`和`geometry_msgs/PointStamped`

前者用于传输**坐标系相关位置信息**，后者用于传输**某个坐标系内坐标点的信息**

```shell
# geometry_msgs/TransformStamped
std_msgs/Header header                   #头信息
  uint32 seq                             	#|-- 序列号
  time stamp                             	#|-- 时间戳
  string frame_id                           #|-- 坐标 ID
string child_frame_id                    #子坐标系的 id
geometry_msgs/Transform transform        #坐标信息
  geometry_msgs/Vector3 translation      	#偏移量
    float64 x                                 #|-- X 方向的偏移量
    float64 y                                 #|-- Y 方向的偏移量
    float64 z                                 #|-- Z 方向上的偏移量
  geometry_msgs/Quaternion rotation        	#四元数
    float64 x                                
    float64 y                                
    float64 z                                
    float64 w
```

```shell
# geometry_msgs/PointStamped
std_msgs/Header header                   #头
  uint32 seq                               #|-- 序号
  time stamp                               #|-- 时间戳
  string frame_id                          #|-- 所属坐标系的 id
geometry_msgs/Point point                #点坐标
  float64 x                                #|-- x y z 坐标
  float64 y
  float64 z
```

#### 1.2 静态坐标转换

两个坐标系之间的相对位置是固定的。

##### 发布方：

1.导包
2.初始化 ROS 节点
3.创建静态坐标广播器
4.创建并组织被广播的消息
5.广播器发送消息
6.spin

```python
#! /usr/bin/env python

import rospy
import tf2_ros
import tf.transformations
from geometry_msgs.msg import TransformStamped

if __name__ == "__main__":
    
    rospy.init_node("static_pub")
    
    # 创建静态广播对象
    broadcast = tf2_ros.StaticTransformBroadcaster()
    
    # 创建消息
    tfs = TransformStamped()

    tfs.header.frame_id = "base"    # 坐标ID
    tfs.header.stamp = rospy.Time.now() # 时间戳
    tfs.header.seq = 101    # 序列号

    tfs.child_frame_id = "radar"    # 子坐标ID
    
    # 坐标偏移量
    tfs.transform.translation.x = 0.2
    tfs.transform.translation.y = 0.0
    tfs.transform.translation.z = 0.5

    # 四元数
    qtn = tf.transformations.quaternion_from_euler(0,0,0)
    tfs.transform.rotation.x = qtn[0]
    tfs.transform.rotation.y = qtn[1]
    tfs.transform.rotation.z = qtn[2]
    tfs.transform.rotation.w = qtn[3]

    broadcast.sendTransform(tfs)
    rospy.spin()
```

##### 订阅方：

1.导包
2.初始化 ROS 节点
3.创建 TF 订阅对象
4.创建一个 radar 坐标系中的坐标点
5.调研订阅对象的 API 将 4 中的点坐标转换成相对于 world 的坐标
6.spin

```python
#! /usr/bin/env python

import rospy
import tf2_ros

from tf2_geometry_msgs import tf2_geometry_msgs

if __name__ == "__main__":
    rospy.init_node("static_sub")

    # 创建订阅对象
    buffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(buffer)
    rate = rospy.Rate(1)

    while not rospy.is_shutdown():
        # 创建坐标点
        point_source = tf2_geometry_msgs.PointStamped()
        point_source.header.frame_id = "radar"
        point_source.header.stamp = rospy.Time.now()
        point_source.point.x = 2.0
        point_source.point.y = 3.0
        point_source.point.z = 5.0

        try:    # 有概率存在时间错位
            point_target = buffer.transform(point_source,"base")
            rospy.loginfo("result: %.2f,%.2f,%.2f",point_target.point.x,point_target.point.y,point_target.point.z)
        except Exception as e:
            rospy.logwarn("error:%s",e)

        rate.sleep()
```

##### 命令行实现：

`rosrun tf2_ros static_transform_publisher x偏移量 y偏移量 z偏移量 z偏航角度 y俯仰角度 x翻滚角度 父级坐标系 子级坐标系`

#### 1.3 动态坐标系变换

与静态类似，偏移量和四元数处设置为变化量

#### 1.4 多坐标变换

依赖于 tf2、tf2_ros、tf2_geometry_msgs、roscpp rospy std_msgs geometry_msgs、turtlesim

```python
#! /usr/bin/env python

import rospy
import tf2_ros
from geometry_msgs.msg import TransformStamped
from tf2_geometry_msgs.tf2_geometry_msgs import PointStamped

if __name__ == "__main__":
    rospy.init_node("coord_sub")
    buffer = tf2_ros.Buffer()
    listener = tf2_ros.TransformListener(buffer)
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        try:
            tfs = buffer.lookup_transform("coord01","coord02",rospy.Time(0))
            rospy.loginfo("相对关系：")
            rospy.loginfo("父系坐标系：%s",tfs.header.frame_id)
            rospy.loginfo("子系坐标系：%s",tfs.child_frame_id)
            rospy.loginfo("相对坐标：(%.2f,%.2f,%.2f)",
                          tfs.transform.translation.x,
                          tfs.transform.translation.y,
                          tfs.transform.translation.z)
            
            point_source = PointStamped()
            point_source.header.frame_id = "coord01"
            point_source.header.stamp = rospy.Time.now()
            point_source.point.x = 1.0
            point_source.point.y = 1.0
            point_source.point.z = 1.0

            point_target = buffer.transform(point_source,"coord02",rospy.Duration(0.5))
            rospy.loginfo("point所属坐标系为:%s",point_source.header.frame_id)
            rospy.loginfo("point相对于coord02的坐标为:(%.2f,%.2f,%.2f)",
                          point_target.point.x,
                          point_target.point.y,
                          point_target.point.z
                          )

        except Exception as e:
            rospy.logerr("错误提示:%s",e)

        rate.sleep()
```

#### 1.5 坐标关系查看

```shell
rosrun tf2_tools view_frames.py
```



### 2. rosbag

**概念**
是用于录制和回放 ROS 主题的一个工具集。

**作用**
实现了数据的复用，方便调试、测试。

**本质**
rosbag本质也是ros的节点，当录制时，rosbag是一个订阅节点，可以订阅话题消息并将订阅到的数据写入磁盘文件；当重放时，rosbag是一个发布节点，可以读取磁盘文件，发布文件中的话题消息。

#### 2.1 命令行使用

进入录制保存目录

```shell
cd xxx
```

开始录制

```shell
rosbag record -a -O 目标文件
```

操作小乌龟一段时间，结束录制使用 ctrl + c，在创建的目录中会生成bag文件

查看文件

```shell
rosbag info 文件名
```

回放文件

```shell
rosbag play 文件名
```

#### 2.2 编码使用

写bag

```python
#! /usr/bin/env python
import rospy
import rosbag
from std_msgs.msg import String

if __name__ == "__main__":
    #初始化节点 
    rospy.init_node("w_bag_p")

    # 创建 rosbag 对象
    bag = rosbag.Bag("/home/rosdemo/demo/test.bag",'w')

    # 写数据
    s = String()
    s.data= "hahahaha"

    bag.write("chatter",s)
    bag.write("chatter",s)
    bag.write("chatter",s)
    # 关闭流
    bag.close()

```

读bag

```python
#! /usr/bin/env python
import rospy
import rosbag
from std_msgs.msg import String

if __name__ == "__main__":
    #初始化节点 
    rospy.init_node("w_bag_p")

    # 创建 rosbag 对象
    bag = rosbag.Bag("/home/rosdemo/demo/test.bag",'r')
    # 读数据
    bagMessage = bag.read_messages("chatter")
    for topic,msg,t in bagMessage:
        rospy.loginfo("%s,%s,%s",topic,msg,t)
    # 关闭流
    bag.close()

```



### 3. rqt工具箱

#### 3.1 rqt_graph

可视化显示计算图

#### 3.2 rqt_console

用于显示和过滤日志的图形化插件

#### 3.3 rqt_plot

以 2D 绘图的方式绘制发布在 topic 上的数据

#### 3.4 rqt_bag

录制和重放 bag 文件的图形化插件



## 五、机器人系统仿真

### 1. URDF集成Rviz

#### 1.1 实现流程

- **准备:新建功能包，导入依赖**

  创建一个新的功能包，名称自定义，导入依赖包:`urdf`与`xacro`

  在当前功能包下，再新建几个目录:

  `urdf`: 存储 urdf 文件的目录

  `meshes`:机器人模型渲染文件(暂不使用)

  `config`: 配置文件

  `launch`: 存储 launch 启动文件

- **核心:编写 urdf 文件**

  新建一个子级文件夹:`urdf`(可选)，文件夹中添加一个`.urdf`文件

- **核心:在 launch 文件集成 URDF 与 Rviz**

  ```xml
  <launch>
  
      <!-- 设置参数 -->
      <param name="robot_description" textfile="$(find 包名)/urdf/urdf/urdf01_HelloWorld.urdf" />
  
      <!-- 启动 rviz -->
      <node pkg="rviz" type="rviz" name="rviz" />
  
  </launch>
  
  ```

- **在 Rviz 中显示机器人模型**

- **优化rviz启动**

  选择`File/Save Config As`保存配置文件

  launch文件中设置读取配置文件：

  ```xml
  <launch>
      <param name="robot_description" textfile="$(find 包名)/urdf/urdf/urdf01_HelloWorld.urdf" />
      <node pkg="rviz" type="rviz" name="rviz" args="-d $(find 包名)/config/rviz/show_mycar.rviz" />
  </launch>
  ```

  

#### 1.2 URDF语法

##### robot

属性：`name`

##### link

属性：`name`

子标签：

```xml
<link name="base_link">
    <visual>
        <geometry>
            <box size="0.5 0.2 0.1" />
        </geometry>
        <origin xyz="0 0 0" rpy="0 0 0" />
        <material name="blue">
            <color rgba="0 0 1.0 0.5" />
        </material>
    </visual>
</link>
```

- visual ---> 描述外观(对应的数据是可视的)
  - geometry 设置连杆的形状
    - 标签1: box(盒状)
      - 属性:size=长(x) 宽(y) 高(z)
    - 标签2: cylinder(圆柱)
      - 属性:radius=半径 length=高度
    - 标签3: sphere(球体)
      - 属性:radius=半径
    - 标签4: mesh(为连杆添加皮肤)
      - 属性: filename=资源路径(格式: package://<packagename>/<path>/文件)
  - origin 设置偏移量与倾斜弧度
    - 属性1: xyz=x偏移 y便宜 z偏移
    - 属性2: rpy=x翻滚 y俯仰 z偏航 (单位是弧度)
  - metrial 设置材料属性(颜色)
    - 属性: name
    - 标签: color
      - 属性: rgba=红绿蓝权重值与透明度 (每个权重值以及透明度取值[0,1])
- collision ---> 连杆的碰撞属性
- Inertial ---> 连杆的惯性矩阵



##### joint

属性：

- name ---> 为关节命名
- type ---> 关节运动形式
  - continuous: 旋转关节，可以绕单轴无限旋转
  - revolute: 旋转关节，类似于 continues,但是有旋转角度限制
  - prismatic: 滑动关节，沿某一轴线移动的关节，有位置极限
  - planer: 平面关节，允许在平面正交方向上平移或旋转
  - floating: 浮动关节，允许进行平移、旋转运动
  - fixed: 固定关节，不允许运动的特殊关节

子标签：

- parent(必需的)

  parent link的名字是一个强制的属性：

  - link:父级连杆的名字，是这个link在机器人结构树中的名字。

- child(必需的)

  child link的名字是一个强制的属性：

  - link:子级连杆的名字，是这个link在机器人结构树中的名字。

- origin

  - 属性: xyz=各轴线上的偏移量 rpy=各轴线上的偏移弧度。

- axis

  - 属性: xyz用于设置围绕哪个关节轴运动。

```xml
<joint name="camera2baselink" type="continuous">
    <parent link="base_link"/>
    <child link="camera" />
    <!-- 需要计算两个 link 的物理中心之间的偏移量 -->
    <origin xyz="0.2 0 0.075" rpy="0 0 0" />
    <axis xyz="0 0 1" />
</joint>
```



#### 1.3 URDF工具

- `check_urdf`命令可以检查复杂的 urdf 文件是否存在语法问题

  进入urdf文件所属目录，调用:`check_urdf urdf文件`，如果不抛出异常，说明文件合法,否则非法

- `urdf_to_graphiz`命令可以查看 urdf 模型结构，显示不同 link 的层级关系

  进入urdf文件所属目录，调用:`urdf_to_graphiz urdf文件`，当前目录下会生成 pdf 文件



### 2. xacro优化

#### 2.1 实现流程

- 创建功能包，导入 urdf 与 xacro
- 在功能包目录下的`urdf`目录下创建`xacro`目录
- 在目录下建立`.urdf.xacro`文件
- 文件首行`robot`标签下写入属性：`<robot xmlns:xacro="http://www.ros.org/wiki/xacro" name="mycar">`

#### 2.2 xacro语法

##### 参数定义

```xml
<xacro:property name="xxxx" value="yyyy" />
```

##### 参数调用

```xml
${属性名称}
${数学表达式}
```

##### 宏定义

```xml
<xacro:macro name="宏名称" params="参数列表(多参数之间使用空格分隔)">

	包装内容

</xacro:macro>
```

##### 宏调用

```xml
<xacro:宏名称 参数1=xxx 参数2=xxx/>
```

##### 文件包含

```xml
<robot name="xxx" xmlns:xacro="http://wiki.ros.org/xacro">
      <xacro:include filename="my_base.xacro" />
      <xacro:include filename="my_camera.xacro" />
      <xacro:include filename="my_laser.xacro" />
      ....
</robot>
```

##### 完整案例

见`/rospy_ws04_simulation/src/xacro/xacro_test.urdf.xacro,./camera.urdf.xacro,./comba.urdf.xacro`

##### xacro转换

xacro 文件解析成 urdf 文件:`rosrun xacro xacro xxx.xacro > xxx.urdf`



#### 2.3 launch文件编写

```xml
<launch>

    <param name="robot_description" command="$(find xacro)/xacro $(find urdf_basic_test)/urdf/xacro/comba.urdf.xacro" />
    <node pkg="rviz" type="rviz" name="rviz" args="-d $(find urdf_basic_test)/config/config02.rviz" /> 

    <!-- 添加关节状态发布节点 -->
    <node pkg="joint_state_publisher" type="joint_state_publisher" name="joint_state_publisher" />
    <!-- 添加机器人状态发布节点 -->
    <node pkg="robot_state_publisher" type="robot_state_publisher" name="robot_state_publisher" />
    <!-- 可选:用于控制关节运动的节点 -->
    <node pkg="joint_state_publisher_gui" type="joint_state_publisher_gui" name="joint_state_publisher_gui" output="screen" />

</launch>
```



#### 2.4 Arbotix使用

控制机器人模型在 rviz 中运动

- **创建新功能包，准备机器人 urdf、xacro**

- **添加 arbotix 所需的配置文件**

  ```yaml
  # 该文件是控制器配置,一个机器人模型可能有多个控制器，比如: 底盘、机械臂、夹持器(机械手)....
  # 因此，根 name 是 controller
  controllers: {
     # 单控制器设置
     base_controller: {
            #类型: 差速控制器
         type: diff_controller,
         #参考坐标
         base_frame_id: base_footprint, 
         #两个轮子之间的间距
         base_width: 0.2,
         #控制频率
         ticks_meter: 2000, 
         #PID控制参数，使机器人车轮快速达到预期速度
         Kp: 12, 
         Kd: 12, 
         Ki: 0, 
         Ko: 50, 
         #加速限制
         accel_limit: 1.0 
      }
  }
  ```

- **launch 文件中配置 arbotix 节点**

  在launch文件中添加如下语句

  ```xml
  <node name="arbotix" pkg="arbotix_python" type="arbotix_driver" output="screen">
       <rosparam file="$(find my_urdf05_rviz)/config/hello.yaml" command="load" />
       <param name="sim" value="true" />
  </node>
  ```

- **启动 launch 文件并控制机器人模型运动**

  在rviz界面打开`Odometry`，利用`/cmd_vel`话题控制运动



### 3. URDF集成Gazebo

#### 3.1 基本流程

URDF 与 Gazebo 集成流程与 Rviz 实现类似，主要步骤如下:

- **创建功能包，导入依赖项**

  导入依赖包: urdf、xacro、gazebo_ros、gazebo_ros_control、gazebo_plugins

- **编写 URDF 或 Xacro 文件**

  - 添加collision标签和inertial标签

    ```xml
    <collision>
    	<geometry>
    		<box size="0.5 0.2 0.1" />
    	</geometry>
    	<origin xyz="0.0 0.0 0.0" rpy="0.0 0.0 0.0" />
    </collision>
    <inertial>
    	<origin xyz="0 0 0" />
    	<mass value="6" />
    	<inertia ixx="1" ixy="0" ixz="0" iyy="1" iyz="0" izz="1" />  <!--转动惯量-->
    </inertial>
    ```

  - 颜色配置

    ```xml
    <gazebo reference="base_link">
    	<material>Gazebo/Black</material>
    </gazebo>
    ```

  - `inertial`部分可以使用`xacro`脚本进行编写

    ```xml
    <robot name="base" xmlns:xacro="http://wiki.ros.org/xacro">
        <!-- Macro for inertia matrix -->
        <xacro:macro name="sphere_inertial_matrix" params="m r">
            <inertial>
                <mass value="${m}" />
                <inertia ixx="${2*m*r*r/5}" ixy="0" ixz="0"
                    iyy="${2*m*r*r/5}" iyz="0" 
                    izz="${2*m*r*r/5}" />
            </inertial>
        </xacro:macro>
    
        <xacro:macro name="cylinder_inertial_matrix" params="m r h">
            <inertial>
                <mass value="${m}" />
                <inertia ixx="${m*(3*r*r+h*h)/12}" ixy = "0" ixz = "0"
                    iyy="${m*(3*r*r+h*h)/12}" iyz = "0"
                    izz="${m*r*r/2}" /> 
            </inertial>
        </xacro:macro>
    
        <xacro:macro name="Box_inertial_matrix" params="m l w h">
           <inertial>
                   <mass value="${m}" />
                   <inertia ixx="${m*(h*h + l*l)/12}" ixy = "0" ixz = "0"
                       iyy="${m*(w*w + l*l)/12}" iyz= "0"
                       izz="${m*(w*w + h*h)/12}" />
           </inertial>
       </xacro:macro>
    </robot>
    ```

- 启动 Gazebo 并显示机器人模型

  launch文件：

  ```xml
  <launch>
      <!-- 将 Urdf 文件的内容加载到参数服务器 -->
      <param name="robot_description" command="$(find xacro)/xacro $(find gazebo_test)/urdf/xacro/comba.urdf.xacro" />
      <!-- 启动 gazebo -->
      <include file="$(find gazebo_ros)/launch/empty_world.launch" >
          <arg name="world_name" value="$(find gazebo_test)/worlds/box_house.world" />
      </include>
      <!-- 在 gazebo 中显示机器人模型 -->
      <node pkg="gazebo_ros" type="spawn_model" name="model" args="-urdf -model mycar -param robot_description"  />
  </launch>
  
  <!-- 
      在 Gazebo 中加载一个机器人模型，该功能由 gazebo_ros 下的 spawn_model 提供:
      -urdf 加载的是 urdf 文件
      -model mycar 模型名称是 mycar
      -param robot_description 从参数 robot_description 中载入模型
      -x 模型载入的 x 坐标
      -y 模型载入的 y 坐标
      -z 模型载入的 z 坐标
  -->
  ```

  ​    

#### 3.2 搭建仿真环境

Gazebo 中创建仿真实现方式有两种:

- 方式1: 直接添加内置组件创建仿真环境
- 方式2: 手动绘制仿真环境(更为灵活)

加载已保存环境：

```xml
<include file="$(find gazebo_ros)/launch/empty_world.launch">
    <arg name="world_name" value="$(find demo02_urdf_gazebo)/worlds/hello.world" />
</include>
```



### 4. 综合应用

#### 4.1 运动控制及里程计信息

传动配置

```xml
<robot name="my_car_move" xmlns:xacro="http://wiki.ros.org/xacro">

    <!-- 传动实现:用于连接控制器与关节 -->
    <xacro:macro name="joint_trans" params="joint_name">
        <!-- Transmission is important to link the joints and the controller -->
        <transmission name="${joint_name}_trans">
            <type>transmission_interface/SimpleTransmission</type>
            <joint name="${joint_name}">
                <hardwareInterface>hardware_interface/VelocityJointInterface</hardwareInterface>
            </joint>
            <actuator name="${joint_name}_motor">
                <hardwareInterface>hardware_interface/VelocityJointInterface</hardwareInterface>
                <mechanicalReduction>1</mechanicalReduction>    <!--电机/关节减速比-->
            </actuator>
        </transmission>
    </xacro:macro>

    <!-- 每一个驱动轮都需要配置传动装置 -->
    <xacro:joint_trans joint_name="left_MoveWheel2base_link" />
    <xacro:joint_trans joint_name="right_MoveWheel2base_link" />

    <!-- 控制器 -->
    <gazebo>
        <plugin name="differential_drive_controller" filename="libgazebo_ros_diff_drive.so">
            <rosDebugLevel>Debug</rosDebugLevel>
            <publishWheelTF>true</publishWheelTF>
            <robotNamespace>/</robotNamespace>
            <publishTf>1</publishTf>
            <publishWheelJointState>true</publishWheelJointState>
            <alwaysOn>true</alwaysOn>
            <updateRate>100.0</updateRate>
            <legacyMode>true</legacyMode>
            <leftJoint>left_MoveWheel2base_link</leftJoint> <!-- 左轮 -->
            <rightJoint>right_MoveWheel2base_link</rightJoint> <!-- 右轮 -->
            <wheelSeparation>${base_link_r * 2}</wheelSeparation> <!-- 车轮间距 -->
            <wheelDiameter>${move_wheel_r * 2}</wheelDiameter> <!-- 车轮直径 -->
            <broadcastTF>1</broadcastTF>
            <wheelTorque>30</wheelTorque>
            <wheelAcceleration>1.8</wheelAcceleration>
            <commandTopic>cmd_vel</commandTopic> <!-- 运动控制话题 -->
            <odometryFrame>odom</odometryFrame> 
            <odometryTopic>odom</odometryTopic> <!-- 里程计话题 -->
            <robotBaseFrame>base_footprint</robotBaseFrame> <!-- 根坐标系 -->
        </plugin>
    </gazebo>

</robot>
```

使用/cmd_vel发布控制话题：

```shell
rostopic pub -r 10 /cmd_vel geometry_msgs/Twist '{linear: {x: 0.2, y: 0, z: 0}, angular: {x: 0, y: 0, z: 0.5}}'
```

启动rviz

```xml
<launch>
    <!-- 启动 rviz -->
    <node pkg="rviz" type="rviz" name="rviz" />

    <!-- 关节以及机器人状态发布节点 -->
    <node name="joint_state_publisher" pkg="joint_state_publisher" type="joint_state_publisher" />
    <node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher" />

</launch>
```

选择odom坐标系，添加Odometry组件



#### 4.2 雷达信息仿真

配置雷达传感器信息

```xml
<robot name="my_sensors" xmlns:xacro="http://wiki.ros.org/xacro">

  <!-- 雷达 -->
  <gazebo reference="laser">
    <sensor type="ray" name="rplidar">
      <pose>0 0 0 0 0 0</pose>
      <visualize>true</visualize>
      <update_rate>5.5</update_rate>
      <ray>
        <scan>
          <horizontal>
            <samples>360</samples>
            <resolution>1</resolution>
            <min_angle>-3</min_angle>
            <max_angle>3</max_angle>
          </horizontal>
        </scan>
        <range>
          <min>0.10</min>
          <max>30.0</max>
          <resolution>0.01</resolution>
        </range>
        <noise>
          <type>gaussian</type>
          <mean>0.0</mean>
          <stddev>0.01</stddev>
        </noise>
      </ray>
      <plugin name="gazebo_rplidar" filename="libgazebo_ros_laser.so">
        <topicName>/scan</topicName>
        <frameName>laser</frameName>
      </plugin>
    </sensor>
  </gazebo>

</robot>
```

启动rviz，添加Laserscan组件



#### 4.3 摄像头信息仿真

配置

```xml
<robot name="my_sensors" xmlns:xacro="http://wiki.ros.org/xacro">
  <!-- 被引用的link -->
  <gazebo reference="camera">
    <!-- 类型设置为 camara -->
    <sensor type="camera" name="camera_node">
      <update_rate>30.0</update_rate> <!-- 更新频率 -->
      <!-- 摄像头基本信息设置 -->
      <camera name="head">
        <horizontal_fov>1.3962634</horizontal_fov>
        <image>
          <width>1280</width>
          <height>720</height>
          <format>R8G8B8</format>
        </image>
        <clip>
          <near>0.02</near>
          <far>300</far>
        </clip>
        <noise>
          <type>gaussian</type>
          <mean>0.0</mean>
          <stddev>0.007</stddev>
        </noise>
      </camera>
      <!-- 核心插件 -->
      <plugin name="gazebo_camera" filename="libgazebo_ros_camera.so">
        <alwaysOn>true</alwaysOn>
        <updateRate>0.0</updateRate>
        <cameraName>/camera</cameraName>
        <imageTopicName>image_raw</imageTopicName>
        <cameraInfoTopicName>camera_info</cameraInfoTopicName>
        <frameName>camera</frameName>
        <hackBaseline>0.07</hackBaseline>
        <distortionK1>0.0</distortionK1>
        <distortionK2>0.0</distortionK2>
        <distortionK3>0.0</distortionK3>
        <distortionT1>0.0</distortionT1>
        <distortionT2>0.0</distortionT2>
      </plugin>
    </sensor>
  </gazebo>
</robot>
```

打开rviz，添加camera组件



#### 4.4 深度相机kinect仿真

配置

```xml
<robot name="my_sensors" xmlns:xacro="http://wiki.ros.org/xacro">
    <gazebo reference="kinect link名称">  
      <sensor type="depth" name="camera">
        <always_on>true</always_on>
        <update_rate>20.0</update_rate>
        <camera>
          <horizontal_fov>${60.0*PI/180.0}</horizontal_fov>
          <image>
            <format>R8G8B8</format>
            <width>640</width>
            <height>480</height>
          </image>
          <clip>
            <near>0.05</near>
            <far>8.0</far>
          </clip>
        </camera>
        <plugin name="kinect_camera_controller" filename="libgazebo_ros_openni_kinect.so">
          <cameraName>camera</cameraName>
          <alwaysOn>true</alwaysOn>
          <updateRate>10</updateRate>
          <imageTopicName>rgb/image_raw</imageTopicName>
          <depthImageTopicName>depth/image_raw</depthImageTopicName>
          <pointCloudTopicName>depth/points</pointCloudTopicName>
          <cameraInfoTopicName>rgb/camera_info</cameraInfoTopicName>
          <depthImageCameraInfoTopicName>depth/camera_info</depthImageCameraInfoTopicName>
          <frameName>kinect link名称</frameName>
          <baseline>0.1</baseline>
          <distortion_k1>0.0</distortion_k1>
          <distortion_k2>0.0</distortion_k2>
          <distortion_k3>0.0</distortion_k3>
          <distortion_t1>0.0</distortion_t1>
          <distortion_t2>0.0</distortion_t2>
          <pointCloudCutoff>0.4</pointCloudCutoff>
        </plugin>
      </sensor>
    </gazebo>
</robot>
```

打开rviz，添加camera组件

##### 点云数据显示

1. 在插件中为kinect设置坐标系，修改配置文件的`<frameName>`标签内容：

```xml
<frameName>support_depth</frameName>
```

2. 发布新设置的坐标系到kinect连杆的坐标变换关系，在启动rviz的launch中，添加:

```xml
<node pkg="tf2_ros" type="static_transform_publisher" name="static_transform_publisher" args="0 0 0 -1.57 0 -1.57 /support /support_depth" />
```

3. 启动rviz，重新显示。
