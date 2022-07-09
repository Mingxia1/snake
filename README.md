# **Snake(仮)**
## 项目说明
这是一个类似贪吃蛇的小游戏。都什么年代了还在玩传统贪吃蛇，这个贪吃蛇可以360°全向旋转，目前还没有球让它吃。
## 开发平台
本项目基于Qt6.3.1开发，构建方式为CMAKE，可以使用配置好的vscode或qtcreator构建此程序。
## 实现方法
使用QPainter类在QWidget类窗口中绘制以很多QPainterPath微元构成的蛇，利用QTimer实现每毫秒更新一次画面。
## 文件说明
- main.cpp
  - 此文件是qt自动生成的程序入口
- paintarea.h/cpp
  - 本来是作为测试QPainter类的临时QWidget类窗口，后来此窗口担当了游戏的主要舞台，由于很懒所以没有改名字。获取各类数据，承担几乎所有绘图任务。
- snake.h/cpp
  - 自定义的snake类，记录了蛇的速度，角度，长度，颜色，宽度，位置等数据，并定义了几个蛇的动作。
- widget.h/cpp
  - 整个程序的主窗口，程序的初始化就从这里开始，控制整个游戏流程。
- widget.ui
  - 主窗口的qtdesigner设计文件
## 待办列表
- [ ] 随机生成的球以及相关交互
- [ ] 增加游戏开始界面
- [ ] 增加游戏结束界面
- [ ] 增加计分机制
- [ ] 优化操作手感
- [ ] 进行性能优化
- [ ] 构思中（?