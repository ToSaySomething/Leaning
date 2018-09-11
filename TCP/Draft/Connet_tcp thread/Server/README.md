模仿POCO库TCP服务端TCPServerConnection 写的SERVER

Server添加了心跳包

activity相当于thread对象

http://www.cppblog.com/richbirdandy/archive/2010/09/10/123994.html
简单的说Notifications模块可用于线程间传递消息，简化多线程服务器的实现。具体到TCPServer，就是把已连接的socket，放到NotificationQueue中，并从TheadPool出来一个线程，线程从NotificationQueue取到这个socket，从而用TCPServerConnection::run()里的逻辑对socket进行处理。


https://www.cnblogs.com/bleachli/p/4352959.html
TCPSERVER结构：

1,TCPServer 主服务,负责 调用select 模型,来处理 连接消息的变化.

2,PooledThread 是线程池.当被激活时,调用 TCPServerDispatcher::run() 来处理收到包后的具体请求.
而 TCPServerDispatcher::run() 中调用 TimeServerConnection.run().  
TimeServerConnection.run()通过子类隐藏 来实现 程序员 自定义 功能.  
不得不说写POCO的大牛利害.

3,TCPServerDispatcher,派遣管理者. 接收消息变化,放入队列.管理 连接数.
当放入队列时,会激活  PooledThread 中的事件 .
PooledThread 又反过来 激活 TCPServerDispatcher::run() [姑且叫 有条件时相互激活吧 ]


4,TCPServerConnection.实现具体行为,通过继承由子类的 run() 来自定义实现 功能.

5,TCPServerConnectionFactory 负责创建和管理 TCPServerConnection.

6,TCPServerParams 这个参数管理 ,就不说了.你懂的.

7,NotificationQueue 把 连接 放入队列.进行管理.

官网：https://pocoproject.org/docs/Poco.html