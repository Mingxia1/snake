# **Snake(仮)**
## 项目说明
这是一个类似贪吃蛇的小游戏。都什么年代了还在玩传统贪吃蛇，这个贪吃蛇可以360°全向旋转。
## 开发平台
本项目基于Qt6.3.1开发，构建方式为CMAKE，可以使用配置好的vscode或qtcreator构建此程序。
(2022/7/30)研究了好几个小时给vscode配置好了clangd，真的好用
## 实现方法
使用QPainter类在QWidget类窗口中绘制以很多QPainterPath微元构成的蛇，利用QTimer实现每毫秒更新一次画面。
## 文件说明
- main.cpp
  - 此文件是qt自动生成的程序入口
- snake.h/cpp
  - snake类，记录了蛇的速度，角度，长度，颜色，宽度，位置等数据，并定义了几个蛇的动作。
- widget.h/cpp
  - 整个程序的主窗口，程序的初始化就从这里开始，控制整个游戏流程。
- ball.h/cpp
  - ball类，记录球的坐标，半径等信息。
- widget.ui
  - 主窗口的qtdesigner设计文件
## 待办列表
- [x] 更改自我碰撞检测机制(2022/7/17)
- [x] 随机生成的球以及相关交互(2022/7/23)
- [ ] 可更改难度
- [x] 增加游戏开始界面(2022/7/23)
  - [ ] 增加更多UI
- [x] 增加游戏结束界面(2022/7/30)
  - [ ] 结束界面优化
- [x] 增加计分机制(2022/7/230)
- [ ] 优化操作手感
- [x] 进行性能优化(2022/7/14)
  - [x] 进一步性能优化(2022/7/17)
    - [ ] 再次性能优化
- [ ] 由于蛇的长度会影响速度，欲添加随时间增长蛇速度的机制以鼓励玩家增加蛇的长度
## 已知BUG
- [ ] (偶尔)生成一半在下边界内的球
- [ ] (偶尔)生成重叠在一起的球
- [x] (偶尔)碰到自己后卡死(2022/1/30)
- [x] (偶尔)吃到球的瞬间程序卡死(2022/7/23)
- [x] (触发条件未知)吃掉一个球后会导致另一个球一并消失(2022/7/23)
- [x] (必定)蛇的长度变长后速度会变慢(添加动态速度以解决)(2022/7/23)(减少影响,没有彻底解决)